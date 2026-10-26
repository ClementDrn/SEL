#pragma once

#include <algorithm>
#include <array>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <limits>
#include <type_traits>
#include <utility>

#include <catch2/catch_test_macros.hpp>
#include <SEL/Maths/Matrix.hpp>

namespace matrixTests
{
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
    void checkProduct(const char* fixture,
                      const std::array<long double, Rows * Inner>& leftValues,
                      const std::array<long double, Inner * Columns>& rightValues,
                      const std::array<long double, Rows * Columns>& expected)
    {
        INFO("Fixture: " << fixture);
        Left left;
        Right right;

        // Fill every element explicitly; zero fixtures do not depend on constructors.
        for (std::size_t row = 0; row < Rows; ++row)
        {
            for (std::size_t column = 0; column < Inner; ++column)
            {
                left[row][column] = static_cast<T>(leftValues[row * Inner + column]);
            }
        }

        for (std::size_t row = 0; row < Inner; ++row)
        {
            for (std::size_t column = 0; column < Columns; ++column)
            {
                right[row][column] = static_cast<T>(rightValues[row * Columns + column]);
            }
        }

        const auto result = left * right;
        static_assert(std::is_same_v<std::remove_cv_t<decltype(result)>, Product>);

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
                    CHECK(result[row][column] == static_cast<T>(value));
                }
            }
        }

        // Multiplication must preserve both operands, including rectangular ones.
        for (std::size_t row = 0; row < Rows; ++row)
        {
            for (std::size_t column = 0; column < Inner; ++column)
            {
                CAPTURE(row, column);
                CHECK(left[row][column] == static_cast<T>(leftValues[row * Inner + column]));
            }
        }

        for (std::size_t row = 0; row < Inner; ++row)
        {
            for (std::size_t column = 0; column < Columns; ++column)
            {
                CAPTURE(row, column);
                CHECK(right[row][column] == static_cast<T>(rightValues[row * Columns + column]));
            }
        }
    }
}
