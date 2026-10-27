#pragma once

#include "GenericMatrix.hpp"

namespace sel {

	/// @brief Compatibility name for a 32x32 fixed-size matrix.
	template <class T>
	using Mat32x32 = Matrix<T, 32, 32>;

	/// @brief 32x32 matrix of Int4 values.
	using Mat32x32i4 = Mat32x32<Int4>;
	/// @brief 32x32 matrix of std::int8_t values.
	using Mat32x32i8 = Mat32x32<std::int8_t>;
	/// @brief 32x32 matrix of int values.
	using Mat32x32i = Mat32x32<int>;
	/// @brief 32x32 matrix of float values.
	using Mat32x32f = Mat32x32<float>;
	/// @brief 32x32 matrix of unsigned int values.
	using Mat32x32u = Mat32x32<unsigned int>;

	/// @brief 32x32 matrix of packed Float4E2M1 values.
	using Mat32x32f4 = Mat32x32<Float4E2M1>;
	/// @brief 32x32 matrix of Float8E4M3 values (the default FP8 format).
	using Mat32x32f8 = Mat32x32<Float8E4M3>;
	/// @brief 32x32 matrix of packed Float4E2M1 values, with an explicit format name.
	using Mat32x32f4e2m1 = Mat32x32<Float4E2M1>;
	/// @brief 32x32 matrix of Float8E4M3 values, with an explicit format name.
	using Mat32x32f8e4m3 = Mat32x32<Float8E4M3>;
	/// @brief 32x32 matrix of Float8E5M2 values.
	using Mat32x32f8e5m2 = Mat32x32<Float8E5M2>;

}
