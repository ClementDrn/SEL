#pragma once

#include "GenericMatrix.hpp"

namespace sel {

	/// @brief Compatibility name for a 3x4 fixed-size matrix.
	template <class T>
	using Mat3x4 = Matrix<T, 3, 4>;

	/// @brief 3x4 matrix of Int4 values.
	using Mat3x4i4 = Mat3x4<Int4>;
	/// @brief 3x4 matrix of std::int8_t values.
	using Mat3x4i8 = Mat3x4<std::int8_t>;
	/// @brief 3x4 matrix of int values.
	using Mat3x4i = Mat3x4<int>;
	/// @brief 3x4 matrix of float values.
	using Mat3x4f = Mat3x4<float>;
	/// @brief 3x4 matrix of unsigned int values.
	using Mat3x4u = Mat3x4<unsigned int>;

	/// @brief 3x4 matrix of packed Float4E2M1 values.
	using Mat3x4f4 = Mat3x4<Float4E2M1>;
	/// @brief 3x4 matrix of Float8E4M3 values (the default FP8 format).
	using Mat3x4f8 = Mat3x4<Float8E4M3>;
	/// @brief 3x4 matrix of packed Float4E2M1 values, with an explicit format name.
	using Mat3x4f4e2m1 = Mat3x4<Float4E2M1>;
	/// @brief 3x4 matrix of Float8E4M3 values, with an explicit format name.
	using Mat3x4f8e4m3 = Mat3x4<Float8E4M3>;
	/// @brief 3x4 matrix of Float8E5M2 values.
	using Mat3x4f8e5m2 = Mat3x4<Float8E5M2>;

}
