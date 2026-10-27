#pragma once

#include "GenericMatrix.hpp"

namespace sel {

	/// @brief Compatibility name for a 2x3 fixed-size matrix.
	template <class T>
	using Mat2x3 = Matrix<T, 2, 3>;

	/// @brief 2x3 matrix of Int4 values.
	using Mat2x3i4 = Mat2x3<Int4>;
	/// @brief 2x3 matrix of std::int8_t values.
	using Mat2x3i8 = Mat2x3<std::int8_t>;
	/// @brief 2x3 matrix of int values.
	using Mat2x3i = Mat2x3<int>;
	/// @brief 2x3 matrix of float values.
	using Mat2x3f = Mat2x3<float>;
	/// @brief 2x3 matrix of unsigned int values.
	using Mat2x3u = Mat2x3<unsigned int>;

	/// @brief 2x3 matrix of packed Float4E2M1 values.
	using Mat2x3f4 = Mat2x3<Float4E2M1>;
	/// @brief 2x3 matrix of Float8E4M3 values (the default FP8 format).
	using Mat2x3f8 = Mat2x3<Float8E4M3>;
	/// @brief 2x3 matrix of packed Float4E2M1 values, with an explicit format name.
	using Mat2x3f4e2m1 = Mat2x3<Float4E2M1>;
	/// @brief 2x3 matrix of Float8E4M3 values, with an explicit format name.
	using Mat2x3f8e4m3 = Mat2x3<Float8E4M3>;
	/// @brief 2x3 matrix of Float8E5M2 values.
	using Mat2x3f8e5m2 = Mat2x3<Float8E5M2>;

}
