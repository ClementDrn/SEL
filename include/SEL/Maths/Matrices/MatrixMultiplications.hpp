#pragma once

#include "GenericMatrix.hpp"

// Preserve the named shapes for code that includes this header directly.
#include "Mat2x2.hpp"
#include "Mat2x3.hpp"
#include "Mat2x4.hpp"
#include "Mat3x2.hpp"
#include "Mat3x3.hpp"
#include "Mat3x4.hpp"
#include "Mat4x2.hpp"
#include "Mat4x3.hpp"
#include "Mat4x4.hpp"
#include "Mat8x8.hpp"
#include "Mat16x16.hpp"
#include "Mat32x32.hpp"

#ifdef SEL_INTRINSIC_MATRIX_MUL
#include "Intrinsic/Float32Mul.hpp"
#include "Intrinsic/Int32Mul.hpp"
#include "Intrinsic/Int8Mul.hpp"
#include "Intrinsic/Int4Mul.hpp"
#include "Intrinsic/RectangularMul.hpp"
#endif

namespace sel::utils {

	/// @brief Retained small kernels whose measurements did not justify removal.
	/// Three-column kernels and longer two-column dots use compiler-optimized loops.
	template <class T, std::size_t Rows, std::size_t Inner, std::size_t Columns>
	inline constexpr bool matrixHasSmallSimd = (std::is_same_v<T, float> || std::is_same_v<T, int>)
		&& Rows >= 2 && Rows <= 4 && Inner >= 2 && Inner <= 4
		&& (Columns == 4 || (Columns == 2 && (Inner == 2
			|| (std::is_same_v<T, float> && Inner == 4 && Rows < 4))));

	/// @brief Whether a product shape/type has an explicit SIMD path.
	/// This describes eligibility independently of the backend build switch.
	template <class T, std::size_t Rows, std::size_t Inner, std::size_t Columns>
	inline constexpr bool matrixHasSimd = std::is_same_v<T, std::int8_t>
		|| ((std::is_same_v<T, float> || std::is_same_v<T, int>) && Columns >= 4)
		|| matrixHasSmallSimd<T, Rows, Inner, Columns>
		|| (std::is_same_v<T, Int4> && Inner % 2 == 0 && Columns % 2 == 0 && Columns >= 4);

	/// @brief Multiply distinct matrices, preserving the inner-coordinate order.
	/// Int4 and int8 retain only their low four/eight bits, without saturation.
	template <class T, std::size_t Rows, std::size_t Inner, std::size_t Columns>
	inline void multiplyMatrices(Matrix<T, Rows, Columns>& dst,
		const Matrix<T, Rows, Inner>& a, const Matrix<T, Inner, Columns>& b)
	{
#ifdef SEL_INTRINSIC_MATRIX_MUL
		if constexpr (std::is_same_v<T, std::int8_t>)
		{
			mulMatrixInt8Simd<Rows, Inner, Columns>(dst, a, b);
			return;
		}
		else if constexpr (std::is_same_v<T, Int4> && Inner % 2 == 0 && Columns % 2 == 0 && Columns >= 4)
		{
			if constexpr (Rows == Inner && Inner == Columns
				&& (Rows == 4 || Rows == 8 || Rows == 16 || Rows == 32))
				mulMatrixInt4Simd<Rows>(dst, a, b);
			else
				mulMatrixInt4Rectangular<Rows, Inner, Columns>(dst, a, b);
			return;
		}
		else if constexpr (std::is_same_v<T, float> || std::is_same_v<T, int>)
		{
			if constexpr (Rows == 2 && Inner == 2 && Columns == 2)
			{
				mulMatrix_2x2_2x2(&dst[0][0], &a[0][0], &b[0][0]);
				return;
			}

			if constexpr (Rows == 2 && Inner == 2 && Columns == 4)
			{
				mulMatrix_2x2_2x4(&dst[0][0], &a[0][0], &b[0][0]);
				return;
			}

			if constexpr (Rows == 2 && Inner == 3 && Columns == 4)
			{
				mulMatrix_2x3_3x4(&dst[0][0], &a[0][0], &b[0][0]);
				return;
			}
			if constexpr (Rows == 2 && Inner == 4 && Columns == 2 && std::is_same_v<T, float>)
			{
				mulMatrix_2x4_4x2(&dst[0][0], &a[0][0], &b[0][0]);
				return;
			}

			if constexpr (Rows == 2 && Inner == 4 && Columns == 4)
			{
				mulMatrix_2x4_4x4(&dst[0][0], &a[0][0], &b[0][0]);
				return;
			}
			if constexpr (Rows == 3 && Inner == 2 && Columns == 2)
			{
				mulMatrix_3x2_2x2(&dst[0][0], &a[0][0], &b[0][0]);
				return;
			}

			if constexpr (Rows == 3 && Inner == 2 && Columns == 4)
			{
				mulMatrix_3x2_2x4(&dst[0][0], &a[0][0], &b[0][0]);
				return;
			}

			if constexpr (Rows == 3 && Inner == 3 && Columns == 4)
			{
				mulMatrix_3x3_3x4(&dst[0][0], &a[0][0], &b[0][0]);
				return;
			}
			if constexpr (Rows == 3 && Inner == 4 && Columns == 2 && std::is_same_v<T, float>)
			{
				mulMatrix_3x4_4x2(&dst[0][0], &a[0][0], &b[0][0]);
				return;
			}

			if constexpr (Rows == 3 && Inner == 4 && Columns == 4)
			{
				mulMatrix_3x4_4x4(&dst[0][0], &a[0][0], &b[0][0]);
				return;
			}
			if constexpr (Rows == 4 && Inner == 2 && Columns == 2)
			{
				mulMatrix_4x2_2x2(&dst[0][0], &a[0][0], &b[0][0]);
				return;
			}

			if constexpr (Rows == 4 && Inner == 2 && Columns == 4)
			{
				mulMatrix_4x2_2x4(&dst[0][0], &a[0][0], &b[0][0]);
				return;
			}

			if constexpr (Rows == 4 && Inner == 3 && Columns == 4)
			{
				mulMatrix_4x3_3x4(&dst[0][0], &a[0][0], &b[0][0]);
				return;
			}

			if constexpr (Rows == 4 && Inner == 4 && Columns == 4)
			{
				mulMatrix_4x4_4x4(&dst[0][0], &a[0][0], &b[0][0]);
				return;
			}
			if constexpr (Columns >= 4)
			{
				mulMatrixRectangular<Rows, Inner, Columns>(dst, a, b);
				return;
			}
		}
#endif
		for (std::size_t row = 0; row < Rows; ++row)
		{
			for (std::size_t column = 0; column < Columns; ++column)
			{
				if constexpr (std::is_same_v<T, Int4> || std::is_same_v<T, std::int8_t>)
				{
					// Reduce every term so arbitrary dot-product lengths cannot
					// overflow a signed accumulator. Unsigned arithmetic is modular.
					constexpr unsigned int mask = std::is_same_v<T, Int4> ? 15u : 255u;
					unsigned int value = 0;
					for (std::size_t inner = 0; inner < Inner; ++inner)
						value = (value + static_cast<unsigned int>(int(a[row][inner]) * int(b[inner][column]))) & mask;
					if constexpr (std::is_same_v<T, Int4>)
						dst[row][column] = Int4(value);
					else
						dst[row][column] = static_cast<std::int8_t>(value < 128u ? int(value) : int(value) - 256);
				}
				else
				{
					dst[row][column] = a[row][0] * b[0][column];
					for (std::size_t inner = 1; inner < Inner; ++inner)
						dst[row][column] += a[row][inner] * b[inner][column];
				}
			}
		}
	}
}

namespace sel {

	/// @brief Multiply Rows x Inner by Inner x Columns, returning Rows x Columns.
	/// Dimensions are checked by deduction; operands must have the same value type.
	/// Define SEL_INTRINSIC_MATRIX_MUL with SSE4.1 enabled to select SIMD kernels.
	/// Ordinary signed integers require representable intermediate arithmetic.
	template <class T, std::size_t Rows, std::size_t Inner, std::size_t Columns>
	inline Matrix<T, Rows, Columns> operator*(const Matrix<T, Rows, Inner>& lhs,
		const Matrix<T, Inner, Columns>& rhs)
	{
		Matrix<T, Rows, Columns> result(utils::UninitializedMatrixTag{});
		utils::multiplyMatrices(result, lhs, rhs);
		return result;
	}
}
