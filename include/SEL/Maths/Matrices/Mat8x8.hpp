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

	/// @brief 8x8 matrix of packed Float4E2M1 values.
	using Mat8x8f4 = Mat8x8<Float4E2M1>;
	/// @brief 8x8 matrix of Float8E4M3 values (the default FP8 format).
	using Mat8x8f8 = Mat8x8<Float8E4M3>;
	/// @brief 8x8 matrix of packed Float4E2M1 values, with an explicit format name.
	using Mat8x8f4e2m1 = Mat8x8<Float4E2M1>;
	/// @brief 8x8 matrix of Float8E4M3 values, with an explicit format name.
	using Mat8x8f8e4m3 = Mat8x8<Float8E4M3>;
	/// @brief 8x8 matrix of Float8E5M2 values.
	using Mat8x8f8e5m2 = Mat8x8<Float8E5M2>;

}
