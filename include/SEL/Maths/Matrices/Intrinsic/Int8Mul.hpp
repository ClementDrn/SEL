// Intrinsic matrix multiplications for signed 8-bit integer values.
#pragma once

#include <immintrin.h>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <type_traits>


namespace sel::utils {

	/// @brief Multiply signed byte matrices in groups of eight columns.
	///
	/// Products wrap to the signed 8-bit range, without saturation.
	///
	/// @tparam Rows is the number of rows of the result.
	/// @tparam Inner is the number of values in each dot product.
	/// @tparam Columns is the number of columns of the result.
	/// @param dst is the destination matrix, distinct from both inputs.
	/// @param a is the first matrix.
	/// @param b is the second matrix.
	///
	template <std::size_t Rows, std::size_t Inner, std::size_t Columns, class Product, class Left, class Right>
	inline void mulMatrixInt8Simd(Product& dst, const Left& a, const Right& b)
	{

		for (std::size_t row = 0; row < Rows; ++row)
		{
			// Separate full vectors and the tail so every copy size is a compile-
			// time constant. A dynamic memcpy size can become a call per term.
			const auto multiplyColumns = [&](auto width, std::size_t column)
			{
				constexpr std::size_t count = decltype(width)::value;
				__m128i vResult = _mm_setzero_si128();
				for (std::size_t inner = 0; inner < Inner; ++inner)
				{
					// Copy only valid bytes; short rows need neither padding nor alignment.
					__m128i vBytes = _mm_setzero_si128();
					std::memcpy(&vBytes, &b[inner][column], count);
					const __m128i vB = _mm_cvtepi8_epi16(vBytes);
					const __m128i vA = _mm_set1_epi16(a[row][inner]);
					vResult = _mm_add_epi16(vResult, _mm_mullo_epi16(vA, vB));
				}

				// Sixteen-bit accumulation preserves the low byte even when it wraps.
				// Mask before packing so unsigned saturation cannot alter that byte.
				vResult = _mm_and_si128(vResult, _mm_set1_epi16(0xff));
				const __m128i vBytes = _mm_packus_epi16(vResult, _mm_setzero_si128());
				std::memcpy(&dst[row][column], &vBytes, count);
			};
			for (std::size_t column = 0; column + 8 <= Columns; column += 8)
				multiplyColumns(std::integral_constant<std::size_t, 8>{}, column);
			if constexpr (Columns % 8 != 0)
				multiplyColumns(std::integral_constant<std::size_t, Columns % 8>{}, Columns - Columns % 8);
		}
	}

}
