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

	/// @brief 3x2 matrix of packed Float4E2M1 values.
	using Mat3x2f4 = Mat3x2<Float4E2M1>;
	/// @brief 3x2 matrix of Float8E4M3 values (the default FP8 format).
	using Mat3x2f8 = Mat3x2<Float8E4M3>;
	/// @brief 3x2 matrix of packed Float4E2M1 values, with an explicit format name.
	using Mat3x2f4e2m1 = Mat3x2<Float4E2M1>;
	/// @brief 3x2 matrix of Float8E4M3 values, with an explicit format name.
	using Mat3x2f8e4m3 = Mat3x2<Float8E4M3>;
	/// @brief 3x2 matrix of Float8E5M2 values.
	using Mat3x2f8e5m2 = Mat3x2<Float8E5M2>;

}
