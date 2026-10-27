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

	/// @brief 16x16 matrix of packed Float4E2M1 values.
	using Mat16x16f4 = Mat16x16<Float4E2M1>;
	/// @brief 16x16 matrix of Float8E4M3 values (the default FP8 format).
	using Mat16x16f8 = Mat16x16<Float8E4M3>;
	/// @brief 16x16 matrix of packed Float4E2M1 values, with an explicit format name.
	using Mat16x16f4e2m1 = Mat16x16<Float4E2M1>;
	/// @brief 16x16 matrix of Float8E4M3 values, with an explicit format name.
	using Mat16x16f8e4m3 = Mat16x16<Float8E4M3>;
	/// @brief 16x16 matrix of Float8E5M2 values.
	using Mat16x16f8e5m2 = Mat16x16<Float8E5M2>;

}
