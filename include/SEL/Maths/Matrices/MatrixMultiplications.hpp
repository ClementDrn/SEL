#pragma once

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
	#include "SEL/Maths/Matrices/IntrinsicMatrixMul.hpp"
#endif


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

#ifdef SEL_INTRINSIC_MATRIX_MUL
		// Intrinsic multiplication is only available for float and int matrices.
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

#ifdef SEL_INTRINSIC_MATRIX_MUL
		// Intrinsic multiplication is only available for float and int matrices.
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

#ifdef SEL_INTRINSIC_MATRIX_MUL
		// Intrinsic multiplication is only available for float and int matrices.
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

#ifdef SEL_INTRINSIC_MATRIX_MUL
		// Intrinsic multiplication is only available for float and int matrices.
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

#ifdef SEL_INTRINSIC_MATRIX_MUL
		// Intrinsic multiplication is only available for float and int matrices.
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

#ifdef SEL_INTRINSIC_MATRIX_MUL
		// Intrinsic multiplication is only available for float and int matrices.
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

#ifdef SEL_INTRINSIC_MATRIX_MUL
		// Intrinsic multiplication is only available for float and int matrices.
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

#ifdef SEL_INTRINSIC_MATRIX_MUL
		// Intrinsic multiplication is only available for float and int matrices.
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

#ifdef SEL_INTRINSIC_MATRIX_MUL
		// Intrinsic multiplication is only available for float and int matrices.
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

#ifdef SEL_INTRINSIC_MATRIX_MUL
		// Intrinsic multiplication is only available for float and int matrices.
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

#ifdef SEL_INTRINSIC_MATRIX_MUL
		// Intrinsic multiplication is only available for float and int matrices.
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

#ifdef SEL_INTRINSIC_MATRIX_MUL
		// Intrinsic multiplication is only available for float and int matrices.
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

#ifdef SEL_INTRINSIC_MATRIX_MUL
		// Intrinsic multiplication is only available for float and int matrices.
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

#ifdef SEL_INTRINSIC_MATRIX_MUL
		// Intrinsic multiplication is only available for float and int matrices.
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

#ifdef SEL_INTRINSIC_MATRIX_MUL
		// Intrinsic multiplication is only available for float and int matrices.
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

#ifdef SEL_INTRINSIC_MATRIX_MUL
		// Intrinsic multiplication is only available for float and int matrices.
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

#ifdef SEL_INTRINSIC_MATRIX_MUL
		// Intrinsic multiplication is only available for float and int matrices.
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

#ifdef SEL_INTRINSIC_MATRIX_MUL
		// Intrinsic multiplication is only available for float and int matrices.
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

#ifdef SEL_INTRINSIC_MATRIX_MUL
		// Intrinsic multiplication is only available for float and int matrices.
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

#ifdef SEL_INTRINSIC_MATRIX_MUL
		// Intrinsic multiplication is only available for float and int matrices.
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

#ifdef SEL_INTRINSIC_MATRIX_MUL
		// Intrinsic multiplication is only available for float and int matrices.
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

#ifdef SEL_INTRINSIC_MATRIX_MUL
		// Intrinsic multiplication is only available for float and int matrices.
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

#ifdef SEL_INTRINSIC_MATRIX_MUL
		// Intrinsic multiplication is only available for float and int matrices.
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

#ifdef SEL_INTRINSIC_MATRIX_MUL
		// Intrinsic multiplication is only available for float and int matrices.
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

#ifdef SEL_INTRINSIC_MATRIX_MUL
		// Intrinsic multiplication is only available for float and int matrices.
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

#ifdef SEL_INTRINSIC_MATRIX_MUL
		// Intrinsic multiplication is only available for float and int matrices.
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

#ifdef SEL_INTRINSIC_MATRIX_MUL
		// Intrinsic multiplication is only available for float and int matrices.
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

}

