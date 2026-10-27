#include "Int4Checks.hpp"

#include <cstdint>
#include <limits>

static_assert(int(sel::Int4(7) + sel::Int4(1)) == -8);
static_assert(int(sel::Int4(-8) - sel::Int4(1)) == 7);
static_assert(int(sel::Int4(-8) * sel::Int4(-8)) == 0);
static_assert(sel::Mat3x3i4::identity()[2][2] == sel::Int4(1));

TEST_CASE("int4 construction and conversion", "[int4]")
{
    CHECK(int(sel::Int4()) == 0);
    for (int value = -512; value <= 512; ++value)
    {
        CHECK(int(sel::Int4(value)) == matrixTests::wrapInt4(value));
        CHECK(sel::Int4(value).value() == matrixTests::wrapInt4(value));
    }
    CHECK(int(sel::Int4(std::numeric_limits<int>::min())) == 0);
    CHECK(int(sel::Int4(std::numeric_limits<int>::max())) == -1);
    CHECK(int(sel::Int4(std::numeric_limits<std::int64_t>::min())) == 0);
    CHECK(int(sel::Int4(std::numeric_limits<std::int64_t>::max())) == -1);
    CHECK(int(sel::Int4(std::numeric_limits<std::uint64_t>::max())) == -1);
}

TEST_CASE("int4 exhaustive arithmetic and comparisons", "[int4]")
{
    for (int left = -8; left <= 7; ++left)
    {
        const sel::Int4 a(left);
        CHECK(int(+a) == left);
        CHECK(int(-a) == matrixTests::wrapInt4(-left));
        for (int right = -8; right <= 7; ++right)
        {
            CAPTURE(left, right);
            const sel::Int4 b(right);
            CHECK(int(a + b) == matrixTests::wrapInt4(left + right));
            CHECK(int(a - b) == matrixTests::wrapInt4(left - right));
            CHECK(int(a * b) == matrixTests::wrapInt4(left * right));
            auto value = a;
            CHECK(&(value += b) == &value);
            CHECK(int(value) == matrixTests::wrapInt4(left + right));
            value = a;
            CHECK(&(value -= b) == &value);
            CHECK(int(value) == matrixTests::wrapInt4(left - right));
            value = a;
            CHECK(&(value *= b) == &value);
            CHECK(int(value) == matrixTests::wrapInt4(left * right));
            CHECK((a == b) == (left == right));
            CHECK((a != b) == (left != right));
            CHECK((a < b) == (left < right));
            CHECK((a > b) == (left > right));
            CHECK((a <= b) == (left <= right));
            CHECK((a >= b) == (left >= right));
        }
    }
}

TEST_CASE("int4 exhaustive proxy arithmetic preserves adjacent values", "[int4][matrix]")
{
    for (int left = -8; left <= 7; ++left)
    {
        for (int right = -8; right <= 7; ++right)
        {
            CAPTURE(left, right);
            sel::Mat2x2i4 matrix;
            matrix[0][0] = left;
            matrix[0][1] = right;
            CHECK(int(+matrix[0][0]) == left);
            CHECK(int(-matrix[0][0]) == matrixTests::wrapInt4(-left));
            CHECK(int(matrix[0][0] + matrix[0][1]) == matrixTests::wrapInt4(left + right));
            CHECK(int(matrix[0][0] - matrix[0][1]) == matrixTests::wrapInt4(left - right));
            CHECK(int(matrix[0][0] * matrix[0][1]) == matrixTests::wrapInt4(left * right));
            CHECK((matrix[0][0] == matrix[0][1]) == (left == right));
            CHECK((matrix[0][0] != matrix[0][1]) == (left != right));
            CHECK((matrix[0][0] < matrix[0][1]) == (left < right));
            CHECK((matrix[0][0] > matrix[0][1]) == (left > right));
            CHECK((matrix[0][0] <= matrix[0][1]) == (left <= right));
            CHECK((matrix[0][0] >= matrix[0][1]) == (left >= right));

            matrix[0][0] += matrix[0][1];
            CHECK(int(matrix[0][0]) == matrixTests::wrapInt4(left + right));
            CHECK(int(matrix[0][1]) == right);
            matrix[0][0] = left;
            matrix[0][1] -= matrix[0][0];
            CHECK(int(matrix[0][1]) == matrixTests::wrapInt4(right - left));
            CHECK(int(matrix[0][0]) == left);
            matrix[0][1] = right;
            matrix[0][0] *= matrix[0][1];
            CHECK(int(matrix[0][0]) == matrixTests::wrapInt4(left * right));
            CHECK(int(matrix[0][1]) == right);

            auto reference = matrix[0][0];
            auto copiedReference = reference;
            copiedReference = left;
            CHECK(int(matrix[0][0]) == left);
            reference = matrix[0][1];
            CHECK(int(matrix[0][0]) == right);
            CHECK(int(matrix[0][1]) == right);
        }
    }
}
