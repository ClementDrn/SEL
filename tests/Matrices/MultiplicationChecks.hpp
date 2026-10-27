#pragma once

#include <algorithm>
#include <array>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <limits>
#include <type_traits>
#include <utility>

#include <catch2/catch_test_macros.hpp>
#include <SEL/Maths/Matrix.hpp>

namespace matrixTests
{
    // int4 intentionally accepts integers only. Fixtures store exact integers
    // in long double, so convert those through int before constructing int4.
    template <class T>
    T fixtureValue(long double value)
    {
        if constexpr (std::is_same_v<T, sel::int4>)
        {
            return T(static_cast<int>(value));
        }
        else
        {
            return static_cast<T>(value);
        }
    }

    // Expand row-major values into the same value constructor as small matrices.
    template <class T, class Matrix, std::size_t... Indices>
    Matrix constructSquare(const std::array<T, sizeof...(Indices)>& values,
                           std::index_sequence<Indices...>)
    {
        return Matrix(values[Indices]...);
    }

    template <class T, class Matrix, std::size_t Size>
    void checkSquareOperations()
    {
        Matrix zero;
        Matrix diagonal(T(3));
        const Matrix identity = Matrix::identity();
        std::array<T, Size * Size> values;
        for (std::size_t index = 0; index < values.size(); ++index)
        {
            values[index] = static_cast<T>(index % 17);
        }

        const Matrix original = constructSquare<T, Matrix>(values, std::make_index_sequence<Size * Size>{});
        Matrix copy(original);
        Matrix assigned;
        assigned = original;
        const Matrix sum = original + diagonal;
        const Matrix difference = sum - diagonal;
        copy += diagonal;
        copy -= diagonal;

        // Matrices only require scalar alignment; place inputs between SIMD boundaries.
        struct alignas(16) OffsetMatrix
        {
            T prefix;
            Matrix value;
        };
        static_assert(offsetof(OffsetMatrix, value) % 16 != 0);
        OffsetMatrix offsetLeft{T(0), original};
        OffsetMatrix offsetRight{T(0), identity};
        const Matrix offsetProduct = offsetLeft.value * offsetRight.value;

        // Check all elements, including off-diagonal values and the final row.
        for (std::size_t row = 0; row < Size; ++row)
        {
            for (std::size_t column = 0; column < Size; ++column)
            {
                CAPTURE(row, column);
                const T value = values[row * Size + column];
                CHECK(zero[row][column] == T(0));
                CHECK(diagonal[row][column] == T(row == column ? 3 : 0));
                CHECK(identity[row][column] == T(row == column ? 1 : 0));
                CHECK(original[row][column] == value);
                CHECK(copy[row][column] == value);
                CHECK(assigned[row][column] == value);
                CHECK(sum[row][column] == value + diagonal[row][column]);
                CHECK(difference[row][column] == value);
                CHECK(offsetProduct[row][column] == value);
            }
        }
    }

    // Inputs and expected values come from Python, independently of SEL arithmetic.
    template <class T, class Left, class Right, class Product,
              std::size_t Rows, std::size_t Inner, std::size_t Columns>
    void checkProductAt(const char* fixture,
                        Left& left, Right& right, Product& result,
                        const std::array<long double, Rows * Inner>& leftValues,
                        const std::array<long double, Inner * Columns>& rightValues,
                        const std::array<long double, Rows * Columns>& expected)
    {
        INFO("Fixture: " << fixture);
        // Fill every element explicitly; zero fixtures do not depend on constructors.
        for (std::size_t row = 0; row < Rows; ++row)
        {
            for (std::size_t column = 0; column < Inner; ++column)
            {
                left[row][column] = fixtureValue<T>(leftValues[row * Inner + column]);
            }
        }

        for (std::size_t row = 0; row < Inner; ++row)
        {
            for (std::size_t column = 0; column < Columns; ++column)
            {
                right[row][column] = fixtureValue<T>(rightValues[row * Columns + column]);
            }
        }

        static_assert(std::is_same_v<decltype(left * right), Product>);
        result = left * right;

        if constexpr (std::is_same_v<T, sel::int4> && (Rows * Columns) % 2 != 0)
        {
            std::array<unsigned char, sizeof(Product)> bytes{};
            std::memcpy(bytes.data(), &result, sizeof(Product));
            CHECK((bytes.back() & 0xf0u) == 0);
        }

        for (std::size_t row = 0; row < Rows; ++row)
        {
            for (std::size_t column = 0; column < Columns; ++column)
            {
                CAPTURE(row, column);
                const auto value = expected[row * Columns + column];
                if constexpr (std::is_floating_point_v<T>)
                {
                    // Scale the rounding allowance by the dot product's magnitudes,
                    // so cancellation near zero still has a meaningful tolerance.
                    long double scale = 0;
                    for (std::size_t inner = 0; inner < Inner; ++inner)
                    {
                        scale += std::abs(leftValues[row * Inner + inner]
                                        * rightValues[inner * Columns + column]);
                    }

                    const auto tolerance = 64 * std::numeric_limits<T>::epsilon()
                                           * std::max(1.0L, scale);
                    CHECK(std::abs(static_cast<long double>(result[row][column]) - value)
                          <= tolerance);
                }
                else
                {
                    if constexpr (std::is_same_v<T, sel::int4>)
                    {
                        // Compare decoded values, so an incorrect expectation
                        // cannot be hidden by the constructor's own wrapping.
                        CHECK(int(result[row][column]) == static_cast<int>(value));
                    }
                    else
                    {
                        CHECK(result[row][column] == static_cast<T>(value));
                    }
                }
            }
        }

        // Multiplication must preserve both operands, including rectangular ones.
        for (std::size_t row = 0; row < Rows; ++row)
        {
            for (std::size_t column = 0; column < Inner; ++column)
            {
                CAPTURE(row, column);
                CHECK(left[row][column] == fixtureValue<T>(leftValues[row * Inner + column]));
            }
        }

        for (std::size_t row = 0; row < Inner; ++row)
        {
            for (std::size_t column = 0; column < Columns; ++column)
            {
                CAPTURE(row, column);
                CHECK(right[row][column] == fixtureValue<T>(rightValues[row * Columns + column]));
            }
        }
    }

    // Force legal scalar-aligned matrix objects away from SIMD boundaries.
    // Guards also detect accidental full-vector writes past short output matrices.
    template <class T, class Matrix>
    struct alignas(16) OffsetProductMatrix
    {
        T prefix = T(42);
        Matrix value;
        T suffix = T(37);
    };

    template <class T, class Left, class Right, class Product,
              std::size_t Rows, std::size_t Inner, std::size_t Columns>
    void checkProduct(const char* fixture,
                      const std::array<long double, Rows * Inner>& leftValues,
                      const std::array<long double, Inner * Columns>& rightValues,
                      const std::array<long double, Rows * Columns>& expected)
    {
        Left left;
        Right right;
        Product result;
        checkProductAt<T, Left, Right, Product, Rows, Inner, Columns>(
            fixture, left, right, result, leftValues, rightValues, expected);

        using OffsetLeft = OffsetProductMatrix<T, Left>;
        using OffsetRight = OffsetProductMatrix<T, Right>;
        using OffsetResult = OffsetProductMatrix<T, Product>;
        static_assert(offsetof(OffsetLeft, value) % 16 != 0);
        static_assert(offsetof(OffsetRight, value) % 16 != 0);
        static_assert(offsetof(OffsetResult, value) % 16 != 0);
        OffsetLeft offsetLeft;
        OffsetRight offsetRight;
        OffsetResult offsetResult;
        INFO("Operands and result offset from 16-byte boundaries");
        checkProductAt<T, Left, Right, Product, Rows, Inner, Columns>(
            fixture, offsetLeft.value, offsetRight.value, offsetResult.value,
            leftValues, rightValues, expected);
        CHECK(offsetLeft.prefix == T(42));
        CHECK(offsetLeft.suffix == T(37));
        CHECK(offsetRight.prefix == T(42));
        CHECK(offsetRight.suffix == T(37));
        CHECK(offsetResult.prefix == T(42));
        CHECK(offsetResult.suffix == T(37));
    }
}
