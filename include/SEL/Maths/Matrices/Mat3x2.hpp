#pragma once

#include "GenericMatrix.hpp"

namespace sel {

	/// @brief Compatibility name for a 3x2 fixed-size matrix.
	template <class T>
	using Mat3x2 = Matrix<T, 3, 2>;

	/// @brief 3x2 matrix of Int4 values.
	using Mat3x2i4 = Mat3x2<Int4>;
	/// @brief 3x2 matrix of std::int8_t values.
	using Mat3x2i8 = Mat3x2<std::int8_t>;
	/// @brief 3x2 matrix of int values.
	using Mat3x2i = Mat3x2<int>;
	/// @brief 3x2 matrix of float values.
	using Mat3x2f = Mat3x2<float>;
	/// @brief 3x2 matrix of unsigned int values.
	using Mat3x2u = Mat3x2<unsigned int>;

}
