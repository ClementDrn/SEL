#pragma once

#include "GenericMatrix.hpp"

namespace sel {

	/// @brief Compatibility name for a 2x4 fixed-size matrix.
	template <class T>
	using Mat2x4 = Matrix<T, 2, 4>;

	/// @brief 2x4 matrix of Int4 values.
	using Mat2x4i4 = Mat2x4<Int4>;
	/// @brief 2x4 matrix of std::int8_t values.
	using Mat2x4i8 = Mat2x4<std::int8_t>;
	/// @brief 2x4 matrix of int values.
	using Mat2x4i = Mat2x4<int>;
	/// @brief 2x4 matrix of float values.
	using Mat2x4f = Mat2x4<float>;
	/// @brief 2x4 matrix of unsigned int values.
	using Mat2x4u = Mat2x4<unsigned int>;

}
