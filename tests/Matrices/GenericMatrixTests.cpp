#include <SEL/Maths/Matrices/MatrixMultiplications.hpp>
// Direct multiplication-header users retain the named compatibility types.
static_assert(std::is_same_v<sel::Mat4x4f, sel::Matrix<float, 4, 4>>);

#include "Int4Checks.hpp"
#include <catch2/catch_template_test_macros.hpp>
#include <memory>

namespace {
    template <class Left, class Right, class = void>
    struct CanMultiply : std::false_type {};

    template <class Left, class Right>
    struct CanMultiply<Left, Right,
        std::void_t<decltype(std::declval<Left>() * std::declval<Right>())>> : std::true_type {};

    static_assert(!CanMultiply<sel::Matrix<float, 2, 3>, sel::Matrix<float, 2, 4>>::value);
    static_assert(!CanMultiply<sel::Matrix<int, 2, 3>, sel::Matrix<float, 3, 4>>::value);
    static_assert(CanMultiply<sel::Matrix<float, 1, 4>, sel::Matrix<float, 4, 1>>::value);
    static_assert(std::is_same_v<sel::Mat8x8f, sel::Matrix<float, 8, 8>>);
    static_assert(std::is_same_v<sel::Mat2x3i4, sel::Matrix<sel::Int4, 2, 3>>);
    static_assert(std::is_same_v<sel::int4_t, sel::Int4>);
    constexpr sel::Matrix<int, 2, 3> values(1, 2, 3, 4, 5, 6);
    static_assert(values[1][2] == 6);
    static_assert(sel::Matrix<int, 1, 1>(7)[0][0] == 7);
}

TEMPLATE_TEST_CASE("Generic rectangular matrix operations", "[matrix][operations]",
                   std::int8_t, int, unsigned int, float, double)
{
    using Matrix = sel::Matrix<TestType, 3, 5>;
    static_assert(Matrix::row_count == 3 && Matrix::column_count == 5);
    static_assert(std::is_same_v<typename Matrix::value_type, TestType>);
    static_assert(sizeof(Matrix) == 15 * sizeof(TestType));
    static_assert(alignof(Matrix) == alignof(TestType));
    const Matrix zero;
    const Matrix diagonal(TestType(3));
    const Matrix identity = Matrix::identity();
    const Matrix original(0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14);
    Matrix copy(original);
    Matrix assigned;
    assigned = original;
    copy += diagonal;
    copy -= diagonal;
    const Matrix restored = (original + diagonal) - diagonal;
    for (std::size_t row = 0; row < 3; ++row)
        for (std::size_t column = 0; column < 5; ++column)
        {
            CAPTURE(row, column);
            CHECK(zero[row][column] == TestType(0));
            CHECK(diagonal[row][column] == TestType(row == column ? 3 : 0));
            CHECK(identity[row][column] == TestType(row == column ? 1 : 0));
            CHECK(original[row][column] == TestType(row * 5 + column));
            CHECK(copy[row][column] == original[row][column]);
            CHECK(assigned[row][column] == original[row][column]);
            CHECK(restored[row][column] == original[row][column]);
        }
    const auto product = original * sel::Matrix<TestType, 5, 5>::identity();
    for (std::size_t row = 0; row < 3; ++row)
        for (std::size_t column = 0; column < 5; ++column)
            CHECK(product[row][column] == original[row][column]);
}

TEST_CASE("Generic packed matrices preserve odd rows and singleton storage", "[matrix][int4]")
{
    matrixTests::checkInt4Operations<sel::Matrix<sel::Int4, 1, 1>, 1, 1>();
    matrixTests::checkInt4Operations<sel::Matrix<sel::Int4, 3, 5>, 3, 5>();
    matrixTests::checkInt4Operations<sel::Matrix<sel::Int4, 1, 8>, 1, 8>();
    matrixTests::checkInt4Operations<sel::Matrix<sel::Int4, 8, 1>, 8, 1>();
}

TEST_CASE("Long signed-byte dot product wraps without signed accumulator overflow", "[matrix][int8]")
{
    constexpr std::size_t inner = 140001;
    auto left = std::make_unique<sel::Matrix<std::int8_t, 1, inner>>();
    auto right = std::make_unique<sel::Matrix<std::int8_t, inner, 1>>();
    for (std::size_t k = 0; k < inner; ++k)
    {
        (*left)[0][k] = -127;
        (*right)[k][0] = -127;
    }
    // 16129 * 140001 exceeds INT32_MAX. Its residue is 225, decoded as -31.
    const auto product = *left * *right;
    CHECK(product[0][0] == -31);
}

TEST_CASE("Long packed dot products preserve modular arithmetic", "[matrix][int4]")
{
    auto left = std::make_unique<sel::Matrix<sel::Int4, 1, 140002>>();
    auto right = std::make_unique<sel::Matrix<sel::Int4, 140002, 4>>();
    for (std::size_t k = 0; k < 140002; ++k)
    {
        (*left)[0][k] = 7;
        for (std::size_t column = 0; column < 4; ++column)
            (*right)[k][column] = int(column) + 4;
    }
    const auto product = *left * *right;
    // Only the two terms left after reducing 140002 modulo 16 matter.
    const int expected[] = {-8, 6, 4, 2};
    for (std::size_t column = 0; column < 4; ++column)
        CHECK(int(product[0][column]) == expected[column]);
}
