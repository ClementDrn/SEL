// Rectangular SSE4.1 kernels. Objects require only natural scalar alignment.
#pragma once

#include <immintrin.h>
#include <cstddef>

namespace sel::utils {

	/// @brief Accumulate independent output columns, then handle a scalar tail.
	/// Each output visits inner coordinates in order; no partial sums are reduced.
	template <std::size_t Rows, std::size_t Inner, std::size_t Columns>
	inline void mulMatrixRectangular(Matrix<float, Rows, Columns>& dst,
		const Matrix<float, Rows, Inner>& a, const Matrix<float, Inner, Columns>& b)
	{
		constexpr std::size_t groups = Columns >= 16 ? 4 : (Columns >= 8 ? 2 : 1);
		constexpr std::size_t block = 4 * groups;
		for (std::size_t row = 0; row < Rows; ++row)
		{
			std::size_t column = 0;
			for (; column + block <= Columns; column += block)
			{
				__m128 sums[groups];
				const __m128 first = _mm_set1_ps(a[row][0]);
				for (std::size_t group = 0; group < groups; ++group)
					sums[group] = _mm_mul_ps(first, _mm_loadu_ps(&b[0][column + 4 * group]));
				for (std::size_t inner = 1; inner < Inner; ++inner)
				{
					const __m128 left = _mm_set1_ps(a[row][inner]);
					for (std::size_t group = 0; group < groups; ++group)
						sums[group] = _mm_add_ps(sums[group], _mm_mul_ps(left, _mm_loadu_ps(&b[inner][column + 4 * group])));
				}
				for (std::size_t group = 0; group < groups; ++group)
					_mm_storeu_ps(&dst[row][column + 4 * group], sums[group]);
			}
			// Smaller complete vectors avoid discarding SIMD opportunities when
			// the output width is not divisible by the main block width.
			for (; column + 4 <= Columns; column += 4)
			{
				__m128 sum = _mm_mul_ps(_mm_set1_ps(a[row][0]), _mm_loadu_ps(&b[0][column]));
				for (std::size_t inner = 1; inner < Inner; ++inner)
					sum = _mm_add_ps(sum, _mm_mul_ps(_mm_set1_ps(a[row][inner]), _mm_loadu_ps(&b[inner][column])));
				_mm_storeu_ps(&dst[row][column], sum);
			}
			for (; column < Columns; ++column)
			{
				dst[row][column] = a[row][0] * b[0][column];
				for (std::size_t inner = 1; inner < Inner; ++inner)
					dst[row][column] += a[row][inner] * b[inner][column];
			}
		}
	}

	/// @brief Accumulate independent output columns, then handle a scalar tail.
	/// Each output visits inner coordinates in order; no partial sums are reduced.
	template <std::size_t Rows, std::size_t Inner, std::size_t Columns>
	inline void mulMatrixRectangular(Matrix<int, Rows, Columns>& dst,
		const Matrix<int, Rows, Inner>& a, const Matrix<int, Inner, Columns>& b)
	{
		constexpr std::size_t groups = 1;
		constexpr std::size_t block = 4 * groups;
		for (std::size_t row = 0; row < Rows; ++row)
		{
			std::size_t column = 0;
			for (; column + block <= Columns; column += block)
			{
				__m128i sums[groups];
				const __m128i first = _mm_set1_epi32(a[row][0]);
				for (std::size_t group = 0; group < groups; ++group)
					sums[group] = _mm_mullo_epi32(first, _mm_loadu_si128(reinterpret_cast<const __m128i*>(&b[0][column + 4 * group])));
				for (std::size_t inner = 1; inner < Inner; ++inner)
				{
					const __m128i left = _mm_set1_epi32(a[row][inner]);
					for (std::size_t group = 0; group < groups; ++group)
						sums[group] = _mm_add_epi32(sums[group], _mm_mullo_epi32(left, _mm_loadu_si128(reinterpret_cast<const __m128i*>(&b[inner][column + 4 * group]))));
				}
				for (std::size_t group = 0; group < groups; ++group)
					_mm_storeu_si128(reinterpret_cast<__m128i*>(&dst[row][column + 4 * group]), sums[group]);
			}
			// Smaller complete vectors avoid discarding SIMD opportunities when
			// the output width is not divisible by the main block width.
			for (; column + 4 <= Columns; column += 4)
			{
				__m128i sum = _mm_mullo_epi32(_mm_set1_epi32(a[row][0]), _mm_loadu_si128(reinterpret_cast<const __m128i*>(&b[0][column])));
				for (std::size_t inner = 1; inner < Inner; ++inner)
					sum = _mm_add_epi32(sum, _mm_mullo_epi32(_mm_set1_epi32(a[row][inner]), _mm_loadu_si128(reinterpret_cast<const __m128i*>(&b[inner][column]))));
				_mm_storeu_si128(reinterpret_cast<__m128i*>(&dst[row][column]), sum);
			}
			for (; column < Columns; ++column)
			{
				dst[row][column] = a[row][0] * b[0][column];
				for (std::size_t inner = 1; inner < Inner; ++inner)
					dst[row][column] += a[row][inner] * b[inner][column];
			}
		}
	}

}
