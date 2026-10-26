#pragma once

#include <algorithm>
#include <array>
#include <cmath>
#include <cstddef>
#include <limits>
#include <type_traits>

#include <catch2/catch_test_macros.hpp>
#include <SEL/Maths/Matrix.hpp>

namespace matrixTests
{
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
