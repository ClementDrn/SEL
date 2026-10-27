#pragma once

#include "GenericMatrix.hpp"

namespace sel {

	/// @brief Compatibility name for a 4x4 fixed-size matrix.
	template <class T>
	using Mat4x4 = Matrix<T, 4, 4>;

	/// @brief 4x4 matrix of Int4 values.
	using Mat4x4i4 = Mat4x4<Int4>;
	/// @brief 4x4 matrix of std::int8_t values.
	using Mat4x4i8 = Mat4x4<std::int8_t>;
	/// @brief 4x4 matrix of int values.
	using Mat4x4i = Mat4x4<int>;
	/// @brief 4x4 matrix of float values.
	using Mat4x4f = Mat4x4<float>;
	/// @brief 4x4 matrix of unsigned int values.
	using Mat4x4u = Mat4x4<unsigned int>;

	/// @brief 4x4 matrix of packed Float4E2M1 values.
	using Mat4x4f4 = Mat4x4<Float4E2M1>;
	/// @brief 4x4 matrix of Float8E4M3 values (the default FP8 format).
	using Mat4x4f8 = Mat4x4<Float8E4M3>;
	/// @brief 4x4 matrix of packed Float4E2M1 values, with an explicit format name.
	using Mat4x4f4e2m1 = Mat4x4<Float4E2M1>;
	/// @brief 4x4 matrix of Float8E4M3 values, with an explicit format name.
	using Mat4x4f8e4m3 = Mat4x4<Float8E4M3>;
	/// @brief 4x4 matrix of Float8E5M2 values.
	using Mat4x4f8e5m2 = Mat4x4<Float8E5M2>;

}
