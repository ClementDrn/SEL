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

	/// @brief 3x3 matrix of packed Float4E2M1 values.
	using Mat3x3f4 = Mat3x3<Float4E2M1>;
	/// @brief 3x3 matrix of Float8E4M3 values (the default FP8 format).
	using Mat3x3f8 = Mat3x3<Float8E4M3>;
	/// @brief 3x3 matrix of packed Float4E2M1 values, with an explicit format name.
	using Mat3x3f4e2m1 = Mat3x3<Float4E2M1>;
	/// @brief 3x3 matrix of Float8E4M3 values, with an explicit format name.
	using Mat3x3f8e4m3 = Mat3x3<Float8E4M3>;
	/// @brief 3x3 matrix of Float8E5M2 values.
	using Mat3x3f8e5m2 = Mat3x3<Float8E5M2>;

}
