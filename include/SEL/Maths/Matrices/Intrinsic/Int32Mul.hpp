// Specialized small matrix kernels retained after generic-backend comparisons.
#pragma once

#include <immintrin.h>
#include <cstddef>
#include <cstring>

namespace sel::utils {

	/// @brief Multiply 1x2 by 2x2 using the small int SIMD kernel.
	inline void mulMatrix_1x2_2x2(int* dst, const int* a, const int* b)
    {
		// Result is 1x2
		__m128i vResult;	// 4 ints
		__m128 vResultF;	// 4 floats (for shuffling)

		vResult = _mm_mullo_epi32(
			_mm_set_epi32(a[1], a[1], a[0], a[0]),
			_mm_lddqu_si128((__m128i*)b)      // 3, 2, 1, 0
		);

		// Cast to float (it is just interpreted as float, no conversion is done)
		vResultF = _mm_castsi128_ps(vResult);

		// Add 0 & 2 and 1 & 3
		// Note: Computations are done twice.
		vResult = _mm_add_epi32(
			vResult,
			_mm_castps_si128(_mm_shuffle_ps(vResultF, vResultF, _MM_SHUFFLE(1, 0, 3, 2)))
		);

		int tmp[4];
		_mm_storeu_si128((__m128i*)tmp, vResult);
		std::memcpy(dst, tmp, sizeof(int) * 2);
    }

	/// @brief Multiply 2x2 by 2x2 using the small int SIMD kernel.
	inline void mulMatrix_2x2_2x2(int* dst, const int* a, const int* b)
    {
		// Result is 2x2
		__m128i vA, vB, vResult;
		__m128 vAf, vBf;

		vA = _mm_lddqu_si128((__m128i*)a);
		vB = _mm_lddqu_si128((__m128i*)b);

		vAf = _mm_castsi128_ps(vA);
		vBf = _mm_castsi128_ps(vB);

		vResult = _mm_mullo_epi32(
			_mm_castps_si128(_mm_shuffle_ps(vAf, vAf, _MM_SHUFFLE(2, 2, 0, 0))),
			_mm_castps_si128(_mm_shuffle_ps(vBf, vBf, _MM_SHUFFLE(1, 0, 1, 0)))
		);

		vResult = _mm_add_epi32(vResult, _mm_mullo_epi32(
			_mm_castps_si128(_mm_shuffle_ps(vAf, vAf, _MM_SHUFFLE(3, 3, 1, 1))),
			_mm_castps_si128(_mm_shuffle_ps(vBf, vBf, _MM_SHUFFLE(3, 2, 3, 2))))
		);

		_mm_storeu_si128((__m128i*)dst, vResult);
	}

	/// @brief Multiply 3x2 by 2x2 using the small int SIMD kernel.
	inline void mulMatrix_3x2_2x2(int* dst, const int* a, const int* b)
	{
		// Result is 3x2
		mulMatrix_2x2_2x2(&dst[0], &a[0], b);
		mulMatrix_1x2_2x2(&dst[4], &a[4], b);
	}

	/// @brief Multiply 4x2 by 2x2 using the small int SIMD kernel.
	inline void mulMatrix_4x2_2x2(int* dst, const int* a, const int* b)
	{
		// Result is 4x2
		mulMatrix_2x2_2x2(&dst[0], &a[0], b);
		mulMatrix_2x2_2x2(&dst[4], &a[4], b);
	}

	/// @brief Multiply 1x2 by 2x4 using the small int SIMD kernel.
	inline void mulMatrix_1x2_2x4(int* dst, const int* a, const int* b)
	{
		// Result is 1x4
		__m128i vB, vResult;

		// Row 0 of b
		vB = _mm_lddqu_si128((__m128i*)&b[0]);
		vResult = _mm_mullo_epi32(
			_mm_set1_epi32(a[0]),		// The register is filled with the first element of a
			vB
		);
		// Row 1 of b
		vB = _mm_lddqu_si128((__m128i*)&b[4]);
		vResult = _mm_add_epi32(vResult, _mm_mullo_epi32(
			_mm_set1_epi32(a[1]),
			vB
		));

		_mm_storeu_si128((__m128i*)dst, vResult);
	}

	/// @brief Multiply 1x3 by 3x4 using the small int SIMD kernel.
	inline void mulMatrix_1x3_3x4(int* dst, const int* a, const int* b)
    {
		// Result is 1x4
		__m128i vB, vResult;

		// Row 0 of b
		vB = _mm_lddqu_si128((__m128i*)&b[0]);
		vResult = _mm_mullo_epi32(
			_mm_set1_epi32(a[0]),
			vB
		);
		// Row 1 of b
		vB = _mm_lddqu_si128((__m128i*)&b[4]);
		vResult = _mm_add_epi32(vResult, _mm_mullo_epi32(
			_mm_set1_epi32(a[1]),
			vB
		));
		// Row 2 of b
		vB = _mm_lddqu_si128((__m128i*)&b[8]);
		vResult = _mm_add_epi32(vResult, _mm_mullo_epi32(
			_mm_set1_epi32(a[2]),
			vB
		));

		_mm_storeu_si128((__m128i*)dst, vResult);
    }

	/// @brief Multiply 1x4 by 4x4 using the small int SIMD kernel.
	inline void mulMatrix_1x4_4x4(int* dst, const int* a, const int* b)
	{
		// Result is 1x4
		__m128i vB, vResult;

		// Row 0 of b
		vB = _mm_lddqu_si128((__m128i*)&b[0]);
		vResult = _mm_mullo_epi32(
			_mm_set1_epi32(a[0]),
			vB
		);
		// Row 1 of b
		vB = _mm_lddqu_si128((__m128i*)&b[4]);
		vResult = _mm_add_epi32(vResult, _mm_mullo_epi32(
			_mm_set1_epi32(a[1]),
			vB
		));
		// Row 2 of b
		vB = _mm_lddqu_si128((__m128i*)&b[8]);
		vResult = _mm_add_epi32(vResult, _mm_mullo_epi32(
			_mm_set1_epi32(a[2]),
			vB
		));
		// Row 3 of b
		vB = _mm_lddqu_si128((__m128i*)&b[12]);
		vResult = _mm_add_epi32(vResult, _mm_mullo_epi32(
			_mm_set1_epi32(a[3]),
			vB
		));

		_mm_storeu_si128((__m128i*)dst, vResult);
	}

	/// @brief Multiply 2x2 by 2x4 using the small int SIMD kernel.
	inline void mulMatrix_2x2_2x4(int* dst, const int* a, const int* b)
	{
		// Result is 2x4
		// We calculate row by row.
		mulMatrix_1x2_2x4(&dst[0], &a[0], b);
		mulMatrix_1x2_2x4(&dst[4], &a[2], b);
	}

	/// @brief Multiply 2x3 by 3x4 using the small int SIMD kernel.
	inline void mulMatrix_2x3_3x4(int* dst, const int* a, const int* b)
	{
		// Result is 2x4
		// We calculate row by row.
		mulMatrix_1x3_3x4(&dst[0], &a[0], b);
		mulMatrix_1x3_3x4(&dst[4], &a[3], b);
	}

	/// @brief Multiply 2x4 by 4x4 using the small int SIMD kernel.
	inline void mulMatrix_2x4_4x4(int* dst, const int* a, const int* b)
	{
		// Result is 2x4
		// We calculate row by row.
		mulMatrix_1x4_4x4(&dst[0], &a[0], b);
		mulMatrix_1x4_4x4(&dst[4], &a[4], b);
	}

	/// @brief Multiply 3x2 by 2x4 using the small int SIMD kernel.
	inline void mulMatrix_3x2_2x4(int* dst, const int* a, const int* b)
	{
		// Result is 3x4
		// We calculate row by row.
		mulMatrix_1x2_2x4(&dst[0], &a[0], b);
		mulMatrix_1x2_2x4(&dst[4], &a[2], b);
		mulMatrix_1x2_2x4(&dst[8], &a[4], b);
	}

	/// @brief Multiply 3x3 by 3x4 using the small int SIMD kernel.
	inline void mulMatrix_3x3_3x4(int* dst, const int* a, const int* b)
	{
		// Result is 3x4
		// We calculate row by row.
		mulMatrix_1x3_3x4(&dst[0], &a[0], b);
		mulMatrix_1x3_3x4(&dst[4], &a[3], b);
		mulMatrix_1x3_3x4(&dst[8], &a[6], b);
	}

	/// @brief Multiply 3x4 by 4x4 using the small int SIMD kernel.
	inline void mulMatrix_3x4_4x4(int* dst, const int* a, const int* b)
	{
		// Result is 3x4
		// We calculate row by row.
		mulMatrix_1x4_4x4(&dst[0], &a[0], b);
		mulMatrix_1x4_4x4(&dst[4], &a[4], b);
		mulMatrix_1x4_4x4(&dst[8], &a[8], b);
	}

	/// @brief Multiply 4x2 by 2x4 using the small int SIMD kernel.
	inline void mulMatrix_4x2_2x4(int* dst, const int* a, const int* b)
	{
		// Result is 4x4
		// We calculate 2-rows blocks each at a time.
		mulMatrix_2x2_2x4(&dst[0], &a[0], b);
		mulMatrix_2x2_2x4(&dst[8], &a[4], b);
	}

	/// @brief Multiply 4x3 by 3x4 using the small int SIMD kernel.
	inline void mulMatrix_4x3_3x4(int* dst, const int* a, const int* b)
	{
		// Result is 4x4
		// We calculate row by row.
		mulMatrix_1x3_3x4(&dst[0], &a[0], b);
		mulMatrix_1x3_3x4(&dst[4], &a[3], b);
		mulMatrix_1x3_3x4(&dst[8], &a[6], b);
		mulMatrix_1x3_3x4(&dst[12], &a[9], b);
	}

	/// @brief Multiply 4x4 by 4x4 using the small int SIMD kernel.
	inline void mulMatrix_4x4_4x4(int* dst, const int* a, const int* b)
	{
		// Result is 4x4
		// We calculate row by row.
		mulMatrix_1x4_4x4(&dst[0], &a[0], b);
		mulMatrix_1x4_4x4(&dst[4], &a[4], b);
		mulMatrix_1x4_4x4(&dst[8], &a[8], b);
		mulMatrix_1x4_4x4(&dst[12], &a[12], b);
	}

}
