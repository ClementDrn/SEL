#pragma once

#include "GenericMatrix.hpp"

namespace sel {

	/// @brief Compatibility name for a 4x2 fixed-size matrix.
	template <class T>
	using Mat4x2 = Matrix<T, 4, 2>;

	/// @brief 4x2 matrix of Int4 values.
	using Mat4x2i4 = Mat4x2<Int4>;
	/// @brief 4x2 matrix of std::int8_t values.
	using Mat4x2i8 = Mat4x2<std::int8_t>;
	/// @brief 4x2 matrix of int values.
	using Mat4x2i = Mat4x2<int>;
	/// @brief 4x2 matrix of float values.
	using Mat4x2f = Mat4x2<float>;
	/// @brief 4x2 matrix of unsigned int values.
	using Mat4x2u = Mat4x2<unsigned int>;

}
