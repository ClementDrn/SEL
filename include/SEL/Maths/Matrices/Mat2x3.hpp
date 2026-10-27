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

}
