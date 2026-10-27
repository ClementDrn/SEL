#pragma once

#include "GenericMatrix.hpp"

namespace sel {

	/// @brief Compatibility name for a 2x2 fixed-size matrix.
	template <class T>
	using Mat2x2 = Matrix<T, 2, 2>;

	/// @brief 2x2 matrix of Int4 values.
	using Mat2x2i4 = Mat2x2<Int4>;
	/// @brief 2x2 matrix of std::int8_t values.
	using Mat2x2i8 = Mat2x2<std::int8_t>;
	/// @brief 2x2 matrix of int values.
	using Mat2x2i = Mat2x2<int>;
	/// @brief 2x2 matrix of float values.
	using Mat2x2f = Mat2x2<float>;
	/// @brief 2x2 matrix of unsigned int values.
	using Mat2x2u = Mat2x2<unsigned int>;

}
