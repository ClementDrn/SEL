#pragma once

#include "GenericMatrix.hpp"

namespace sel {

	/// @brief Compatibility name for a 16x16 fixed-size matrix.
	template <class T>
	using Mat16x16 = Matrix<T, 16, 16>;

	/// @brief 16x16 matrix of Int4 values.
	using Mat16x16i4 = Mat16x16<Int4>;
	/// @brief 16x16 matrix of std::int8_t values.
	using Mat16x16i8 = Mat16x16<std::int8_t>;
	/// @brief 16x16 matrix of int values.
	using Mat16x16i = Mat16x16<int>;
	/// @brief 16x16 matrix of float values.
	using Mat16x16f = Mat16x16<float>;
	/// @brief 16x16 matrix of unsigned int values.
	using Mat16x16u = Mat16x16<unsigned int>;

}
