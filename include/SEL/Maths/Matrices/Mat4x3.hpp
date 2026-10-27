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

}
