#include <SEL/Maths/Float4E2M1.hpp>
#include <SEL/Maths/Float8E4M3.hpp>
#include <SEL/Maths/Float8E5M2.hpp>
#include <SEL/Maths/Matrix.hpp>

#include <array>
#include <cmath>
#include <cstring>
#include <iomanip>
#include <limits>
#include <sstream>
#include <type_traits>
#include <utility>
#include <catch2/catch_template_test_macros.hpp>

namespace {
    // Test-only reference: decode the published fields with ldexp, then find
    // the closest finite code by exhaustive search, independently of SEL.
    template <class T> struct Format
    {
        static constexpr int e = std::is_same_v<T, sel::Float4E2M1> ? 2
                               : std::is_same_v<T, sel::Float8E4M3> ? 4 : 5;
        static constexpr int m = e == 2 ? 1 : e == 4 ? 3 : 2;
        static constexpr unsigned sign = 1u << (e + m);
        static constexpr unsigned maximum = e == 2 ? 7 : e == 4 ? 126 : 123;
        static constexpr unsigned nan = e == 2 ? 0 : e == 4 ? 127 : 126;
    };

    template <class T> float decode(unsigned bits)
    {
        using F = Format<T>;
        const unsigned magnitude = bits & (F::sign - 1);
        const unsigned exponent = magnitude >> F::m;
        const unsigned fraction = magnitude % (1u << F::m);
        float value;
        if constexpr (F::e == 4)
        {
            if (magnitude == 127) return std::numeric_limits<float>::quiet_NaN();
        }
        if constexpr (F::e == 5)
        {
            if (exponent == 31)
            {
                value = fraction ? std::numeric_limits<float>::quiet_NaN()
                                 : std::numeric_limits<float>::infinity();
                return bits & F::sign ? -value : value;
            }
        }
        const int bias = (1 << (F::e - 1)) - 1;
        value = std::ldexp(float(fraction + (exponent ? (1u << F::m) : 0u)),
                           int(exponent ? exponent : 1) - bias - F::m);
        return bits & F::sign ? -value : value;
    }

    template <class T> unsigned encode(long double value)
    {
        using F = Format<T>;
        if (std::isnan(value)) return F::nan;
        const unsigned sign = std::signbit(value) ? F::sign : 0;
        value = std::fabs(value);
        if (value >= decode<T>(F::maximum)) return sign | F::maximum;
        static const auto grid = [] {
            std::array<long double, F::maximum + 1> result{};
            for (unsigned code = 0; code <= F::maximum; ++code) result[code] = decode<T>(code);
            return result;
        }();
        unsigned best = 0;
        long double distance = value;
        for (unsigned code = 1; code <= F::maximum; ++code)
        {
            const auto candidate = std::fabs(value - grid[code]);
            if (candidate < distance || (candidate == distance && code % 2 == 0))
            {
                best = code;
                distance = candidate;
            }
        }
        return sign | best;
    }

    template <class T, std::size_t Rows, std::size_t Columns>
    void matrixOperations()
    {
        using M = sel::Matrix<T, Rows, Columns>;
        constexpr bool packed = std::is_same_v<T, sel::Float4E2M1>;
        static_assert(sizeof(M) == (packed ? (Rows * Columns + 1) / 2 : Rows * Columns));
        static_assert(alignof(M) == 1);
        static_assert(std::is_same_v<typename M::value_type, T>);
        M original;
        const M zero;
        const M diagonal(T(2));
        const M identity = M::identity();
        for (std::size_t row = 0; row < Rows; ++row)
            for (std::size_t col = 0; col < Columns; ++col)
                original[row][col] = T::from_bits((row * Columns + col) % (Format<T>::maximum + 1));
        M copy(original), assigned;
        assigned = original;
        const M sum = original + diagonal;
        const M difference = original - diagonal;
        copy += diagonal;
        assigned -= diagonal;
        for (std::size_t row = 0; row < Rows; ++row)
            for (std::size_t col = 0; col < Columns; ++col)
            {
                CHECK(zero[row][col].bits() == 0);
                CHECK(diagonal[row][col].value() == (row == col ? 2 : 0));
                CHECK(identity[row][col].value() == (row == col ? 1 : 0));
                const float a = original[row][col].value(), b = diagonal[row][col].value();
                CHECK(sum[row][col].bits() == encode<T>(a + b));
                CHECK(difference[row][col].bits() == encode<T>(a - b));
                CHECK(copy[row][col].bits() == sum[row][col].bits());
                CHECK(assigned[row][col].bits() == difference[row][col].bits());
            }
        // Also inspect physical nibble ordering and padding across odd rows.
        if constexpr (packed)
        {
            std::array<unsigned char, sizeof(M)> bytes{};
            std::memcpy(bytes.data(), &original, sizeof(M));
            for (std::size_t i = 0; i < Rows * Columns; ++i)
                CHECK(((bytes[i / 2] >> (4 * (i % 2))) & 15u) == i % 8);
            if constexpr ((Rows * Columns) % 2) CHECK((bytes.back() & 0xf0u) == 0);
            std::memcpy(bytes.data(), &copy, sizeof(M));
            if constexpr ((Rows * Columns) % 2) CHECK((bytes.back() & 0xf0u) == 0);
        }
    }

    template <class L, class R, class = void> struct CanMultiply : std::false_type {};
    template <class L, class R> struct CanMultiply<L, R,
        std::void_t<decltype(std::declval<L>() * std::declval<R>())>> : std::true_type {};
    static_assert(!CanMultiply<sel::Matrix<sel::Float8E4M3, 2, 3>,
                              sel::Matrix<sel::Float8E5M2, 3, 2>>::value);
    static_assert(!CanMultiply<sel::Matrix<sel::Float4E2M1, 2, 3>,
                              sel::Matrix<sel::Float4E2M1, 2, 3>>::value);
    static_assert(sel::Float8E4M3::from_bits(0x38).value() == 1);
    static_assert(sel::Float8E5M2::from_bits(0x3c).value() == 1);
    static_assert(sel::Float4E2M1::from_bits(0xf2).bits() == 2);
}

TEMPLATE_TEST_CASE("Low-precision decoding and conversions", "[float][conversion]",
                   sel::Float4E2M1, sel::Float8E4M3, sel::Float8E5M2)
{
    using T = TestType;
    using F = Format<T>;
    static_assert(sizeof(T) == 1 && alignof(T) == 1);
    static_assert(std::is_trivially_copyable_v<T>);
    static_assert(std::is_convertible_v<float, T> && std::is_convertible_v<int, T>);
    static_assert(!std::is_convertible_v<T, float>);
    CHECK(T().bits() == 0);
    CHECK(T(-0.0).bits() == F::sign);
    CHECK(T(1LL).value() == 1);
    CHECK(T(1ULL).value() == 1);
    CHECK(T(true).value() == 1);
    CHECK(T(std::numeric_limits<long double>::infinity()).bits() == F::maximum);
    CHECK(T(-std::numeric_limits<long double>::infinity()).bits() == (F::sign | F::maximum));
    CHECK(T(std::numeric_limits<long double>::quiet_NaN()).bits() == F::nan);
    CHECK(T(std::numeric_limits<long double>::max()).bits() == F::maximum);
    CHECK(T(-std::numeric_limits<long double>::max()).bits() == (F::sign | F::maximum));
    for (unsigned bits = 0; bits < 2 * F::sign; ++bits)
    {
        CAPTURE(bits);
        const T value = T::from_bits(static_cast<unsigned char>(bits));
        const float expected = decode<T>(bits);
        CHECK(value.bits() == bits);
        CHECK((-value).bits() == (bits ^ F::sign));
        CHECK((+value).bits() == bits);
        if (std::isnan(expected)) CHECK(std::isnan(value.value()));
        else
        {
            CHECK(value.value() == expected);
            CHECK(float(value) == expected);
            CHECK(std::signbit(value.value()) == std::signbit(expected));
            if (std::isfinite(expected)) CHECK(T(expected).bits() == bits);
        }
    }
    for (unsigned lower = 0; lower < F::maximum; ++lower)
    {
        const long double midpoint = (static_cast<long double>(decode<T>(lower)) + decode<T>(lower + 1)) / 2;
        const unsigned tie = lower % 2 ? lower + 1 : lower;
        for (int sign : {1, -1})
        {
            const unsigned signbit = sign < 0 ? F::sign : 0;
            CHECK(T(sign * midpoint).bits() == (signbit | tie));
            CHECK(T(sign * std::nextafter(midpoint, 0.0L)).bits() == (signbit | lower));
            CHECK(T(sign * std::nextafter(midpoint, std::numeric_limits<long double>::infinity())).bits()
                  == (signbit | (lower + 1)));
            const double middle = static_cast<double>(midpoint);
            CHECK(T(sign * std::nextafter(middle, 0.0)).bits() == (signbit | lower));
            CHECK(T(sign * std::nextafter(middle, std::numeric_limits<double>::infinity())).bits()
                  == (signbit | (lower + 1)));
            const float middle32 = static_cast<float>(midpoint);
            CHECK(T(sign * std::nextafter(middle32, 0.0f)).bits() == (signbit | lower));
            CHECK(T(sign * std::nextafter(middle32, std::numeric_limits<float>::infinity())).bits()
                  == (signbit | (lower + 1)));
        }
    }
    std::ostringstream stream;
    stream << std::fixed << std::setprecision(2) << T(1.5) << ' ' << T(-2);
    CHECK(stream.str() == "1.50 -2.00");
}

TEMPLATE_TEST_CASE("Low-precision exhaustive scalar arithmetic", "[float][arithmetic]",
                   sel::Float4E2M1, sel::Float8E4M3, sel::Float8E5M2)
{
    using T = TestType;
    for (unsigned left = 0; left < 2 * Format<T>::sign; ++left)
        for (unsigned right = 0; right < 2 * Format<T>::sign; ++right)
        {
            CAPTURE(left, right);
            const T a = T::from_bits(left), b = T::from_bits(right);
            const float x = decode<T>(left), y = decode<T>(right);
            volatile float add = x + y, subtract = x - y, multiply = x * y, divide = x / y;
            CHECK((a + b).bits() == encode<T>(add));
            CHECK((a - b).bits() == encode<T>(subtract));
            CHECK((a * b).bits() == encode<T>(multiply));
            CHECK((a / b).bits() == encode<T>(divide));
            T compound = a;
            CHECK((compound += b).bits() == encode<T>(add));
            compound = a;
            CHECK((compound -= b).bits() == encode<T>(subtract));
            compound = a;
            CHECK((compound *= b).bits() == encode<T>(multiply));
            compound = a;
            CHECK((compound /= b).bits() == encode<T>(divide));
            CHECK((a == b) == (x == y));
            CHECK((a != b) == (x != y));
            CHECK((a < b) == (x < y));
            CHECK((a > b) == (x > y));
            CHECK((a <= b) == (x <= y));
            CHECK((a >= b) == (x >= y));
        }
}

TEST_CASE("Packed FP4 proxies preserve values and neighboring nibbles", "[float][proxy]")
{
    using T = sel::Float4E2M1;
    for (unsigned left = 0; left < 16; ++left)
        for (unsigned right = 0; right < 16; ++right)
        {
            sel::Matrix<T, 1, 2> matrix(T::from_bits(left), T::from_bits(right));
            auto proxy = matrix[0][0];
            auto alias = proxy;
            const float x = decode<T>(left), y = decode<T>(right);
            CHECK((proxy + matrix[0][1]).bits() == encode<T>(x + y));
            CHECK((proxy - matrix[0][1]).bits() == encode<T>(x - y));
            CHECK((proxy * matrix[0][1]).bits() == encode<T>(x * y));
            CHECK((proxy / matrix[0][1]).bits() == encode<T>(x / y));
            CHECK((proxy == matrix[0][1]) == (x == y));
            CHECK((proxy != matrix[0][1]) == (x != y));
            CHECK((proxy < matrix[0][1]) == (x < y));
            CHECK((proxy > matrix[0][1]) == (x > y));
            CHECK((proxy <= matrix[0][1]) == (x <= y));
            CHECK((proxy >= matrix[0][1]) == (x >= y));
            CHECK(float(proxy) == x);
            CHECK((-proxy).bits() == (left ^ 8));
            CHECK((+proxy).bits() == left);
            proxy += matrix[0][1];
            CHECK(proxy.bits() == encode<T>(x + y));
            CHECK(alias.bits() == proxy.bits());
            CHECK(matrix[0][1].bits() == right);
            proxy = T::from_bits(left);
            proxy -= matrix[0][1];
            CHECK(proxy.bits() == encode<T>(x - y));
            proxy = T::from_bits(left);
            proxy *= matrix[0][1];
            CHECK(proxy.bits() == encode<T>(x * y));
            proxy = T::from_bits(left);
            proxy /= matrix[0][1];
            CHECK(proxy.bits() == encode<T>(x / y));
            proxy = matrix[0][1];
            CHECK(proxy.bits() == right);
            CHECK(alias.bits() == right);
            CHECK(matrix[0][1].bits() == right);
            std::ostringstream stream;
            stream << proxy << ' ' << std::as_const(matrix)[0][1];
            std::ostringstream expected;
            expected << y << ' ' << y;
            CHECK(stream.str() == expected.str());
        }
}

TEMPLATE_TEST_CASE("Low-precision matrix construction and element arithmetic", "[float][matrix]",
                   sel::Float4E2M1, sel::Float8E4M3, sel::Float8E5M2)
{
    matrixOperations<TestType, 1, 1>();
    matrixOperations<TestType, 1, 8>();
    matrixOperations<TestType, 8, 1>();
    matrixOperations<TestType, 3, 5>();
    matrixOperations<TestType, 2, 2>();
    matrixOperations<TestType, 2, 3>();
    matrixOperations<TestType, 2, 4>();
    matrixOperations<TestType, 3, 2>();
    matrixOperations<TestType, 3, 3>();
    matrixOperations<TestType, 3, 4>();
    matrixOperations<TestType, 4, 2>();
    matrixOperations<TestType, 4, 3>();
    matrixOperations<TestType, 4, 4>();
    matrixOperations<TestType, 8, 8>();
    matrixOperations<TestType, 16, 16>();
    matrixOperations<TestType, 32, 32>();
    using T = TestType;
    const sel::Matrix<T, 2, 3> values(1, 2, 3, 4, 5, 6);
    const float expected[] = {1, 2, 3, 4, 5, 6};
    for (unsigned i = 0; i < 6; ++i)
        CHECK(values[i / 3][i % 3].bits() == encode<T>(expected[i]));
    const sel::Matrix<T, 1, 1> singleton(2);
    CHECK(singleton[0][0].value() == 2);
}

TEMPLATE_TEST_CASE("Low-precision multiplication retains FP32 intermediate values", "[float][matrix]",
                   sel::Float4E2M1, sel::Float8E4M3, sel::Float8E5M2)
{
    using T = TestType;
    const auto maximum = decode<T>(Format<T>::maximum);
    const sel::Matrix<T, 1, 3> a(maximum, maximum, 1);
    const sel::Matrix<T, 3, 1> b(2, -1, 1);
    const auto result = a * b;
    CHECK(result[0][0].value() == maximum);
    static_assert(!sel::utils::matrixHasSimd<T, 4, 4, 4>);
    static_assert(std::is_same_v<decltype(result), const sel::Matrix<T, 1, 1>>);

    // Raw special values also propagate through FP32 arithmetic and final conversion.
    if constexpr (!std::is_same_v<T, sel::Float4E2M1>)
    {
        const sel::Matrix<T, 1, 1> nan(T::from_bits(Format<T>::nan));
        const auto output = nan * sel::Matrix<T, 1, 1>(1);
        CHECK(std::isnan(output[0][0].value()));
    }
    if constexpr (std::is_same_v<T, sel::Float8E5M2>)
    {
        const sel::Matrix<T, 1, 3> roundingLeft(maximum, 1, -maximum);
        const sel::Matrix<T, 3, 1> roundingRight(maximum, 1, maximum);
        CHECK((roundingLeft * roundingRight)[0][0].bits() == 0);
        const sel::Matrix<T, 1, 1> infinity(T::from_bits(0x7c));
        CHECK((infinity * sel::Matrix<T, 1, 1>(1))[0][0].bits() == 0x7b);
        CHECK(std::isnan((infinity * sel::Matrix<T, 1, 1>(0))[0][0].value()));
    }
}
static_assert(std::is_same_v<sel::Mat16x16f4, sel::Mat16x16<sel::Float4E2M1>>);
static_assert(std::is_same_v<sel::Mat16x16f8, sel::Mat16x16<sel::Float8E4M3>>);
static_assert(std::is_same_v<sel::Mat16x16f4e2m1, sel::Mat16x16<sel::Float4E2M1>>);
static_assert(std::is_same_v<sel::Mat16x16f8e4m3, sel::Mat16x16<sel::Float8E4M3>>);
static_assert(std::is_same_v<sel::Mat16x16f8e5m2, sel::Mat16x16<sel::Float8E5M2>>);
static_assert(std::is_same_v<sel::Mat2x2f4, sel::Mat2x2<sel::Float4E2M1>>);
static_assert(std::is_same_v<sel::Mat2x2f8, sel::Mat2x2<sel::Float8E4M3>>);
static_assert(std::is_same_v<sel::Mat2x2f4e2m1, sel::Mat2x2<sel::Float4E2M1>>);
static_assert(std::is_same_v<sel::Mat2x2f8e4m3, sel::Mat2x2<sel::Float8E4M3>>);
static_assert(std::is_same_v<sel::Mat2x2f8e5m2, sel::Mat2x2<sel::Float8E5M2>>);
static_assert(std::is_same_v<sel::Mat2x3f4, sel::Mat2x3<sel::Float4E2M1>>);
static_assert(std::is_same_v<sel::Mat2x3f8, sel::Mat2x3<sel::Float8E4M3>>);
static_assert(std::is_same_v<sel::Mat2x3f4e2m1, sel::Mat2x3<sel::Float4E2M1>>);
static_assert(std::is_same_v<sel::Mat2x3f8e4m3, sel::Mat2x3<sel::Float8E4M3>>);
static_assert(std::is_same_v<sel::Mat2x3f8e5m2, sel::Mat2x3<sel::Float8E5M2>>);
static_assert(std::is_same_v<sel::Mat2x4f4, sel::Mat2x4<sel::Float4E2M1>>);
static_assert(std::is_same_v<sel::Mat2x4f8, sel::Mat2x4<sel::Float8E4M3>>);
static_assert(std::is_same_v<sel::Mat2x4f4e2m1, sel::Mat2x4<sel::Float4E2M1>>);
static_assert(std::is_same_v<sel::Mat2x4f8e4m3, sel::Mat2x4<sel::Float8E4M3>>);
static_assert(std::is_same_v<sel::Mat2x4f8e5m2, sel::Mat2x4<sel::Float8E5M2>>);
static_assert(std::is_same_v<sel::Mat32x32f4, sel::Mat32x32<sel::Float4E2M1>>);
static_assert(std::is_same_v<sel::Mat32x32f8, sel::Mat32x32<sel::Float8E4M3>>);
static_assert(std::is_same_v<sel::Mat32x32f4e2m1, sel::Mat32x32<sel::Float4E2M1>>);
static_assert(std::is_same_v<sel::Mat32x32f8e4m3, sel::Mat32x32<sel::Float8E4M3>>);
static_assert(std::is_same_v<sel::Mat32x32f8e5m2, sel::Mat32x32<sel::Float8E5M2>>);
static_assert(std::is_same_v<sel::Mat3x2f4, sel::Mat3x2<sel::Float4E2M1>>);
static_assert(std::is_same_v<sel::Mat3x2f8, sel::Mat3x2<sel::Float8E4M3>>);
static_assert(std::is_same_v<sel::Mat3x2f4e2m1, sel::Mat3x2<sel::Float4E2M1>>);
static_assert(std::is_same_v<sel::Mat3x2f8e4m3, sel::Mat3x2<sel::Float8E4M3>>);
static_assert(std::is_same_v<sel::Mat3x2f8e5m2, sel::Mat3x2<sel::Float8E5M2>>);
static_assert(std::is_same_v<sel::Mat3x3f4, sel::Mat3x3<sel::Float4E2M1>>);
static_assert(std::is_same_v<sel::Mat3x3f8, sel::Mat3x3<sel::Float8E4M3>>);
static_assert(std::is_same_v<sel::Mat3x3f4e2m1, sel::Mat3x3<sel::Float4E2M1>>);
static_assert(std::is_same_v<sel::Mat3x3f8e4m3, sel::Mat3x3<sel::Float8E4M3>>);
static_assert(std::is_same_v<sel::Mat3x3f8e5m2, sel::Mat3x3<sel::Float8E5M2>>);
static_assert(std::is_same_v<sel::Mat3x4f4, sel::Mat3x4<sel::Float4E2M1>>);
static_assert(std::is_same_v<sel::Mat3x4f8, sel::Mat3x4<sel::Float8E4M3>>);
static_assert(std::is_same_v<sel::Mat3x4f4e2m1, sel::Mat3x4<sel::Float4E2M1>>);
static_assert(std::is_same_v<sel::Mat3x4f8e4m3, sel::Mat3x4<sel::Float8E4M3>>);
static_assert(std::is_same_v<sel::Mat3x4f8e5m2, sel::Mat3x4<sel::Float8E5M2>>);
static_assert(std::is_same_v<sel::Mat4x2f4, sel::Mat4x2<sel::Float4E2M1>>);
static_assert(std::is_same_v<sel::Mat4x2f8, sel::Mat4x2<sel::Float8E4M3>>);
static_assert(std::is_same_v<sel::Mat4x2f4e2m1, sel::Mat4x2<sel::Float4E2M1>>);
static_assert(std::is_same_v<sel::Mat4x2f8e4m3, sel::Mat4x2<sel::Float8E4M3>>);
static_assert(std::is_same_v<sel::Mat4x2f8e5m2, sel::Mat4x2<sel::Float8E5M2>>);
static_assert(std::is_same_v<sel::Mat4x3f4, sel::Mat4x3<sel::Float4E2M1>>);
static_assert(std::is_same_v<sel::Mat4x3f8, sel::Mat4x3<sel::Float8E4M3>>);
static_assert(std::is_same_v<sel::Mat4x3f4e2m1, sel::Mat4x3<sel::Float4E2M1>>);
static_assert(std::is_same_v<sel::Mat4x3f8e4m3, sel::Mat4x3<sel::Float8E4M3>>);
static_assert(std::is_same_v<sel::Mat4x3f8e5m2, sel::Mat4x3<sel::Float8E5M2>>);
static_assert(std::is_same_v<sel::Mat4x4f4, sel::Mat4x4<sel::Float4E2M1>>);
static_assert(std::is_same_v<sel::Mat4x4f8, sel::Mat4x4<sel::Float8E4M3>>);
static_assert(std::is_same_v<sel::Mat4x4f4e2m1, sel::Mat4x4<sel::Float4E2M1>>);
static_assert(std::is_same_v<sel::Mat4x4f8e4m3, sel::Mat4x4<sel::Float8E4M3>>);
static_assert(std::is_same_v<sel::Mat4x4f8e5m2, sel::Mat4x4<sel::Float8E5M2>>);
static_assert(std::is_same_v<sel::Mat8x8f4, sel::Mat8x8<sel::Float4E2M1>>);
static_assert(std::is_same_v<sel::Mat8x8f8, sel::Mat8x8<sel::Float8E4M3>>);
static_assert(std::is_same_v<sel::Mat8x8f4e2m1, sel::Mat8x8<sel::Float4E2M1>>);
static_assert(std::is_same_v<sel::Mat8x8f8e4m3, sel::Mat8x8<sel::Float8E4M3>>);
static_assert(std::is_same_v<sel::Mat8x8f8e5m2, sel::Mat8x8<sel::Float8E5M2>>);
