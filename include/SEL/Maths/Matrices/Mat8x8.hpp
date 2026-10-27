#pragma once

#include "GenericMatrix.hpp"

namespace sel {

	/// @brief Compatibility name for a 8x8 fixed-size matrix.
	template <class T>
	using Mat8x8 = Matrix<T, 8, 8>;

	/// @brief 8x8 matrix of Int4 values.
	using Mat8x8i4 = Mat8x8<Int4>;
	/// @brief 8x8 matrix of std::int8_t values.
	using Mat8x8i8 = Mat8x8<std::int8_t>;
	/// @brief 8x8 matrix of int values.
	using Mat8x8i = Mat8x8<int>;
	/// @brief 8x8 matrix of float values.
	using Mat8x8f = Mat8x8<float>;
	/// @brief 8x8 matrix of unsigned int values.
	using Mat8x8u = Mat8x8<unsigned int>;

}
