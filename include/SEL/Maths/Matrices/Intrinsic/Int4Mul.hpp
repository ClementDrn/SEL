// Intrinsic multiplication for packed square signed four-bit matrices.
#pragma once

#include <immintrin.h>
#include <cstddef>
#include <cstring>

#include "SEL/Maths/Matrices/PackedInt4Matrix.hpp"

namespace sel::utils {

	/// @brief Multiply 4x4, 8x8, 16x16, or 32x32 packed matrices modulo 16.
	/// Destination storage must be distinct from both inputs.
	template <std::size_t Size, class Product, class Left, class Right>
	inline void mulMatrixInt4Simd(Product& dst, const Left& a, const Right& b)
	{
		static_assert(Size == 4 || Size == 8 || Size == 16 || Size == 32,
			"Packed int4 SIMD supports square sizes 4, 8, 16, and 32");
		constexpr std::size_t groups = Size < 8 ? 1 : Size / 8;
		constexpr std::size_t packedGroupBytes = Size < 8 ? Size / 2 : 4;
		const auto* left = PackedInt4Access::data(a);
		const auto* right = PackedInt4Access::data(b);
		auto* output = PackedInt4Access::data(dst);
		const __m128i nibbleMask = _mm_set1_epi8(0x0f);
		const __m128i laneMask = _mm_set1_epi16(0x0f);

		// Expand rhs once, then reuse its vectors across all output rows.
		// The 4x4 case loads two bytes per row and leaves four lanes zero.
		__m128i rightRows[Size][groups];
		for (std::size_t inner = 0; inner < Size; ++inner)
		{
			for (std::size_t group = 0; group < groups; ++group)
			{
				__m128i packed = _mm_setzero_si128();
				std::memcpy(&packed, right + inner * (Size / 2) + group * 4, packedGroupBytes);
				const __m128i low = _mm_and_si128(packed, nibbleMask);
				const __m128i high = _mm_and_si128(_mm_srli_epi16(packed, 4), nibbleMask);
				rightRows[inner][group] = _mm_cvtepu8_epi16(_mm_unpacklo_epi8(low, high));
			}
		}

		for (std::size_t row = 0; row < Size; ++row)
		{
			__m128i sums[groups];
			for (std::size_t group = 0; group < groups; ++group)
			{
				sums[group] = _mm_setzero_si128();
			}
			for (std::size_t inner = 0; inner < Size; ++inner)
			{
				const unsigned int byte = left[row * (Size / 2) + inner / 2];
				const __m128i value = _mm_set1_epi16((byte >> ((inner % 2) * 4)) & 0x0f);
				// Unsigned residues have the same low four product bits as signed
				// int4 values. Even the largest sum is only 32 * 15 * 15 = 7200.
				for (std::size_t group = 0; group < groups; ++group)
				{
					sums[group] = _mm_add_epi16(sums[group], _mm_mullo_epi16(value, rightRows[inner][group]));
				}
			}
			for (std::size_t group = 0; group < groups; ++group)
			{
				const __m128i bytes = _mm_packus_epi16(_mm_and_si128(sums[group], laneMask), _mm_setzero_si128());
				// Each pair becomes low + 16 * high, at most 255. Neither packing
				// nor the multiply-add can saturate these masked values.
				const __m128i pairs = _mm_maddubs_epi16(bytes, _mm_set1_epi16(0x1001));
				const __m128i packed = _mm_packus_epi16(pairs, _mm_setzero_si128());
				std::memcpy(output + row * (Size / 2) + group * 4, &packed, packedGroupBytes);
			}
		}
	}

}
