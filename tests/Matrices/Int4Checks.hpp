#pragma once

#include <array>
#include <cstring>
#include <type_traits>
#include <utility>

#include <catch2/catch_test_macros.hpp>
#include <SEL/Maths/Matrix.hpp>

namespace matrixTests
{
    // Independent mathematical normalization, without using SEL arithmetic.
    constexpr int wrapInt4(int value)
    {
        const int residue = (value % 16 + 16) % 16;
        return residue >= 8 ? residue - 16 : residue;
    }

    template <class Matrix, std::size_t... Indices>
    Matrix constructInt4Matrix(std::index_sequence<Indices...>)
    {
        return Matrix((int(Indices % 31) - 15)...);
    }

    template <class Matrix, std::size_t Rows, std::size_t Columns>
    void checkInt4Operations()
    {
        constexpr std::size_t count = Rows * Columns;
        static_assert(sizeof(Matrix) == (count + 1) / 2);
        static_assert(alignof(Matrix) == 1);
        static_assert(std::is_trivially_copyable_v<Matrix>);
        static_assert(std::is_same_v<decltype(std::declval<const Matrix&>()[0][0]), sel::Int4>);
        static_assert(std::is_same_v<decltype(std::declval<Matrix&>() += std::declval<const Matrix&>()), Matrix&>);
        static_assert(std::is_same_v<decltype(std::declval<Matrix&>() -= std::declval<const Matrix&>()), Matrix&>);
        static_assert(std::is_same_v<decltype(std::declval<Matrix>() + std::declval<Matrix>()), Matrix>);
        static_assert(std::is_same_v<decltype(std::declval<Matrix>() - std::declval<Matrix>()), Matrix>);

        Matrix zero;
        const Matrix diagonal(7);
        const Matrix identity = Matrix::identity();
        const Matrix original = constructInt4Matrix<Matrix>(std::make_index_sequence<count>{});
        Matrix copy(original);
        Matrix assigned;
        assigned = original;
        const Matrix sum = original + diagonal;
        const Matrix difference = original - diagonal;
        copy += diagonal;
        copy -= diagonal;

        for (std::size_t row = 0; row < Rows; ++row)
        {
            for (std::size_t column = 0; column < Columns; ++column)
            {
                CAPTURE(row, column);
                const auto index = row * Columns + column;
                const int value = wrapInt4(int(index % 31) - 15);
                const int offset = row == column ? 7 : 0;
                CHECK(int(zero[row][column]) == 0);
                CHECK(int(diagonal[row][column]) == offset);
                CHECK(int(identity[row][column]) == (row == column ? 1 : 0));
                CHECK(int(original[row][column]) == value);
                CHECK(int(copy[row][column]) == value);
                CHECK(int(assigned[row][column]) == value);
                CHECK(int(sum[row][column]) == wrapInt4(value + offset));
                CHECK(int(difference[row][column]) == wrapInt4(value - offset));
            }
        }

        // Verify the actual layout, including the zero high nibble for odd counts.
        std::array<unsigned char, sizeof(Matrix)> bytes{};
        std::memcpy(bytes.data(), &original, sizeof(Matrix));
        for (std::size_t byte = 0; byte < bytes.size(); ++byte)
        {
            const auto index = byte * 2;
            const int low = (wrapInt4(int(index % 31) - 15) + 16) % 16;
            const int high = index + 1 < count
                ? (wrapInt4(int((index + 1) % 31) - 15) + 16) % 16 : 0;
            CHECK(int(bytes[byte]) == low + 16 * high);
        }

        // Change each nibble independently, checking every other element each time.
        for (std::size_t index = 0; index < count; ++index)
        {
            Matrix changed = original;
            changed[index / Columns][index % Columns] = 23;
            for (std::size_t other = 0; other < count; ++other)
            {
                const int expected = other == index ? 7 : wrapInt4(int(other % 31) - 15);
                REQUIRE(int(changed[other / Columns][other % Columns]) == expected);
            }
        }

        // Assignment must copy values, even between two nibbles sharing a byte.
        assigned[0][0] = 7;
        assigned[0][1] = -8;
        assigned[0][0] = assigned[0][1];
        CHECK(int(assigned[0][0]) == -8);
        CHECK(int(assigned[0][1]) == -8);
        assigned[0][0] = 3;
        CHECK(int(assigned[0][1]) == -8);
        assigned[0][1] = assigned[0][0];
        CHECK(int(assigned[0][1]) == 3);
        assigned[0][0] = assigned[0][0];
        CHECK(int(assigned[0][0]) == 3);
        assigned[0][0] = original[Rows - 1][Columns - 1];
        CHECK(assigned[0][0] == original[Rows - 1][Columns - 1]);

        zero[0][0] = 7;
        zero[0][0] += 1;
        CHECK(int(zero[0][0]) == -8);
        zero[0][0] -= 1;
        CHECK(int(zero[0][0]) == 7);
        zero[0][0] *= 7;
        CHECK(int(zero[0][0]) == 1);
        zero[0][1] = 2;
        CHECK(int(zero[0][0] + zero[0][1]) == 3);
        CHECK(int(zero[0][0] - zero[0][1]) == -1);
        CHECK(int(zero[0][0] * zero[0][1]) == 2);
        CHECK(zero[0][0] < zero[0][1]);

        assigned = original;
        assigned += assigned;
        for (std::size_t index = 0; index < count; ++index)
        {
            CHECK(int(assigned[index / Columns][index % Columns])
                  == wrapInt4(2 * wrapInt4(int(index % 31) - 15)));
        }
        assigned -= assigned;
        for (std::size_t index = 0; index < count; ++index)
        {
            CHECK(int(assigned[index / Columns][index % Columns]) == 0);
        }
        if constexpr (count % 2 != 0)
        {
            copy[Rows - 1][Columns - 1] = -1;
            std::memcpy(bytes.data(), &copy, sizeof(Matrix));
            CHECK((bytes.back() & 0xf0u) == 0);
            std::memcpy(bytes.data(), &sum, sizeof(Matrix));
            CHECK((bytes.back() & 0xf0u) == 0);
        }
    }
}
