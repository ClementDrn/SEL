#pragma once

#include "GenericMatrix.hpp"

namespace sel {

	/// @brief Compatibility name for a 3x3 fixed-size matrix.
	template <class T>
	using Mat3x3 = Matrix<T, 3, 3>;

	/// @brief 3x3 matrix of Int4 values.
	using Mat3x3i4 = Mat3x3<Int4>;
	/// @brief 3x3 matrix of std::int8_t values.
	using Mat3x3i8 = Mat3x3<std::int8_t>;
	/// @brief 3x3 matrix of int values.
	using Mat3x3i = Mat3x3<int>;
	/// @brief 3x3 matrix of float values.
	using Mat3x3f = Mat3x3<float>;
	/// @brief 3x3 matrix of unsigned int values.
	using Mat3x3u = Mat3x3<unsigned int>;

}
