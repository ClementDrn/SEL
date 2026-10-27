#pragma once

#include <type_traits>
#include <cstddef>
#include <cstdint>

#include "Mat8x8.hpp"
#include "Mat16x16.hpp"
#include "Mat32x32.hpp"

#include "Mat4x4.hpp"
#include "Mat4x3.hpp"
#include "Mat4x2.hpp"

#include "Mat3x4.hpp"
#include "Mat3x3.hpp"
#include "Mat3x2.hpp"

#include "Mat2x4.hpp"
#include "Mat2x3.hpp"
#include "Mat2x2.hpp"

#ifdef SEL_INTRINSIC_MATRIX_MUL
	#include "SEL/Maths/Matrices/Intrinsic/Int32Mul.hpp"
	#include "SEL/Maths/Matrices/Intrinsic/Float32Mul.hpp"
	#include "SEL/Maths/Matrices/Intrinsic/Int8Mul.hpp"
	#include "SEL/Maths/Matrices/Intrinsic/Int4Mul.hpp"
#endif


namespace sel::utils {

	/// @brief Multiply packed int4 matrices, wrapping each result modulo 16.
	/// Selected square sizes use SIMD when the intrinsic backend is enabled.
	template <std::size_t Rows, std::size_t Inner, std::size_t Columns, class Product, class Left, class Right>
	inline void mulMatrixInt4(Product& dst, const Left& a, const Right& b)
	{
#ifdef SEL_INTRINSIC_MATRIX_MUL
		if constexpr (Rows == Inner && Inner == Columns
			&& (Rows == 4 || Rows == 8 || Rows == 16 || Rows == 32))
		{
			mulMatrixInt4Simd<Rows>(dst, a, b);
			return;
		}
#endif
		// Current shapes have at most 32 terms, each with magnitude at most 64.
		static_assert(Inner <= 32, "Review int4 accumulator bounds for larger shapes");
		for (std::size_t row = 0; row < Rows; ++row)
		{
			for (std::size_t column = 0; column < Columns; ++column)
			{
				int value = 0;
				for (std::size_t inner = 0; inner < Inner; ++inner)
				{
					value += int(a[row][inner]) * int(b[inner][column]);
				}
				dst[row][column] = Int4(value);
			}
		}
	}

	/// @brief Multiply signed byte matrices using the configured backend.
	///
	/// Products wrap to the signed 8-bit range, without saturation.
	///
	/// @tparam Rows is the number of rows of the result.
	/// @tparam Inner is the number of values in each dot product.
	/// @tparam Columns is the number of columns of the result.
	/// @param dst is the destination matrix, distinct from both inputs.
	/// @param a is the first matrix.
	/// @param b is the second matrix.
	///
	template <std::size_t Rows, std::size_t Inner, std::size_t Columns, class Product, class Left, class Right>
	inline void mulMatrixInt8(Product& dst, const Left& a, const Right& b)
	{
#ifdef SEL_INTRINSIC_MATRIX_MUL
		// Widen signed bytes for SIMD products, then retain the low eight bits.
		mulMatrixInt8Simd<Rows, Inner, Columns>(dst, a, b);
#else
		// Accumulate in int so intermediate products never overflow signed bytes.
		for (std::size_t row = 0; row < Rows; ++row)
		{
			for (std::size_t column = 0; column < Columns; ++column)
			{
				int value = 0;
				for (std::size_t inner = 0; inner < Inner; ++inner)
				{
					value += int(a[row][inner]) * int(b[inner][column]);
				}

				// Wrap to [-128, 127] without an out-of-range signed conversion.
				const unsigned int lowByte = static_cast<unsigned int>(value) & 0xffu;
				dst[row][column] = static_cast<std::int8_t>(lowByte < 128u ? int(lowByte) : int(lowByte) - 256);
			}
		}
#endif
	}

}


namespace sel {

	// --- 4x4 result ----------------------------------------------------------

	/// @brief Overload of * binary arithmetic operator.
	///
	/// @tparam T is the type of the matrices' values.
	/// @param lhs is the first matrix.
	/// @param rhs is the second matrix.
	/// 
	/// @return The matrix resulted by the multiplication of the two provided matrices.
	/// 
	template <class T>
	inline Mat4x4<T> operator*(const Mat4x4<T>& lhs, const Mat4x4<T>& rhs)
	{
		Mat4x4<T> result;

		if constexpr (std::is_same_v<T, Int4>)
		{
			utils::mulMatrixInt4<4, 4, 4>(result, lhs, rhs);
			return result;
		}

		if constexpr (std::is_same_v<T, std::int8_t>)
		{
			utils::mulMatrixInt8<4, 4, 4>(result, lhs, rhs);
			return result;
		}

#ifdef SEL_INTRINSIC_MATRIX_MUL
		// Select the 32-bit float and integer intrinsic backends.
		if constexpr (std::is_same_v<T, float>)
		{
			utils::mulMatrix_4x4_4x4((float*)&result, (float*)&lhs, (float*)&rhs);
			return result;
		}
		else if constexpr (std::is_same_v<T, int>)
		{
			utils::mulMatrix_4x4_4x4((int*)&result, (int*)&lhs, (int*)&rhs);
			return result;
		}
#endif

		// Normal multiplication
		// First row
		result[0][0] = lhs[0][0] * rhs[0][0] + lhs[0][1] * rhs[1][0] + lhs[0][2] * rhs[2][0] + lhs[0][3] * rhs[3][0];
		result[0][1] = lhs[0][0] * rhs[0][1] + lhs[0][1] * rhs[1][1] + lhs[0][2] * rhs[2][1] + lhs[0][3] * rhs[3][1];
		result[0][2] = lhs[0][0] * rhs[0][2] + lhs[0][1] * rhs[1][2] + lhs[0][2] * rhs[2][2] + lhs[0][3] * rhs[3][2];
		result[0][3] = lhs[0][0] * rhs[0][3] + lhs[0][1] * rhs[1][3] + lhs[0][2] * rhs[2][3] + lhs[0][3] * rhs[3][3];

		// Second row
		result[1][0] = lhs[1][0] * rhs[0][0] + lhs[1][1] * rhs[1][0] + lhs[1][2] * rhs[2][0] + lhs[1][3] * rhs[3][0];
		result[1][1] = lhs[1][0] * rhs[0][1] + lhs[1][1] * rhs[1][1] + lhs[1][2] * rhs[2][1] + lhs[1][3] * rhs[3][1];
		result[1][2] = lhs[1][0] * rhs[0][2] + lhs[1][1] * rhs[1][2] + lhs[1][2] * rhs[2][2] + lhs[1][3] * rhs[3][2];
		result[1][3] = lhs[1][0] * rhs[0][3] + lhs[1][1] * rhs[1][3] + lhs[1][2] * rhs[2][3] + lhs[1][3] * rhs[3][3];

		// Third row
		result[2][0] = lhs[2][0] * rhs[0][0] + lhs[2][1] * rhs[1][0] + lhs[2][2] * rhs[2][0] + lhs[2][3] * rhs[3][0];
		result[2][1] = lhs[2][0] * rhs[0][1] + lhs[2][1] * rhs[1][1] + lhs[2][2] * rhs[2][1] + lhs[2][3] * rhs[3][1];
		result[2][2] = lhs[2][0] * rhs[0][2] + lhs[2][1] * rhs[1][2] + lhs[2][2] * rhs[2][2] + lhs[2][3] * rhs[3][2];
		result[2][3] = lhs[2][0] * rhs[0][3] + lhs[2][1] * rhs[1][3] + lhs[2][2] * rhs[2][3] + lhs[2][3] * rhs[3][3];

		// Fourth row
		result[3][0] = lhs[3][0] * rhs[0][0] + lhs[3][1] * rhs[1][0] + lhs[3][2] * rhs[2][0] + lhs[3][3] * rhs[3][0];
		result[3][1] = lhs[3][0] * rhs[0][1] + lhs[3][1] * rhs[1][1] + lhs[3][2] * rhs[2][1] + lhs[3][3] * rhs[3][1];
		result[3][2] = lhs[3][0] * rhs[0][2] + lhs[3][1] * rhs[1][2] + lhs[3][2] * rhs[2][2] + lhs[3][3] * rhs[3][2];
		result[3][3] = lhs[3][0] * rhs[0][3] + lhs[3][1] * rhs[1][3] + lhs[3][2] * rhs[2][3] + lhs[3][3] * rhs[3][3];

		return result;
	}

	/// @brief Overload of * binary arithmetic operator.
	///
	/// @tparam T is the type of the matrices' values.
	/// @param lhs is the first matrix.
	/// @param rhs is the second matrix.
	/// 
	/// @return The matrix resulted by the multiplication of the two provided matrices.
	/// 
	template <class T>
	inline Mat4x4<T> operator*(const Mat4x3<T>& lhs, const Mat3x4<T>& rhs)
	{
		Mat4x4<T> result;

		if constexpr (std::is_same_v<T, Int4>)
		{
			utils::mulMatrixInt4<4, 3, 4>(result, lhs, rhs);
			return result;
		}

		if constexpr (std::is_same_v<T, std::int8_t>)
		{
			utils::mulMatrixInt8<4, 3, 4>(result, lhs, rhs);
			return result;
		}

#ifdef SEL_INTRINSIC_MATRIX_MUL
		// Select the 32-bit float and integer intrinsic backends.
		if constexpr (std::is_same_v<T, float>)
		{
			utils::mulMatrix_4x3_3x4((float*)&result, (float*)&lhs, (float*)&rhs);
			return result;
		}
		else if constexpr (std::is_same_v<T, int>)
		{
			utils::mulMatrix_4x3_3x4((int*)&result, (int*)&lhs, (int*)&rhs);
			return result;
		}
#endif

		// Normal multiplication
		// First row
		result[0][0] = lhs[0][0] * rhs[0][0] + lhs[0][1] * rhs[1][0] + lhs[0][2] * rhs[2][0];
		result[0][1] = lhs[0][0] * rhs[0][1] + lhs[0][1] * rhs[1][1] + lhs[0][2] * rhs[2][1];
		result[0][2] = lhs[0][0] * rhs[0][2] + lhs[0][1] * rhs[1][2] + lhs[0][2] * rhs[2][2];
		result[0][3] = lhs[0][0] * rhs[0][3] + lhs[0][1] * rhs[1][3] + lhs[0][2] * rhs[2][3];

		// Second row
		result[1][0] = lhs[1][0] * rhs[0][0] + lhs[1][1] * rhs[1][0] + lhs[1][2] * rhs[2][0];
		result[1][1] = lhs[1][0] * rhs[0][1] + lhs[1][1] * rhs[1][1] + lhs[1][2] * rhs[2][1];
		result[1][2] = lhs[1][0] * rhs[0][2] + lhs[1][1] * rhs[1][2] + lhs[1][2] * rhs[2][2];
		result[1][3] = lhs[1][0] * rhs[0][3] + lhs[1][1] * rhs[1][3] + lhs[1][2] * rhs[2][3];

		// Third row
		result[2][0] = lhs[2][0] * rhs[0][0] + lhs[2][1] * rhs[1][0] + lhs[2][2] * rhs[2][0];
		result[2][1] = lhs[2][0] * rhs[0][1] + lhs[2][1] * rhs[1][1] + lhs[2][2] * rhs[2][1];
		result[2][2] = lhs[2][0] * rhs[0][2] + lhs[2][1] * rhs[1][2] + lhs[2][2] * rhs[2][2];
		result[2][3] = lhs[2][0] * rhs[0][3] + lhs[2][1] * rhs[1][3] + lhs[2][2] * rhs[2][3];

		// Fourth row
		result[3][0] = lhs[3][0] * rhs[0][0] + lhs[3][1] * rhs[1][0] + lhs[3][2] * rhs[2][0];
		result[3][1] = lhs[3][0] * rhs[0][1] + lhs[3][1] * rhs[1][1] + lhs[3][2] * rhs[2][1];
		result[3][2] = lhs[3][0] * rhs[0][2] + lhs[3][1] * rhs[1][2] + lhs[3][2] * rhs[2][2];
		result[3][3] = lhs[3][0] * rhs[0][3] + lhs[3][1] * rhs[1][3] + lhs[3][2] * rhs[2][3];

		return result;
	}

	/// @brief Overload of * binary arithmetic operator.
	///
	/// @tparam T is the type of the matrices' values.
	/// @param lhs is the first matrix.
	/// @param rhs is the second matrix.
	/// 
	/// @return The matrix resulted by the multiplication of the two provided matrices.
	/// 
	template <class T>
	inline Mat4x4<T> operator*(const Mat4x2<T>& lhs, const Mat2x4<T>& rhs)
	{
		Mat4x4<T> result;

		if constexpr (std::is_same_v<T, Int4>)
		{
			utils::mulMatrixInt4<4, 2, 4>(result, lhs, rhs);
			return result;
		}

		if constexpr (std::is_same_v<T, std::int8_t>)
		{
			utils::mulMatrixInt8<4, 2, 4>(result, lhs, rhs);
			return result;
		}

#ifdef SEL_INTRINSIC_MATRIX_MUL
		// Select the 32-bit float and integer intrinsic backends.
		if constexpr (std::is_same_v<T, float>)
		{
			utils::mulMatrix_4x2_2x4((float*)&result, (float*)&lhs, (float*)&rhs);
			return result;
		}
		else if constexpr (std::is_same_v<T, int>)
		{
			utils::mulMatrix_4x2_2x4((int*)&result, (int*)&lhs, (int*)&rhs);
			return result;
		}
#endif

		// Normal multiplication
		// First row
		result[0][0] = lhs[0][0] * rhs[0][0] + lhs[0][1] * rhs[1][0];
		result[0][1] = lhs[0][0] * rhs[0][1] + lhs[0][1] * rhs[1][1];
		result[0][2] = lhs[0][0] * rhs[0][2] + lhs[0][1] * rhs[1][2];
		result[0][3] = lhs[0][0] * rhs[0][3] + lhs[0][1] * rhs[1][3];

		// Second row
		result[1][0] = lhs[1][0] * rhs[0][0] + lhs[1][1] * rhs[1][0];
		result[1][1] = lhs[1][0] * rhs[0][1] + lhs[1][1] * rhs[1][1];
		result[1][2] = lhs[1][0] * rhs[0][2] + lhs[1][1] * rhs[1][2];
		result[1][3] = lhs[1][0] * rhs[0][3] + lhs[1][1] * rhs[1][3];

		// Third row
		result[2][0] = lhs[2][0] * rhs[0][0] + lhs[2][1] * rhs[1][0];
		result[2][1] = lhs[2][0] * rhs[0][1] + lhs[2][1] * rhs[1][1];
		result[2][2] = lhs[2][0] * rhs[0][2] + lhs[2][1] * rhs[1][2];
		result[2][3] = lhs[2][0] * rhs[0][3] + lhs[2][1] * rhs[1][3];

		// Fourth row
		result[3][0] = lhs[3][0] * rhs[0][0] + lhs[3][1] * rhs[1][0];
		result[3][1] = lhs[3][0] * rhs[0][1] + lhs[3][1] * rhs[1][1];
		result[3][2] = lhs[3][0] * rhs[0][2] + lhs[3][1] * rhs[1][2];
		result[3][3] = lhs[3][0] * rhs[0][3] + lhs[3][1] * rhs[1][3];

		return result;
	}


	// --- 4x3 result ----------------------------------------------------------

	/// @brief Overload of * binary arithmetic operator.
	///
	/// @tparam T is the type of the matrices' values.
	/// @param lhs is the first matrix.
	/// @param rhs is the second matrix.
	/// 
	/// @return The matrix resulted by the multiplication of the two provided matrices.
	/// 
	template <class T>
	inline Mat4x3<T> operator*(const Mat4x4<T>& lhs, const Mat4x3<T>& rhs)
	{
		Mat4x3<T> result;

		if constexpr (std::is_same_v<T, Int4>)
		{
			utils::mulMatrixInt4<4, 4, 3>(result, lhs, rhs);
			return result;
		}

		if constexpr (std::is_same_v<T, std::int8_t>)
		{
			utils::mulMatrixInt8<4, 4, 3>(result, lhs, rhs);
			return result;
		}

#ifdef SEL_INTRINSIC_MATRIX_MUL
		// Select the 32-bit float and integer intrinsic backends.
		if constexpr (std::is_same_v<T, float>)
		{
			utils::mulMatrix_4x4_4x3((float*)&result, (float*)&lhs, (float*)&rhs);
			return result;
		}
		else if constexpr (std::is_same_v<T, int>)
		{
			utils::mulMatrix_4x4_4x3((int*)&result, (int*)&lhs, (int*)&rhs);
			return result;
		}
#endif

		// Normal multiplication
		// First row
		result[0][0] = lhs[0][0] * rhs[0][0] + lhs[0][1] * rhs[1][0] + lhs[0][2] * rhs[2][0] + lhs[0][3] * rhs[3][0];
		result[0][1] = lhs[0][0] * rhs[0][1] + lhs[0][1] * rhs[1][1] + lhs[0][2] * rhs[2][1] + lhs[0][3] * rhs[3][1];
		result[0][2] = lhs[0][0] * rhs[0][2] + lhs[0][1] * rhs[1][2] + lhs[0][2] * rhs[2][2] + lhs[0][3] * rhs[3][2];

		// Second row
		result[1][0] = lhs[1][0] * rhs[0][0] + lhs[1][1] * rhs[1][0] + lhs[1][2] * rhs[2][0] + lhs[1][3] * rhs[3][0];
		result[1][1] = lhs[1][0] * rhs[0][1] + lhs[1][1] * rhs[1][1] + lhs[1][2] * rhs[2][1] + lhs[1][3] * rhs[3][1];
		result[1][2] = lhs[1][0] * rhs[0][2] + lhs[1][1] * rhs[1][2] + lhs[1][2] * rhs[2][2] + lhs[1][3] * rhs[3][2];

		// Third row
		result[2][0] = lhs[2][0] * rhs[0][0] + lhs[2][1] * rhs[1][0] + lhs[2][2] * rhs[2][0] + lhs[2][3] * rhs[3][0];
		result[2][1] = lhs[2][0] * rhs[0][1] + lhs[2][1] * rhs[1][1] + lhs[2][2] * rhs[2][1] + lhs[2][3] * rhs[3][1];
		result[2][2] = lhs[2][0] * rhs[0][2] + lhs[2][1] * rhs[1][2] + lhs[2][2] * rhs[2][2] + lhs[2][3] * rhs[3][2];

		// Fourth row
		result[3][0] = lhs[3][0] * rhs[0][0] + lhs[3][1] * rhs[1][0] + lhs[3][2] * rhs[2][0] + lhs[3][3] * rhs[3][0];
		result[3][1] = lhs[3][0] * rhs[0][1] + lhs[3][1] * rhs[1][1] + lhs[3][2] * rhs[2][1] + lhs[3][3] * rhs[3][1];
		result[3][2] = lhs[3][0] * rhs[0][2] + lhs[3][1] * rhs[1][2] + lhs[3][2] * rhs[2][2] + lhs[3][3] * rhs[3][2];

		return result;
	}

	/// @brief Overload of * binary arithmetic operator.
	///
	/// @tparam T is the type of the matrices' values.
	/// @param lhs is the first matrix.
	/// @param rhs is the second matrix.
	/// 
	/// @return The matrix resulted by the multiplication of the two provided matrices.
	/// 
	template <class T>
	inline Mat4x3<T> operator*(const Mat4x3<T>& lhs, const Mat3x3<T>& rhs)
	{
		Mat4x3<T> result;

		if constexpr (std::is_same_v<T, Int4>)
		{
			utils::mulMatrixInt4<4, 3, 3>(result, lhs, rhs);
			return result;
		}

		if constexpr (std::is_same_v<T, std::int8_t>)
		{
			utils::mulMatrixInt8<4, 3, 3>(result, lhs, rhs);
			return result;
		}

#ifdef SEL_INTRINSIC_MATRIX_MUL
		// Select the 32-bit float and integer intrinsic backends.
		if constexpr (std::is_same_v<T, float>)
		{
			utils::mulMatrix_4x3_3x3((float*)&result, (float*)&lhs, (float*)&rhs);
			return result;
		}
		else if constexpr (std::is_same_v<T, int>)
		{
			utils::mulMatrix_4x3_3x3((int*)&result, (int*)&lhs, (int*)&rhs);
			return result;
		}
#endif

		// Normal multiplication
		// First row
		result[0][0] = lhs[0][0] * rhs[0][0] + lhs[0][1] * rhs[1][0] + lhs[0][2] * rhs[2][0];
		result[0][1] = lhs[0][0] * rhs[0][1] + lhs[0][1] * rhs[1][1] + lhs[0][2] * rhs[2][1];
		result[0][2] = lhs[0][0] * rhs[0][2] + lhs[0][1] * rhs[1][2] + lhs[0][2] * rhs[2][2];

		// Second row
		result[1][0] = lhs[1][0] * rhs[0][0] + lhs[1][1] * rhs[1][0] + lhs[1][2] * rhs[2][0];
		result[1][1] = lhs[1][0] * rhs[0][1] + lhs[1][1] * rhs[1][1] + lhs[1][2] * rhs[2][1];
		result[1][2] = lhs[1][0] * rhs[0][2] + lhs[1][1] * rhs[1][2] + lhs[1][2] * rhs[2][2];

		// Third row
		result[2][0] = lhs[2][0] * rhs[0][0] + lhs[2][1] * rhs[1][0] + lhs[2][2] * rhs[2][0];
		result[2][1] = lhs[2][0] * rhs[0][1] + lhs[2][1] * rhs[1][1] + lhs[2][2] * rhs[2][1];
		result[2][2] = lhs[2][0] * rhs[0][2] + lhs[2][1] * rhs[1][2] + lhs[2][2] * rhs[2][2];

		// Fourth row
		result[3][0] = lhs[3][0] * rhs[0][0] + lhs[3][1] * rhs[1][0] + lhs[3][2] * rhs[2][0];
		result[3][1] = lhs[3][0] * rhs[0][1] + lhs[3][1] * rhs[1][1] + lhs[3][2] * rhs[2][1];
		result[3][2] = lhs[3][0] * rhs[0][2] + lhs[3][1] * rhs[1][2] + lhs[3][2] * rhs[2][2];

		return result;
	}

	/// @brief Overload of * binary arithmetic operator.
	///
	/// @tparam T is the type of the matrices' values.
	/// @param lhs is the first matrix.
	/// @param rhs is the second matrix.
	/// 
	/// @return The matrix resulted by the multiplication of the two provided matrices.
	/// 
	template <class T>
	inline Mat4x3<T> operator*(const Mat4x2<T>& lhs, const Mat2x3<T>& rhs)
	{
		Mat4x3<T> result;

		if constexpr (std::is_same_v<T, Int4>)
		{
			utils::mulMatrixInt4<4, 2, 3>(result, lhs, rhs);
			return result;
		}

		if constexpr (std::is_same_v<T, std::int8_t>)
		{
			utils::mulMatrixInt8<4, 2, 3>(result, lhs, rhs);
			return result;
		}

#ifdef SEL_INTRINSIC_MATRIX_MUL
		// Select the 32-bit float and integer intrinsic backends.
		if constexpr (std::is_same_v<T, float>)
		{
			utils::mulMatrix_4x2_2x3((float*)&result, (float*)&lhs, (float*)&rhs);
			return result;
		}
		else if constexpr (std::is_same_v<T, int>)
		{
			utils::mulMatrix_4x2_2x3((int*)&result, (int*)&lhs, (int*)&rhs);
			return result;
		}
#endif

		// Normal multiplication
		// First row
		result[0][0] = lhs[0][0] * rhs[0][0] + lhs[0][1] * rhs[1][0];
		result[0][1] = lhs[0][0] * rhs[0][1] + lhs[0][1] * rhs[1][1];
		result[0][2] = lhs[0][0] * rhs[0][2] + lhs[0][1] * rhs[1][2];

		// Second row
		result[1][0] = lhs[1][0] * rhs[0][0] + lhs[1][1] * rhs[1][0];
		result[1][1] = lhs[1][0] * rhs[0][1] + lhs[1][1] * rhs[1][1];
		result[1][2] = lhs[1][0] * rhs[0][2] + lhs[1][1] * rhs[1][2];

		// Third row
		result[2][0] = lhs[2][0] * rhs[0][0] + lhs[2][1] * rhs[1][0];
		result[2][1] = lhs[2][0] * rhs[0][1] + lhs[2][1] * rhs[1][1];
		result[2][2] = lhs[2][0] * rhs[0][2] + lhs[2][1] * rhs[1][2];

		// Fourth row
		result[3][0] = lhs[3][0] * rhs[0][0] + lhs[3][1] * rhs[1][0];
		result[3][1] = lhs[3][0] * rhs[0][1] + lhs[3][1] * rhs[1][1];
		result[3][2] = lhs[3][0] * rhs[0][2] + lhs[3][1] * rhs[1][2];

		return result;
	}


	// --- 4x2 result ----------------------------------------------------------

	/// @brief Overload of * binary arithmetic operator.
	///
	/// @tparam T is the type of the matrices' values.
	/// @param lhs is the first matrix.
	/// @param rhs is the second matrix.
	/// 
	/// @return The matrix resulted by the multiplication of the two provided matrices.
	/// 
	template <class T>
	inline Mat4x2<T> operator*(const Mat4x4<T>& lhs, const Mat4x2<T>& rhs)
	{
		Mat4x2<T> result;

		if constexpr (std::is_same_v<T, Int4>)
		{
			utils::mulMatrixInt4<4, 4, 2>(result, lhs, rhs);
			return result;
		}

		if constexpr (std::is_same_v<T, std::int8_t>)
		{
			utils::mulMatrixInt8<4, 4, 2>(result, lhs, rhs);
			return result;
		}

#ifdef SEL_INTRINSIC_MATRIX_MUL
		// Select the 32-bit float and integer intrinsic backends.
		if constexpr (std::is_same_v<T, float>)
		{
			utils::mulMatrix_4x4_4x2((float*)&result, (float*)&lhs, (float*)&rhs);
			return result;
		}
		else if constexpr (std::is_same_v<T, int>)
		{
			utils::mulMatrix_4x4_4x2((int*)&result, (int*)&lhs, (int*)&rhs);
			return result;
		}
#endif

		// Normal multiplication
		// First row
		result[0][0] = lhs[0][0] * rhs[0][0] + lhs[0][1] * rhs[1][0] + lhs[0][2] * rhs[2][0] + lhs[0][3] * rhs[3][0];
		result[0][1] = lhs[0][0] * rhs[0][1] + lhs[0][1] * rhs[1][1] + lhs[0][2] * rhs[2][1] + lhs[0][3] * rhs[3][1];

		// Second row
		result[1][0] = lhs[1][0] * rhs[0][0] + lhs[1][1] * rhs[1][0] + lhs[1][2] * rhs[2][0] + lhs[1][3] * rhs[3][0];
		result[1][1] = lhs[1][0] * rhs[0][1] + lhs[1][1] * rhs[1][1] + lhs[1][2] * rhs[2][1] + lhs[1][3] * rhs[3][1];

		// Third row
		result[2][0] = lhs[2][0] * rhs[0][0] + lhs[2][1] * rhs[1][0] + lhs[2][2] * rhs[2][0] + lhs[2][3] * rhs[3][0];
		result[2][1] = lhs[2][0] * rhs[0][1] + lhs[2][1] * rhs[1][1] + lhs[2][2] * rhs[2][1] + lhs[2][3] * rhs[3][1];

		// Fourth row
		result[3][0] = lhs[3][0] * rhs[0][0] + lhs[3][1] * rhs[1][0] + lhs[3][2] * rhs[2][0] + lhs[3][3] * rhs[3][0];
		result[3][1] = lhs[3][0] * rhs[0][1] + lhs[3][1] * rhs[1][1] + lhs[3][2] * rhs[2][1] + lhs[3][3] * rhs[3][1];

		return result;
	}

	/// @brief Overload of * binary arithmetic operator.
	///
	/// @tparam T is the type of the matrices' values.
	/// @param lhs is the first matrix.
	/// @param rhs is the second matrix.
	/// 
	/// @return The matrix resulted by the multiplication of the two provided matrices.
	/// 
	template <class T>
	inline Mat4x2<T> operator*(const Mat4x3<T>& lhs, const Mat3x2<T>& rhs)
	{
		Mat4x2<T> result;

		if constexpr (std::is_same_v<T, Int4>)
		{
			utils::mulMatrixInt4<4, 3, 2>(result, lhs, rhs);
			return result;
		}

		if constexpr (std::is_same_v<T, std::int8_t>)
		{
			utils::mulMatrixInt8<4, 3, 2>(result, lhs, rhs);
			return result;
		}

#ifdef SEL_INTRINSIC_MATRIX_MUL
		// Select the 32-bit float and integer intrinsic backends.
		if constexpr (std::is_same_v<T, float>)
		{
			utils::mulMatrix_4x3_3x2((float*)&result, (float*)&lhs, (float*)&rhs);
			return result;
		}
		else if constexpr (std::is_same_v<T, int>)
		{
			utils::mulMatrix_4x3_3x2((int*)&result, (int*)&lhs, (int*)&rhs);
			return result;
		}
#endif

		// Normal multiplication
		// First row
		result[0][0] = lhs[0][0] * rhs[0][0] + lhs[0][1] * rhs[1][0] + lhs[0][2] * rhs[2][0];
		result[0][1] = lhs[0][0] * rhs[0][1] + lhs[0][1] * rhs[1][1] + lhs[0][2] * rhs[2][1];

		// Second row
		result[1][0] = lhs[1][0] * rhs[0][0] + lhs[1][1] * rhs[1][0] + lhs[1][2] * rhs[2][0];
		result[1][1] = lhs[1][0] * rhs[0][1] + lhs[1][1] * rhs[1][1] + lhs[1][2] * rhs[2][1];

		// Third row
		result[2][0] = lhs[2][0] * rhs[0][0] + lhs[2][1] * rhs[1][0] + lhs[2][2] * rhs[2][0];
		result[2][1] = lhs[2][0] * rhs[0][1] + lhs[2][1] * rhs[1][1] + lhs[2][2] * rhs[2][1];

		// Fourth row
		result[3][0] = lhs[3][0] * rhs[0][0] + lhs[3][1] * rhs[1][0] + lhs[3][2] * rhs[2][0];
		result[3][1] = lhs[3][0] * rhs[0][1] + lhs[3][1] * rhs[1][1] + lhs[3][2] * rhs[2][1];

		return result;
	}

	/// @brief Overload of * binary arithmetic operator.
	///
	/// @tparam T is the type of the matrices' values.
	/// @param lhs is the first matrix.
	/// @param rhs is the second matrix.
	/// 
	/// @return The matrix resulted by the multiplication of the two provided matrices.
	/// 
	template <class T>
	inline Mat4x2<T> operator*(const Mat4x2<T>& lhs, const Mat2x2<T>& rhs)
	{
		Mat4x2<T> result;

		if constexpr (std::is_same_v<T, Int4>)
		{
			utils::mulMatrixInt4<4, 2, 2>(result, lhs, rhs);
			return result;
		}

		if constexpr (std::is_same_v<T, std::int8_t>)
		{
			utils::mulMatrixInt8<4, 2, 2>(result, lhs, rhs);
			return result;
		}

#ifdef SEL_INTRINSIC_MATRIX_MUL
		// Select the 32-bit float and integer intrinsic backends.
		if constexpr (std::is_same_v<T, float>)
		{
			utils::mulMatrix_4x2_2x2((float*)&result, (float*)&lhs, (float*)&rhs);
			return result;
		}
		else if constexpr (std::is_same_v<T, int>)
		{
			utils::mulMatrix_4x2_2x2((int*)&result, (int*)&lhs, (int*)&rhs);
			return result;
		}
#endif

		// Normal multiplication
		// First row
		result[0][0] = lhs[0][0] * rhs[0][0] + lhs[0][1] * rhs[1][0];
		result[0][1] = lhs[0][0] * rhs[0][1] + lhs[0][1] * rhs[1][1];

		// Second row
		result[1][0] = lhs[1][0] * rhs[0][0] + lhs[1][1] * rhs[1][0];
		result[1][1] = lhs[1][0] * rhs[0][1] + lhs[1][1] * rhs[1][1];

		// Third row
		result[2][0] = lhs[2][0] * rhs[0][0] + lhs[2][1] * rhs[1][0];
		result[2][1] = lhs[2][0] * rhs[0][1] + lhs[2][1] * rhs[1][1];

		// Fourth row
		result[3][0] = lhs[3][0] * rhs[0][0] + lhs[3][1] * rhs[1][0];
		result[3][1] = lhs[3][0] * rhs[0][1] + lhs[3][1] * rhs[1][1];

		return result;
	}


	// --- 3x4 result ----------------------------------------------------------

	/// @brief Overload of * binary arithmetic operator.
	///
	/// @tparam T is the type of the matrices' values.
	/// @param lhs is the first matrix.
	/// @param rhs is the second matrix.
	/// 
	/// @return The matrix resulted by the multiplication of the two provided matrices.
	/// 
	template <class T>
	inline Mat3x4<T> operator*(const Mat3x4<T>& lhs, const Mat4x4<T>& rhs)
	{
		Mat3x4<T> result;

		if constexpr (std::is_same_v<T, Int4>)
		{
			utils::mulMatrixInt4<3, 4, 4>(result, lhs, rhs);
			return result;
		}

		if constexpr (std::is_same_v<T, std::int8_t>)
		{
			utils::mulMatrixInt8<3, 4, 4>(result, lhs, rhs);
			return result;
		}

#ifdef SEL_INTRINSIC_MATRIX_MUL
		// Select the 32-bit float and integer intrinsic backends.
		if constexpr (std::is_same_v<T, float>)
		{
			utils::mulMatrix_3x4_4x4((float*)&result, (float*)&lhs, (float*)&rhs);
			return result;
		}
		else if constexpr (std::is_same_v<T, int>)
		{
			utils::mulMatrix_3x4_4x4((int*)&result, (int*)&lhs, (int*)&rhs);
			return result;
		}
#endif

		// Normal multiplication
		// First row
		result[0][0] = lhs[0][0] * rhs[0][0] + lhs[0][1] * rhs[1][0] + lhs[0][2] * rhs[2][0] + lhs[0][3] * rhs[3][0];
		result[0][1] = lhs[0][0] * rhs[0][1] + lhs[0][1] * rhs[1][1] + lhs[0][2] * rhs[2][1] + lhs[0][3] * rhs[3][1];
		result[0][2] = lhs[0][0] * rhs[0][2] + lhs[0][1] * rhs[1][2] + lhs[0][2] * rhs[2][2] + lhs[0][3] * rhs[3][2];
		result[0][3] = lhs[0][0] * rhs[0][3] + lhs[0][1] * rhs[1][3] + lhs[0][2] * rhs[2][3] + lhs[0][3] * rhs[3][3];

		// Second row
		result[1][0] = lhs[1][0] * rhs[0][0] + lhs[1][1] * rhs[1][0] + lhs[1][2] * rhs[2][0] + lhs[1][3] * rhs[3][0];
		result[1][1] = lhs[1][0] * rhs[0][1] + lhs[1][1] * rhs[1][1] + lhs[1][2] * rhs[2][1] + lhs[1][3] * rhs[3][1];
		result[1][2] = lhs[1][0] * rhs[0][2] + lhs[1][1] * rhs[1][2] + lhs[1][2] * rhs[2][2] + lhs[1][3] * rhs[3][2];
		result[1][3] = lhs[1][0] * rhs[0][3] + lhs[1][1] * rhs[1][3] + lhs[1][2] * rhs[2][3] + lhs[1][3] * rhs[3][3];

		// Third row
		result[2][0] = lhs[2][0] * rhs[0][0] + lhs[2][1] * rhs[1][0] + lhs[2][2] * rhs[2][0] + lhs[2][3] * rhs[3][0];
		result[2][1] = lhs[2][0] * rhs[0][1] + lhs[2][1] * rhs[1][1] + lhs[2][2] * rhs[2][1] + lhs[2][3] * rhs[3][1];
		result[2][2] = lhs[2][0] * rhs[0][2] + lhs[2][1] * rhs[1][2] + lhs[2][2] * rhs[2][2] + lhs[2][3] * rhs[3][2];
		result[2][3] = lhs[2][0] * rhs[0][3] + lhs[2][1] * rhs[1][3] + lhs[2][2] * rhs[2][3] + lhs[2][3] * rhs[3][3];

		return result;
	}

	/// @brief Overload of * binary arithmetic operator.
	///
	/// @tparam T is the type of the matrices' values.
	/// @param lhs is the first matrix.
	/// @param rhs is the second matrix.
	/// 
	/// @return The matrix resulted by the multiplication of the two provided matrices.
	/// 
	template <class T>
	inline Mat3x4<T> operator*(const Mat3x3<T>& lhs, const Mat3x4<T>& rhs)
	{
		Mat3x4<T> result;

		if constexpr (std::is_same_v<T, Int4>)
		{
			utils::mulMatrixInt4<3, 3, 4>(result, lhs, rhs);
			return result;
		}

		if constexpr (std::is_same_v<T, std::int8_t>)
		{
			utils::mulMatrixInt8<3, 3, 4>(result, lhs, rhs);
			return result;
		}

#ifdef SEL_INTRINSIC_MATRIX_MUL
		// Select the 32-bit float and integer intrinsic backends.
		if constexpr (std::is_same_v<T, float>)
		{
			utils::mulMatrix_3x3_3x4((float*)&result, (float*)&lhs, (float*)&rhs);
			return result;
		}
		else if constexpr (std::is_same_v<T, int>)
		{
			utils::mulMatrix_3x3_3x4((int*)&result, (int*)&lhs, (int*)&rhs);
			return result;
		}
#endif

		// Normal multiplication
		// First row
		result[0][0] = lhs[0][0] * rhs[0][0] + lhs[0][1] * rhs[1][0] + lhs[0][2] * rhs[2][0];
		result[0][1] = lhs[0][0] * rhs[0][1] + lhs[0][1] * rhs[1][1] + lhs[0][2] * rhs[2][1];
		result[0][2] = lhs[0][0] * rhs[0][2] + lhs[0][1] * rhs[1][2] + lhs[0][2] * rhs[2][2];
		result[0][3] = lhs[0][0] * rhs[0][3] + lhs[0][1] * rhs[1][3] + lhs[0][2] * rhs[2][3];

		// Second row
		result[1][0] = lhs[1][0] * rhs[0][0] + lhs[1][1] * rhs[1][0] + lhs[1][2] * rhs[2][0];
		result[1][1] = lhs[1][0] * rhs[0][1] + lhs[1][1] * rhs[1][1] + lhs[1][2] * rhs[2][1];
		result[1][2] = lhs[1][0] * rhs[0][2] + lhs[1][1] * rhs[1][2] + lhs[1][2] * rhs[2][2];
		result[1][3] = lhs[1][0] * rhs[0][3] + lhs[1][1] * rhs[1][3] + lhs[1][2] * rhs[2][3];

		// Third row
		result[2][0] = lhs[2][0] * rhs[0][0] + lhs[2][1] * rhs[1][0] + lhs[2][2] * rhs[2][0];
		result[2][1] = lhs[2][0] * rhs[0][1] + lhs[2][1] * rhs[1][1] + lhs[2][2] * rhs[2][1];
		result[2][2] = lhs[2][0] * rhs[0][2] + lhs[2][1] * rhs[1][2] + lhs[2][2] * rhs[2][2];
		result[2][3] = lhs[2][0] * rhs[0][3] + lhs[2][1] * rhs[1][3] + lhs[2][2] * rhs[2][3];

		return result;
	}

	/// @brief Overload of * binary arithmetic operator.
	///
	/// @tparam T is the type of the matrices' values.
	/// @param lhs is the first matrix.
	/// @param rhs is the second matrix.
	/// 
	/// @return The matrix resulted by the multiplication of the two provided matrices.
	/// 
	template <class T>
	inline Mat3x4<T> operator*(const Mat3x2<T>& lhs, const Mat2x4<T>& rhs)
	{
		Mat3x4<T> result;

		if constexpr (std::is_same_v<T, Int4>)
		{
			utils::mulMatrixInt4<3, 2, 4>(result, lhs, rhs);
			return result;
		}

		if constexpr (std::is_same_v<T, std::int8_t>)
		{
			utils::mulMatrixInt8<3, 2, 4>(result, lhs, rhs);
			return result;
		}

#ifdef SEL_INTRINSIC_MATRIX_MUL
		// Select the 32-bit float and integer intrinsic backends.
		if constexpr (std::is_same_v<T, float>)
		{
			utils::mulMatrix_3x2_2x4((float*)&result, (float*)&lhs, (float*)&rhs);
			return result;
		}
		else if constexpr (std::is_same_v<T, int>)
		{
			utils::mulMatrix_3x2_2x4((int*)&result, (int*)&lhs, (int*)&rhs);
			return result;
		}
#endif

		// Normal multiplication
		// First row
		result[0][0] = lhs[0][0] * rhs[0][0] + lhs[0][1] * rhs[1][0];
		result[0][1] = lhs[0][0] * rhs[0][1] + lhs[0][1] * rhs[1][1];
		result[0][2] = lhs[0][0] * rhs[0][2] + lhs[0][1] * rhs[1][2];
		result[0][3] = lhs[0][0] * rhs[0][3] + lhs[0][1] * rhs[1][3];

		// Second row
		result[1][0] = lhs[1][0] * rhs[0][0] + lhs[1][1] * rhs[1][0];
		result[1][1] = lhs[1][0] * rhs[0][1] + lhs[1][1] * rhs[1][1];
		result[1][2] = lhs[1][0] * rhs[0][2] + lhs[1][1] * rhs[1][2];
		result[1][3] = lhs[1][0] * rhs[0][3] + lhs[1][1] * rhs[1][3];

		// Third row
		result[2][0] = lhs[2][0] * rhs[0][0] + lhs[2][1] * rhs[1][0];
		result[2][1] = lhs[2][0] * rhs[0][1] + lhs[2][1] * rhs[1][1];
		result[2][2] = lhs[2][0] * rhs[0][2] + lhs[2][1] * rhs[1][2];
		result[2][3] = lhs[2][0] * rhs[0][3] + lhs[2][1] * rhs[1][3];

		return result;
	}


	// --- 3x3 result ----------------------------------------------------------

	/// @brief Overload of * binary arithmetic operator.
	///
	/// @tparam T is the type of the matrices' values.
	/// @param lhs is the first matrix.
	/// @param rhs is the second matrix.
	/// 
	/// @return The matrix resulted by the multiplication of the two provided matrices.
	/// 
	template <class T>
	inline Mat3x3<T> operator*(const Mat3x4<T>& lhs, const Mat4x3<T>& rhs)
	{
		Mat3x3<T> result;

		if constexpr (std::is_same_v<T, Int4>)
		{
			utils::mulMatrixInt4<3, 4, 3>(result, lhs, rhs);
			return result;
		}

		if constexpr (std::is_same_v<T, std::int8_t>)
		{
			utils::mulMatrixInt8<3, 4, 3>(result, lhs, rhs);
			return result;
		}

#ifdef SEL_INTRINSIC_MATRIX_MUL
		// Select the 32-bit float and integer intrinsic backends.
		if constexpr (std::is_same_v<T, float>)
		{
			utils::mulMatrix_3x4_4x3((float*)&result, (float*)&lhs, (float*)&rhs);
			return result;
		}
		else if constexpr (std::is_same_v<T, int>)
		{
			utils::mulMatrix_3x4_4x3((int*)&result, (int*)&lhs, (int*)&rhs);
			return result;
		}
#endif

		// Normal multiplication
		// First row
		result[0][0] = lhs[0][0] * rhs[0][0] + lhs[0][1] * rhs[1][0] + lhs[0][2] * rhs[2][0] + lhs[0][3] * rhs[3][0];
		result[0][1] = lhs[0][0] * rhs[0][1] + lhs[0][1] * rhs[1][1] + lhs[0][2] * rhs[2][1] + lhs[0][3] * rhs[3][1];
		result[0][2] = lhs[0][0] * rhs[0][2] + lhs[0][1] * rhs[1][2] + lhs[0][2] * rhs[2][2] + lhs[0][3] * rhs[3][2];

		// Second row
		result[1][0] = lhs[1][0] * rhs[0][0] + lhs[1][1] * rhs[1][0] + lhs[1][2] * rhs[2][0] + lhs[1][3] * rhs[3][0];
		result[1][1] = lhs[1][0] * rhs[0][1] + lhs[1][1] * rhs[1][1] + lhs[1][2] * rhs[2][1] + lhs[1][3] * rhs[3][1];
		result[1][2] = lhs[1][0] * rhs[0][2] + lhs[1][1] * rhs[1][2] + lhs[1][2] * rhs[2][2] + lhs[1][3] * rhs[3][2];

		// Third row
		result[2][0] = lhs[2][0] * rhs[0][0] + lhs[2][1] * rhs[1][0] + lhs[2][2] * rhs[2][0] + lhs[2][3] * rhs[3][0];
		result[2][1] = lhs[2][0] * rhs[0][1] + lhs[2][1] * rhs[1][1] + lhs[2][2] * rhs[2][1] + lhs[2][3] * rhs[3][1];
		result[2][2] = lhs[2][0] * rhs[0][2] + lhs[2][1] * rhs[1][2] + lhs[2][2] * rhs[2][2] + lhs[2][3] * rhs[3][2];

		return result;
	}

	/// @brief Overload of * binary arithmetic operator.
	///
	/// @tparam T is the type of the matrices' values.
	/// @param lhs is the first matrix.
	/// @param rhs is the second matrix.
	/// 
	/// @return The matrix resulted by the multiplication of the two provided matrices.
	/// 
	template <class T>
	inline Mat3x3<T> operator*(const Mat3x3<T>& lhs, const Mat3x3<T>& rhs)
	{
		Mat3x3<T> result;

		if constexpr (std::is_same_v<T, Int4>)
		{
			utils::mulMatrixInt4<3, 3, 3>(result, lhs, rhs);
			return result;
		}

		if constexpr (std::is_same_v<T, std::int8_t>)
		{
			utils::mulMatrixInt8<3, 3, 3>(result, lhs, rhs);
			return result;
		}

#ifdef SEL_INTRINSIC_MATRIX_MUL
		// Select the 32-bit float and integer intrinsic backends.
		if constexpr (std::is_same_v<T, float>)
		{
			utils::mulMatrix_3x3_3x3((float*)&result, (float*)&lhs, (float*)&rhs);
			return result;
		}
		else if constexpr (std::is_same_v<T, int>)
		{
			utils::mulMatrix_3x3_3x3((int*)&result, (int*)&lhs, (int*)&rhs);
			return result;
		}
#endif

		// Normal multiplication
		// First row
		result[0][0] = lhs[0][0] * rhs[0][0] + lhs[0][1] * rhs[1][0] + lhs[0][2] * rhs[2][0];
		result[0][1] = lhs[0][0] * rhs[0][1] + lhs[0][1] * rhs[1][1] + lhs[0][2] * rhs[2][1];
		result[0][2] = lhs[0][0] * rhs[0][2] + lhs[0][1] * rhs[1][2] + lhs[0][2] * rhs[2][2];

		// Second row
		result[1][0] = lhs[1][0] * rhs[0][0] + lhs[1][1] * rhs[1][0] + lhs[1][2] * rhs[2][0];
		result[1][1] = lhs[1][0] * rhs[0][1] + lhs[1][1] * rhs[1][1] + lhs[1][2] * rhs[2][1];
		result[1][2] = lhs[1][0] * rhs[0][2] + lhs[1][1] * rhs[1][2] + lhs[1][2] * rhs[2][2];

		// Third row
		result[2][0] = lhs[2][0] * rhs[0][0] + lhs[2][1] * rhs[1][0] + lhs[2][2] * rhs[2][0];
		result[2][1] = lhs[2][0] * rhs[0][1] + lhs[2][1] * rhs[1][1] + lhs[2][2] * rhs[2][1];
		result[2][2] = lhs[2][0] * rhs[0][2] + lhs[2][1] * rhs[1][2] + lhs[2][2] * rhs[2][2];

		return result;
	}

	/// @brief Overload of * binary arithmetic operator.
	///
	/// @tparam T is the type of the matrices' values.
	/// @param lhs is the first matrix.
	/// @param rhs is the second matrix.
	/// 
	/// @return The matrix resulted by the multiplication of the two provided matrices.
	/// 
	template <class T>
	inline Mat3x3<T> operator*(const Mat3x2<T>& lhs, const Mat2x3<T>& rhs)
	{
		Mat3x3<T> result;

		if constexpr (std::is_same_v<T, Int4>)
		{
			utils::mulMatrixInt4<3, 2, 3>(result, lhs, rhs);
			return result;
		}

		if constexpr (std::is_same_v<T, std::int8_t>)
		{
			utils::mulMatrixInt8<3, 2, 3>(result, lhs, rhs);
			return result;
		}

#ifdef SEL_INTRINSIC_MATRIX_MUL
		// Select the 32-bit float and integer intrinsic backends.
		if constexpr (std::is_same_v<T, float>)
		{
			utils::mulMatrix_3x2_2x3((float*)&result, (float*)&lhs, (float*)&rhs);
			return result;
		}
		else if constexpr (std::is_same_v<T, int>)
		{
			utils::mulMatrix_3x2_2x3((int*)&result, (int*)&lhs, (int*)&rhs);
			return result;
		}
#endif

		// Normal multiplication
		// First row
		result[0][0] = lhs[0][0] * rhs[0][0] + lhs[0][1] * rhs[1][0];
		result[0][1] = lhs[0][0] * rhs[0][1] + lhs[0][1] * rhs[1][1];
		result[0][2] = lhs[0][0] * rhs[0][2] + lhs[0][1] * rhs[1][2];

		// Second row
		result[1][0] = lhs[1][0] * rhs[0][0] + lhs[1][1] * rhs[1][0];
		result[1][1] = lhs[1][0] * rhs[0][1] + lhs[1][1] * rhs[1][1];
		result[1][2] = lhs[1][0] * rhs[0][2] + lhs[1][1] * rhs[1][2];

		// Third row
		result[2][0] = lhs[2][0] * rhs[0][0] + lhs[2][1] * rhs[1][0];
		result[2][1] = lhs[2][0] * rhs[0][1] + lhs[2][1] * rhs[1][1];
		result[2][2] = lhs[2][0] * rhs[0][2] + lhs[2][1] * rhs[1][2];

		return result;
	}


	// --- 3x2 result ----------------------------------------------------------

	/// @brief Overload of * binary arithmetic operator.
	///
	/// @tparam T is the type of the matrices' values.
	/// @param lhs is the first matrix.
	/// @param rhs is the second matrix.
	/// 
	/// @return The matrix resulted by the multiplication of the two provided matrices.
	/// 
	template <class T>
	inline Mat3x2<T> operator*(const Mat3x4<T>& lhs, const Mat4x2<T>& rhs)
	{
		Mat3x2<T> result;

		if constexpr (std::is_same_v<T, Int4>)
		{
			utils::mulMatrixInt4<3, 4, 2>(result, lhs, rhs);
			return result;
		}

		if constexpr (std::is_same_v<T, std::int8_t>)
		{
			utils::mulMatrixInt8<3, 4, 2>(result, lhs, rhs);
			return result;
		}

#ifdef SEL_INTRINSIC_MATRIX_MUL
		// Select the 32-bit float and integer intrinsic backends.
		if constexpr (std::is_same_v<T, float>)
		{
			utils::mulMatrix_3x4_4x2((float*)&result, (float*)&lhs, (float*)&rhs);
			return result;
		}
		else if constexpr (std::is_same_v<T, int>)
		{
			utils::mulMatrix_3x4_4x2((int*)&result, (int*)&lhs, (int*)&rhs);
			return result;
		}
#endif

		// Normal multiplication
		// First row
		result[0][0] = lhs[0][0] * rhs[0][0] + lhs[0][1] * rhs[1][0] + lhs[0][2] * rhs[2][0] + lhs[0][3] * rhs[3][0];
		result[0][1] = lhs[0][0] * rhs[0][1] + lhs[0][1] * rhs[1][1] + lhs[0][2] * rhs[2][1] + lhs[0][3] * rhs[3][1];

		// Second row
		result[1][0] = lhs[1][0] * rhs[0][0] + lhs[1][1] * rhs[1][0] + lhs[1][2] * rhs[2][0] + lhs[1][3] * rhs[3][0];
		result[1][1] = lhs[1][0] * rhs[0][1] + lhs[1][1] * rhs[1][1] + lhs[1][2] * rhs[2][1] + lhs[1][3] * rhs[3][1];

		// Third row
		result[2][0] = lhs[2][0] * rhs[0][0] + lhs[2][1] * rhs[1][0] + lhs[2][2] * rhs[2][0] + lhs[2][3] * rhs[3][0];
		result[2][1] = lhs[2][0] * rhs[0][1] + lhs[2][1] * rhs[1][1] + lhs[2][2] * rhs[2][1] + lhs[2][3] * rhs[3][1];

		return result;
	}

	/// @brief Overload of * binary arithmetic operator.
	///
	/// @tparam T is the type of the matrices' values.
	/// @param lhs is the first matrix.
	/// @param rhs is the second matrix.
	/// 
	/// @return The matrix resulted by the multiplication of the two provided matrices.
	/// 
	template <class T>
	inline Mat3x2<T> operator*(const Mat3x3<T>& lhs, const Mat3x2<T>& rhs)
	{
		Mat3x2<T> result;

		if constexpr (std::is_same_v<T, Int4>)
		{
			utils::mulMatrixInt4<3, 3, 2>(result, lhs, rhs);
			return result;
		}

		if constexpr (std::is_same_v<T, std::int8_t>)
		{
			utils::mulMatrixInt8<3, 3, 2>(result, lhs, rhs);
			return result;
		}

#ifdef SEL_INTRINSIC_MATRIX_MUL
		// Select the 32-bit float and integer intrinsic backends.
		if constexpr (std::is_same_v<T, float>)
		{
			utils::mulMatrix_3x3_3x2((float*)&result, (float*)&lhs, (float*)&rhs);
			return result;
		}
		else if constexpr (std::is_same_v<T, int>)
		{
			utils::mulMatrix_3x3_3x2((int*)&result, (int*)&lhs, (int*)&rhs);
			return result;
		}
#endif

		// Normal multiplication
		// First row
		result[0][0] = lhs[0][0] * rhs[0][0] + lhs[0][1] * rhs[1][0] + lhs[0][2] * rhs[2][0];
		result[0][1] = lhs[0][0] * rhs[0][1] + lhs[0][1] * rhs[1][1] + lhs[0][2] * rhs[2][1];

		// Second row
		result[1][0] = lhs[1][0] * rhs[0][0] + lhs[1][1] * rhs[1][0] + lhs[1][2] * rhs[2][0];
		result[1][1] = lhs[1][0] * rhs[0][1] + lhs[1][1] * rhs[1][1] + lhs[1][2] * rhs[2][1];

		// Third row
		result[2][0] = lhs[2][0] * rhs[0][0] + lhs[2][1] * rhs[1][0] + lhs[2][2] * rhs[2][0];
		result[2][1] = lhs[2][0] * rhs[0][1] + lhs[2][1] * rhs[1][1] + lhs[2][2] * rhs[2][1];

		return result;
	}

	/// @brief Overload of * binary arithmetic operator.
	///
	/// @tparam T is the type of the matrices' values.
	/// @param lhs is the first matrix.
	/// @param rhs is the second matrix.
	/// 
	/// @return The matrix resulted by the multiplication of the two provided matrices.
	/// 
	template <class T>
	inline Mat3x2<T> operator*(const Mat3x2<T>& lhs, const Mat2x2<T>& rhs)
	{
		Mat3x2<T> result;

		if constexpr (std::is_same_v<T, Int4>)
		{
			utils::mulMatrixInt4<3, 2, 2>(result, lhs, rhs);
			return result;
		}

		if constexpr (std::is_same_v<T, std::int8_t>)
		{
			utils::mulMatrixInt8<3, 2, 2>(result, lhs, rhs);
			return result;
		}

#ifdef SEL_INTRINSIC_MATRIX_MUL
		// Select the 32-bit float and integer intrinsic backends.
		if constexpr (std::is_same_v<T, float>)
		{
			utils::mulMatrix_3x2_2x2((float*)&result, (float*)&lhs, (float*)&rhs);
			return result;
		}
		else if constexpr (std::is_same_v<T, int>)
		{
			utils::mulMatrix_3x2_2x2((int*)&result, (int*)&lhs, (int*)&rhs);
			return result;
		}
#endif

		// Normal multiplication
		// First row
		result[0][0] = lhs[0][0] * rhs[0][0] + lhs[0][1] * rhs[1][0];
		result[0][1] = lhs[0][0] * rhs[0][1] + lhs[0][1] * rhs[1][1];

		// Second row
		result[1][0] = lhs[1][0] * rhs[0][0] + lhs[1][1] * rhs[1][0];
		result[1][1] = lhs[1][0] * rhs[0][1] + lhs[1][1] * rhs[1][1];

		// Third row
		result[2][0] = lhs[2][0] * rhs[0][0] + lhs[2][1] * rhs[1][0];
		result[2][1] = lhs[2][0] * rhs[0][1] + lhs[2][1] * rhs[1][1];

		return result;
	}


	// --- 2x4 result ----------------------------------------------------------

	/// @brief Overload of * binary arithmetic operator.
	///
	/// @tparam T is the type of the matrices' values.
	/// @param lhs is the first matrix.
	/// @param rhs is the second matrix.
	/// 
	/// @return The matrix resulted by the multiplication of the two provided matrices.
	/// 
	template <class T>
	inline Mat2x4<T> operator*(const Mat2x4<T>& lhs, const Mat4x4<T>& rhs)
	{
		Mat2x4<T> result;

		if constexpr (std::is_same_v<T, Int4>)
		{
			utils::mulMatrixInt4<2, 4, 4>(result, lhs, rhs);
			return result;
		}

		if constexpr (std::is_same_v<T, std::int8_t>)
		{
			utils::mulMatrixInt8<2, 4, 4>(result, lhs, rhs);
			return result;
		}

#ifdef SEL_INTRINSIC_MATRIX_MUL
		// Select the 32-bit float and integer intrinsic backends.
		if constexpr (std::is_same_v<T, float>)
		{
			utils::mulMatrix_2x4_4x4((float*)&result, (float*)&lhs, (float*)&rhs);
			return result;
		}
		else if constexpr (std::is_same_v<T, int>)
		{
			utils::mulMatrix_2x4_4x4((int*)&result, (int*)&lhs, (int*)&rhs);
			return result;
		}
#endif

		// Normal multiplication
		// First row
		result[0][0] = lhs[0][0] * rhs[0][0] + lhs[0][1] * rhs[1][0] + lhs[0][2] * rhs[2][0] + lhs[0][3] * rhs[3][0];
		result[0][1] = lhs[0][0] * rhs[0][1] + lhs[0][1] * rhs[1][1] + lhs[0][2] * rhs[2][1] + lhs[0][3] * rhs[3][1];
		result[0][2] = lhs[0][0] * rhs[0][2] + lhs[0][1] * rhs[1][2] + lhs[0][2] * rhs[2][2] + lhs[0][3] * rhs[3][2];
		result[0][3] = lhs[0][0] * rhs[0][3] + lhs[0][1] * rhs[1][3] + lhs[0][2] * rhs[2][3] + lhs[0][3] * rhs[3][3];

		// Second row
		result[1][0] = lhs[1][0] * rhs[0][0] + lhs[1][1] * rhs[1][0] + lhs[1][2] * rhs[2][0] + lhs[1][3] * rhs[3][0];
		result[1][1] = lhs[1][0] * rhs[0][1] + lhs[1][1] * rhs[1][1] + lhs[1][2] * rhs[2][1] + lhs[1][3] * rhs[3][1];
		result[1][2] = lhs[1][0] * rhs[0][2] + lhs[1][1] * rhs[1][2] + lhs[1][2] * rhs[2][2] + lhs[1][3] * rhs[3][2];
		result[1][3] = lhs[1][0] * rhs[0][3] + lhs[1][1] * rhs[1][3] + lhs[1][2] * rhs[2][3] + lhs[1][3] * rhs[3][3];

		return result;
	}

	/// @brief Overload of * binary arithmetic operator.
	///
	/// @tparam T is the type of the matrices' values.
	/// @param lhs is the first matrix.
	/// @param rhs is the second matrix.
	/// 
	/// @return The matrix resulted by the multiplication of the two provided matrices.
	/// 
	template <class T>
	inline Mat2x4<T> operator*(const Mat2x3<T>& lhs, const Mat3x4<T>& rhs)
	{
		Mat2x4<T> result;

		if constexpr (std::is_same_v<T, Int4>)
		{
			utils::mulMatrixInt4<2, 3, 4>(result, lhs, rhs);
			return result;
		}

		if constexpr (std::is_same_v<T, std::int8_t>)
		{
			utils::mulMatrixInt8<2, 3, 4>(result, lhs, rhs);
			return result;
		}

#ifdef SEL_INTRINSIC_MATRIX_MUL
		// Select the 32-bit float and integer intrinsic backends.
		if constexpr (std::is_same_v<T, float>)
		{
			utils::mulMatrix_2x3_3x4((float*)&result, (float*)&lhs, (float*)&rhs);
			return result;
		}
		else if constexpr (std::is_same_v<T, int>)
		{
			utils::mulMatrix_2x3_3x4((int*)&result, (int*)&lhs, (int*)&rhs);
			return result;
		}
#endif

		// Normal multiplication
		// First row
		result[0][0] = lhs[0][0] * rhs[0][0] + lhs[0][1] * rhs[1][0] + lhs[0][2] * rhs[2][0];
		result[0][1] = lhs[0][0] * rhs[0][1] + lhs[0][1] * rhs[1][1] + lhs[0][2] * rhs[2][1];
		result[0][2] = lhs[0][0] * rhs[0][2] + lhs[0][1] * rhs[1][2] + lhs[0][2] * rhs[2][2];
		result[0][3] = lhs[0][0] * rhs[0][3] + lhs[0][1] * rhs[1][3] + lhs[0][2] * rhs[2][3];

		// Second row
		result[1][0] = lhs[1][0] * rhs[0][0] + lhs[1][1] * rhs[1][0] + lhs[1][2] * rhs[2][0];
		result[1][1] = lhs[1][0] * rhs[0][1] + lhs[1][1] * rhs[1][1] + lhs[1][2] * rhs[2][1];
		result[1][2] = lhs[1][0] * rhs[0][2] + lhs[1][1] * rhs[1][2] + lhs[1][2] * rhs[2][2];
		result[1][3] = lhs[1][0] * rhs[0][3] + lhs[1][1] * rhs[1][3] + lhs[1][2] * rhs[2][3];

		return result;
	}

	/// @brief Overload of * binary arithmetic operator.
	///
	/// @tparam T is the type of the matrices' values.
	/// @param lhs is the first matrix.
	/// @param rhs is the second matrix.
	/// 
	/// @return The matrix resulted by the multiplication of the two provided matrices.
	/// 
	template <class T>
	inline Mat2x4<T> operator*(const Mat2x2<T>& lhs, const Mat2x4<T>& rhs)
	{
		Mat2x4<T> result;

		if constexpr (std::is_same_v<T, Int4>)
		{
			utils::mulMatrixInt4<2, 2, 4>(result, lhs, rhs);
			return result;
		}

		if constexpr (std::is_same_v<T, std::int8_t>)
		{
			utils::mulMatrixInt8<2, 2, 4>(result, lhs, rhs);
			return result;
		}

#ifdef SEL_INTRINSIC_MATRIX_MUL
		// Select the 32-bit float and integer intrinsic backends.
		if constexpr (std::is_same_v<T, float>)
		{
			utils::mulMatrix_2x2_2x4((float*)&result, (float*)&lhs, (float*)&rhs);
			return result;
		}
		else if constexpr (std::is_same_v<T, int>)
		{
			utils::mulMatrix_2x2_2x4((int*)&result, (int*)&lhs, (int*)&rhs);
			return result;
		}
#endif

		// Normal multiplication
		// First row
		result[0][0] = lhs[0][0] * rhs[0][0] + lhs[0][1] * rhs[1][0];
		result[0][1] = lhs[0][0] * rhs[0][1] + lhs[0][1] * rhs[1][1];
		result[0][2] = lhs[0][0] * rhs[0][2] + lhs[0][1] * rhs[1][2];
		result[0][3] = lhs[0][0] * rhs[0][3] + lhs[0][1] * rhs[1][3];

		// Second row
		result[1][0] = lhs[1][0] * rhs[0][0] + lhs[1][1] * rhs[1][0];
		result[1][1] = lhs[1][0] * rhs[0][1] + lhs[1][1] * rhs[1][1];
		result[1][2] = lhs[1][0] * rhs[0][2] + lhs[1][1] * rhs[1][2];
		result[1][3] = lhs[1][0] * rhs[0][3] + lhs[1][1] * rhs[1][3];

		return result;
	}


	// --- 2x3 result ----------------------------------------------------------

	/// @brief Overload of * binary arithmetic operator.
	///
	/// @tparam T is the type of the matrices' values.
	/// @param lhs is the first matrix.
	/// @param rhs is the second matrix.
	/// 
	/// @return The matrix resulted by the multiplication of the two provided matrices.
	/// 
	template <class T>
	inline Mat2x3<T> operator*(const Mat2x4<T>& lhs, const Mat4x3<T>& rhs)
	{
		Mat2x3<T> result;

		if constexpr (std::is_same_v<T, Int4>)
		{
			utils::mulMatrixInt4<2, 4, 3>(result, lhs, rhs);
			return result;
		}

		if constexpr (std::is_same_v<T, std::int8_t>)
		{
			utils::mulMatrixInt8<2, 4, 3>(result, lhs, rhs);
			return result;
		}

#ifdef SEL_INTRINSIC_MATRIX_MUL
		// Select the 32-bit float and integer intrinsic backends.
		if constexpr (std::is_same_v<T, float>)
		{
			utils::mulMatrix_2x4_4x3((float*)&result, (float*)&lhs, (float*)&rhs);
			return result;
		}
		else if constexpr (std::is_same_v<T, int>)
		{
			utils::mulMatrix_2x4_4x3((int*)&result, (int*)&lhs, (int*)&rhs);
			return result;
		}
#endif

		// Normal multiplication
		// First row
		result[0][0] = lhs[0][0] * rhs[0][0] + lhs[0][1] * rhs[1][0] + lhs[0][2] * rhs[2][0] + lhs[0][3] * rhs[3][0];
		result[0][1] = lhs[0][0] * rhs[0][1] + lhs[0][1] * rhs[1][1] + lhs[0][2] * rhs[2][1] + lhs[0][3] * rhs[3][1];
		result[0][2] = lhs[0][0] * rhs[0][2] + lhs[0][1] * rhs[1][2] + lhs[0][2] * rhs[2][2] + lhs[0][3] * rhs[3][2];

		// Second row
		result[1][0] = lhs[1][0] * rhs[0][0] + lhs[1][1] * rhs[1][0] + lhs[1][2] * rhs[2][0] + lhs[1][3] * rhs[3][0];
		result[1][1] = lhs[1][0] * rhs[0][1] + lhs[1][1] * rhs[1][1] + lhs[1][2] * rhs[2][1] + lhs[1][3] * rhs[3][1];
		result[1][2] = lhs[1][0] * rhs[0][2] + lhs[1][1] * rhs[1][2] + lhs[1][2] * rhs[2][2] + lhs[1][3] * rhs[3][2];

		return result;
	}

	/// @brief Overload of * binary arithmetic operator.
	///
	/// @tparam T is the type of the matrices' values.
	/// @param lhs is the first matrix.
	/// @param rhs is the second matrix.
	/// 
	/// @return The matrix resulted by the multiplication of the two provided matrices.
	/// 
	template <class T>
	inline Mat2x3<T> operator*(const Mat2x3<T>& lhs, const Mat3x3<T>& rhs)
	{
		Mat2x3<T> result;

		if constexpr (std::is_same_v<T, Int4>)
		{
			utils::mulMatrixInt4<2, 3, 3>(result, lhs, rhs);
			return result;
		}

		if constexpr (std::is_same_v<T, std::int8_t>)
		{
			utils::mulMatrixInt8<2, 3, 3>(result, lhs, rhs);
			return result;
		}

#ifdef SEL_INTRINSIC_MATRIX_MUL
		// Select the 32-bit float and integer intrinsic backends.
		if constexpr (std::is_same_v<T, float>)
		{
			utils::mulMatrix_2x3_3x3((float*)&result, (float*)&lhs, (float*)&rhs);
			return result;
		}
		else if constexpr (std::is_same_v<T, int>)
		{
			utils::mulMatrix_2x3_3x3((int*)&result, (int*)&lhs, (int*)&rhs);
			return result;
		}
#endif

		// Normal multiplication
		// First row
		result[0][0] = lhs[0][0] * rhs[0][0] + lhs[0][1] * rhs[1][0] + lhs[0][2] * rhs[2][0];
		result[0][1] = lhs[0][0] * rhs[0][1] + lhs[0][1] * rhs[1][1] + lhs[0][2] * rhs[2][1];
		result[0][2] = lhs[0][0] * rhs[0][2] + lhs[0][1] * rhs[1][2] + lhs[0][2] * rhs[2][2];

		// Second row
		result[1][0] = lhs[1][0] * rhs[0][0] + lhs[1][1] * rhs[1][0] + lhs[1][2] * rhs[2][0];
		result[1][1] = lhs[1][0] * rhs[0][1] + lhs[1][1] * rhs[1][1] + lhs[1][2] * rhs[2][1];
		result[1][2] = lhs[1][0] * rhs[0][2] + lhs[1][1] * rhs[1][2] + lhs[1][2] * rhs[2][2];

		return result;
	}

	/// @brief Overload of * binary arithmetic operator.
	///
	/// @tparam T is the type of the matrices' values.
	/// @param lhs is the first matrix.
	/// @param rhs is the second matrix.
	/// 
	/// @return The matrix resulted by the multiplication of the two provided matrices.
	/// 
	template <class T>
	inline Mat2x3<T> operator*(const Mat2x2<T>& lhs, const Mat2x3<T>& rhs)
	{
		Mat2x3<T> result;

		if constexpr (std::is_same_v<T, Int4>)
		{
			utils::mulMatrixInt4<2, 2, 3>(result, lhs, rhs);
			return result;
		}

		if constexpr (std::is_same_v<T, std::int8_t>)
		{
			utils::mulMatrixInt8<2, 2, 3>(result, lhs, rhs);
			return result;
		}

#ifdef SEL_INTRINSIC_MATRIX_MUL
		// Select the 32-bit float and integer intrinsic backends.
		if constexpr (std::is_same_v<T, float>)
		{
			utils::mulMatrix_2x2_2x3((float*)&result, (float*)&lhs, (float*)&rhs);
			return result;
		}
		else if constexpr (std::is_same_v<T, int>)
		{
			utils::mulMatrix_2x2_2x3((int*)&result, (int*)&lhs, (int*)&rhs);
			return result;
		}
#endif

		// Normal multiplication
		// First row
		result[0][0] = lhs[0][0] * rhs[0][0] + lhs[0][1] * rhs[1][0];
		result[0][1] = lhs[0][0] * rhs[0][1] + lhs[0][1] * rhs[1][1];
		result[0][2] = lhs[0][0] * rhs[0][2] + lhs[0][1] * rhs[1][2];

		// Second row
		result[1][0] = lhs[1][0] * rhs[0][0] + lhs[1][1] * rhs[1][0];
		result[1][1] = lhs[1][0] * rhs[0][1] + lhs[1][1] * rhs[1][1];
		result[1][2] = lhs[1][0] * rhs[0][2] + lhs[1][1] * rhs[1][2];

		return result;
	}


	// --- 2x2 result ----------------------------------------------------------

	/// @brief Overload of * binary arithmetic operator.
	///
	/// @tparam T is the type of the matrices' values.
	/// @param lhs is the first matrix.
	/// @param rhs is the second matrix.
	/// 
	/// @return The matrix resulted by the multiplication of the two provided matrices.
	/// 
	template <class T>
	inline Mat2x2<T> operator*(const Mat2x4<T>& lhs, const Mat4x2<T>& rhs)
	{
		Mat2x2<T> result;

		if constexpr (std::is_same_v<T, Int4>)
		{
			utils::mulMatrixInt4<2, 4, 2>(result, lhs, rhs);
			return result;
		}

		if constexpr (std::is_same_v<T, std::int8_t>)
		{
			utils::mulMatrixInt8<2, 4, 2>(result, lhs, rhs);
			return result;
		}

#ifdef SEL_INTRINSIC_MATRIX_MUL
		// Select the 32-bit float and integer intrinsic backends.
		if constexpr (std::is_same_v<T, float>)
		{
			utils::mulMatrix_2x4_4x2((float*)&result, (float*)&lhs, (float*)&rhs);
			return result;
		}
		else if constexpr (std::is_same_v<T, int>)
		{
			utils::mulMatrix_2x4_4x2((int*)&result, (int*)&lhs, (int*)&rhs);
			return result;
		}
#endif

		// Normal multiplication
		// First row
		result[0][0] = lhs[0][0] * rhs[0][0] + lhs[0][1] * rhs[1][0] + lhs[0][2] * rhs[2][0] + lhs[0][3] * rhs[3][0];
		result[0][1] = lhs[0][0] * rhs[0][1] + lhs[0][1] * rhs[1][1] + lhs[0][2] * rhs[2][1] + lhs[0][3] * rhs[3][1];

		// Second row
		result[1][0] = lhs[1][0] * rhs[0][0] + lhs[1][1] * rhs[1][0] + lhs[1][2] * rhs[2][0] + lhs[1][3] * rhs[3][0];
		result[1][1] = lhs[1][0] * rhs[0][1] + lhs[1][1] * rhs[1][1] + lhs[1][2] * rhs[2][1] + lhs[1][3] * rhs[3][1];

		return result;
	}

	/// @brief Overload of * binary arithmetic operator.
	///
	/// @tparam T is the type of the matrices' values.
	/// @param lhs is the first matrix.
	/// @param rhs is the second matrix.
	/// 
	/// @return The matrix resulted by the multiplication of the two provided matrices.
	/// 
	template <class T>
	inline Mat2x2<T> operator*(const Mat2x3<T>& lhs, const Mat3x2<T>& rhs)
	{
		Mat2x2<T> result;

		if constexpr (std::is_same_v<T, Int4>)
		{
			utils::mulMatrixInt4<2, 3, 2>(result, lhs, rhs);
			return result;
		}

		if constexpr (std::is_same_v<T, std::int8_t>)
		{
			utils::mulMatrixInt8<2, 3, 2>(result, lhs, rhs);
			return result;
		}

#ifdef SEL_INTRINSIC_MATRIX_MUL
		// Select the 32-bit float and integer intrinsic backends.
		if constexpr (std::is_same_v<T, float>)
		{
			utils::mulMatrix_2x3_3x2((float*)&result, (float*)&lhs, (float*)&rhs);
			return result;
		}
		else if constexpr (std::is_same_v<T, int>)
		{
			utils::mulMatrix_2x3_3x2((int*)&result, (int*)&lhs, (int*)&rhs);
			return result;
		}
#endif

		// Normal multiplication
		// First row
		result[0][0] = lhs[0][0] * rhs[0][0] + lhs[0][1] * rhs[1][0] + lhs[0][2] * rhs[2][0];
		result[0][1] = lhs[0][0] * rhs[0][1] + lhs[0][1] * rhs[1][1] + lhs[0][2] * rhs[2][1];

		// Second row
		result[1][0] = lhs[1][0] * rhs[0][0] + lhs[1][1] * rhs[1][0] + lhs[1][2] * rhs[2][0];
		result[1][1] = lhs[1][0] * rhs[0][1] + lhs[1][1] * rhs[1][1] + lhs[1][2] * rhs[2][1];

		return result;
	}

	/// @brief Overload of * binary arithmetic operator.
	///
	/// @tparam T is the type of the matrices' values.
	/// @param lhs is the first matrix.
	/// @param rhs is the second matrix.
	/// 
	/// @return The matrix resulted by the multiplication of the two provided matrices.
	/// 
	template <class T>
	inline Mat2x2<T> operator*(const Mat2x2<T>& lhs, const Mat2x2<T>& rhs)
	{
		Mat2x2<T> result;

		if constexpr (std::is_same_v<T, Int4>)
		{
			utils::mulMatrixInt4<2, 2, 2>(result, lhs, rhs);
			return result;
		}

		if constexpr (std::is_same_v<T, std::int8_t>)
		{
			utils::mulMatrixInt8<2, 2, 2>(result, lhs, rhs);
			return result;
		}

#ifdef SEL_INTRINSIC_MATRIX_MUL
		// Select the 32-bit float and integer intrinsic backends.
		if constexpr (std::is_same_v<T, float>)
		{
			utils::mulMatrix_2x2_2x2((float*)&result, (float*)&lhs, (float*)&rhs);
			return result;
		}
		else if constexpr (std::is_same_v<T, int>)
		{
			utils::mulMatrix_2x2_2x2((int*)&result, (int*)&lhs, (int*)&rhs);
			return result;
		}
#endif

		// Normal multiplication
		// First row
		result[0][0] = lhs[0][0] * rhs[0][0] + lhs[0][1] * rhs[1][0];
		result[0][1] = lhs[0][0] * rhs[0][1] + lhs[0][1] * rhs[1][1];

		// Second row
		result[1][0] = lhs[1][0] * rhs[0][0] + lhs[1][1] * rhs[1][0];
		result[1][1] = lhs[1][0] * rhs[0][1] + lhs[1][1] * rhs[1][1];

		return result;
	}


	// --- 8x8 result ----------------------------------------------------------

	/// @brief Overload of * binary arithmetic operator.
	///
	/// @tparam T is the type of the matrices' values.
	/// @param lhs is the first matrix.
	/// @param rhs is the second matrix.
	///
	/// @return The matrix resulted by the multiplication of the two provided matrices.
	///
	template <class T>
	inline Mat8x8<T> operator*(const Mat8x8<T>& lhs, const Mat8x8<T>& rhs)
	{
		Mat8x8<T> result;

		if constexpr (std::is_same_v<T, Int4>)
		{
			utils::mulMatrixInt4<8, 8, 8>(result, lhs, rhs);
			return result;
		}

		if constexpr (std::is_same_v<T, std::int8_t>)
		{
			utils::mulMatrixInt8<8, 8, 8>(result, lhs, rhs);
			return result;
		}

#ifdef SEL_INTRINSIC_MATRIX_MUL
		// Select the 32-bit float and integer intrinsic backends.
		if constexpr (std::is_same_v<T, float> || std::is_same_v<T, int>)
		{
			utils::mulMatrix_8x8_8x8(result.m_data, lhs.m_data, rhs.m_data);
			return result;
		}
#endif

		// Normal multiplication
		// Calculate each row by accumulating rows of rhs in their original order.
		for (std::size_t row = 0; row < 8; ++row)
		{
			for (std::size_t column = 0; column < 8; ++column)
			{
				result[row][column] = lhs[row][0] * rhs[0][column];
				for (std::size_t inner = 1; inner < 8; ++inner)
				{
					result[row][column] += lhs[row][inner] * rhs[inner][column];
				}
			}
		}

		return result;
	}


	// --- 16x16 result ----------------------------------------------------------

	/// @brief Overload of * binary arithmetic operator.
	///
	/// @tparam T is the type of the matrices' values.
	/// @param lhs is the first matrix.
	/// @param rhs is the second matrix.
	///
	/// @return The matrix resulted by the multiplication of the two provided matrices.
	///
	template <class T>
	inline Mat16x16<T> operator*(const Mat16x16<T>& lhs, const Mat16x16<T>& rhs)
	{
		Mat16x16<T> result;

		if constexpr (std::is_same_v<T, Int4>)
		{
			utils::mulMatrixInt4<16, 16, 16>(result, lhs, rhs);
			return result;
		}

		if constexpr (std::is_same_v<T, std::int8_t>)
		{
			utils::mulMatrixInt8<16, 16, 16>(result, lhs, rhs);
			return result;
		}

#ifdef SEL_INTRINSIC_MATRIX_MUL
		// Select the 32-bit float and integer intrinsic backends.
		if constexpr (std::is_same_v<T, float> || std::is_same_v<T, int>)
		{
			utils::mulMatrix_16x16_16x16(result.m_data, lhs.m_data, rhs.m_data);
			return result;
		}
#endif

		// Normal multiplication
		// Calculate each row by accumulating rows of rhs in their original order.
		for (std::size_t row = 0; row < 16; ++row)
		{
			for (std::size_t column = 0; column < 16; ++column)
			{
				result[row][column] = lhs[row][0] * rhs[0][column];
				for (std::size_t inner = 1; inner < 16; ++inner)
				{
					result[row][column] += lhs[row][inner] * rhs[inner][column];
				}
			}
		}

		return result;
	}


	// --- 32x32 result ----------------------------------------------------------

	/// @brief Overload of * binary arithmetic operator.
	///
	/// @tparam T is the type of the matrices' values.
	/// @param lhs is the first matrix.
	/// @param rhs is the second matrix.
	///
	/// @return The matrix resulted by the multiplication of the two provided matrices.
	///
	template <class T>
	inline Mat32x32<T> operator*(const Mat32x32<T>& lhs, const Mat32x32<T>& rhs)
	{
		Mat32x32<T> result;

		if constexpr (std::is_same_v<T, Int4>)
		{
			utils::mulMatrixInt4<32, 32, 32>(result, lhs, rhs);
			return result;
		}

		if constexpr (std::is_same_v<T, std::int8_t>)
		{
			utils::mulMatrixInt8<32, 32, 32>(result, lhs, rhs);
			return result;
		}

#ifdef SEL_INTRINSIC_MATRIX_MUL
		// Select the 32-bit float and integer intrinsic backends.
		if constexpr (std::is_same_v<T, float> || std::is_same_v<T, int>)
		{
			utils::mulMatrix_32x32_32x32(result.m_data, lhs.m_data, rhs.m_data);
			return result;
		}
#endif

		// Normal multiplication
		// Calculate each row by accumulating rows of rhs in their original order.
		for (std::size_t row = 0; row < 32; ++row)
		{
			for (std::size_t column = 0; column < 32; ++column)
			{
				result[row][column] = lhs[row][0] * rhs[0][column];
				for (std::size_t inner = 1; inner < 32; ++inner)
				{
					result[row][column] += lhs[row][inner] * rhs[inner][column];
				}
			}
		}

		return result;
	}

}
