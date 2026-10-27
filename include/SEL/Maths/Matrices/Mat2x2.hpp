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

	/// @brief 2x2 matrix of packed Float4E2M1 values.
	using Mat2x2f4 = Mat2x2<Float4E2M1>;
	/// @brief 2x2 matrix of Float8E4M3 values (the default FP8 format).
	using Mat2x2f8 = Mat2x2<Float8E4M3>;
	/// @brief 2x2 matrix of packed Float4E2M1 values, with an explicit format name.
	using Mat2x2f4e2m1 = Mat2x2<Float4E2M1>;
	/// @brief 2x2 matrix of Float8E4M3 values, with an explicit format name.
	using Mat2x2f8e4m3 = Mat2x2<Float8E4M3>;
	/// @brief 2x2 matrix of Float8E5M2 values.
	using Mat2x2f8e5m2 = Mat2x2<Float8E5M2>;

}
