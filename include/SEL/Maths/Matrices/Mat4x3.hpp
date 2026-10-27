#pragma once

#include "GenericMatrix.hpp"

namespace sel {

	/// @brief Compatibility name for a 4x3 fixed-size matrix.
	template <class T>
	using Mat4x3 = Matrix<T, 4, 3>;

	/// @brief 4x3 matrix of Int4 values.
	using Mat4x3i4 = Mat4x3<Int4>;
	/// @brief 4x3 matrix of std::int8_t values.
	using Mat4x3i8 = Mat4x3<std::int8_t>;
	/// @brief 4x3 matrix of int values.
	using Mat4x3i = Mat4x3<int>;
	/// @brief 4x3 matrix of float values.
	using Mat4x3f = Mat4x3<float>;
	/// @brief 4x3 matrix of unsigned int values.
	using Mat4x3u = Mat4x3<unsigned int>;

	/// @brief 4x3 matrix of packed Float4E2M1 values.
	using Mat4x3f4 = Mat4x3<Float4E2M1>;
	/// @brief 4x3 matrix of Float8E4M3 values (the default FP8 format).
	using Mat4x3f8 = Mat4x3<Float8E4M3>;
	/// @brief 4x3 matrix of packed Float4E2M1 values, with an explicit format name.
	using Mat4x3f4e2m1 = Mat4x3<Float4E2M1>;
	/// @brief 4x3 matrix of Float8E4M3 values, with an explicit format name.
	using Mat4x3f8e4m3 = Mat4x3<Float8E4M3>;
	/// @brief 4x3 matrix of Float8E5M2 values.
	using Mat4x3f8e5m2 = Mat4x3<Float8E5M2>;

}
