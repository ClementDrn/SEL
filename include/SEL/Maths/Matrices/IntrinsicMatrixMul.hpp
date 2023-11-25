// Intrinsic matrix multiplications for float and int.
#pragma once

#include <immintrin.h>
#include <vcruntime_string.h>


namespace sel::utils {

	// --- 1x2 result ----------------------------------------------------------

    inline void mulMatrix_1x2_2x2(float* dst, const float* a, const float* b)
    {
        // Result is 1x2
        __m128 vResult;     // 4 floats

        vResult = _mm_mul_ps(
            _mm_set_ps(a[1], a[1], a[0], a[0]),
            _mm_load_ps(b)      // 3, 2, 1, 0
        );
		
		// Add 0 & 2 and 1 & 3
		// Note: Computations are done twice.
		vResult = _mm_add_ps(
			vResult,
			_mm_shuffle_ps(vResult, vResult, _MM_SHUFFLE(1, 0, 3, 2))
		);
		
        float tmp[4];
        _mm_store_ps(tmp, vResult);
        memcpy(dst, tmp, sizeof(float) * 2);
    }

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
		_mm_store_si128((__m128i*)tmp, vResult);
		memcpy(dst, tmp, sizeof(int) * 2);
    }


    inline void mulMatrix_1x3_3x2(float* dst, const float* a, const float* b)
    {
		// Result is 1x2
		// First we do 1x2_2x2, then 1x1_1x2
        __m128 vResult, vResult1, vResult2;

        vResult1 = _mm_mul_ps(
            _mm_set_ps(a[1], a[1], a[0], a[0]),
            _mm_load_ps(b)      // 3, 2, 1, 0
        );

        // Add 0 & 2 and 1 & 3
		// Note: Computations are done twice.
        vResult1 = _mm_add_ps(
            vResult1,
            _mm_shuffle_ps(vResult1, vResult1, _MM_SHUFFLE(1, 0, 3, 2))
        );

		// 1x1_1x2
		vResult2 = _mm_mul_ps(
			_mm_set_ps(0.0f, 0.0f, a[2], a[2]),		// Putting numbers at the end, will place them at the beginning of the returned array.
            _mm_set_ps(0.0f, 0.0f, b[5], b[4])
		);
		
		// Add the two sub results
		vResult = _mm_add_ps(
			vResult1,
			vResult2
		);

		float tmp[4];
        _mm_store_ps(tmp, vResult);
        memcpy(dst, tmp, sizeof(float) * 2);
    }

    inline void mulMatrix_1x3_3x2(int* dst, const int* a, const int* b)
    {
        // Result is 1x2
        // First we do 1x2_2x2, then 1x1_1x2
        __m128i vResult, vResult1, vResult2;
		__m128 vResult1F;

        vResult1 = _mm_mullo_epi32(
			_mm_set_epi32(a[1], a[1], a[0], a[0]),
			_mm_lddqu_si128((__m128i*)&b[0])      // 3, 2, 1, 0
		);

		// Cast to float (it is just interpreted as float, no conversion is done)
		vResult1F = _mm_castsi128_ps(vResult1);

        // Add 0 & 2 and 1 & 3
        vResult1 = _mm_add_epi32(
			vResult1,
			_mm_castps_si128(_mm_shuffle_ps(vResult1F, vResult1F, _MM_SHUFFLE(1, 0, 3, 2)))
		);

		// 1x1_1x2
		vResult2 = _mm_mullo_epi32(
            _mm_set_epi32(0, 0, a[2], a[2]),
            _mm_set_epi32(0, 0, b[5], b[4])
		);

        // Add the two sub results
		vResult = _mm_add_epi32(
            vResult1,
            vResult2
		);

        int tmp[4];
		_mm_store_si128((__m128i*)tmp, vResult);
		memcpy(dst, tmp, sizeof(int) * 2);
    }


    inline void mulMatrix_1x4_4x2(float* dst, const float* a, const float* b)
    {
		// Result is 1x2
        // Matrices are cut in half, 1x2 for a and 2x2 for b.
		__m128 vResult, vResult1, vResult2;

        vResult1 = _mm_mul_ps(
            _mm_set_ps(a[1], a[1], a[0], a[0]),
            _mm_load_ps(b)      // 3, 2, 1, 0
        );

        vResult2 = _mm_mul_ps(
            _mm_set_ps(a[3], a[3], a[2], a[2]),
            _mm_load_ps(&b[4])      // 3, 2, 1, 0
        );

        vResult = _mm_add_ps(
            vResult1,
            vResult2
        );

        // Add 0 & 2 and 1 & 3
        // Note: Computations are done twice.
        vResult = _mm_add_ps(
            vResult,
            _mm_shuffle_ps(vResult, vResult, _MM_SHUFFLE(1, 0, 3, 2))
        );

        float tmp[4];
        _mm_store_ps(tmp, vResult);
        memcpy(dst, tmp, sizeof(float) * 2);
	}

	inline void mulMatrix_1x4_4x2(int* dst, const int* a, const int* b)
	{
		// Result is 1x2
		// Matrices are cut in half, 1x2 for a and 2x2 for b.
		__m128i vResult, vResult1, vResult2;
		__m128 vResultF;

		vResult1 = _mm_mullo_epi32(
			_mm_set_epi32(a[1], a[1], a[0], a[0]),
			_mm_lddqu_si128((__m128i*)b)      // 3, 2, 1, 0
		);

		vResult2 = _mm_mullo_epi32(
			_mm_set_epi32(a[3], a[3], a[2], a[2]),
			_mm_lddqu_si128((__m128i*)&b[4])      // 3, 2, 1, 0
		);

		vResult = _mm_add_epi32(
			vResult1,
			vResult2
		);

		// Cast to float (it is just interpreted as float, no conversion is done)
		vResultF = _mm_castsi128_ps(vResult);

		// Add 0 & 2 and 1 & 3
		vResult = _mm_add_epi32(
			vResult,
			_mm_castps_si128(_mm_shuffle_ps(vResultF, vResultF, _MM_SHUFFLE(1, 0, 3, 2)))
		);

		int tmp[4];
		_mm_store_si128((__m128i*)tmp, vResult);
		memcpy(dst, tmp, sizeof(int) * 2);
	}



	// --- 2x2 result ----------------------------------------------------------

	inline void mulMatrix_2x2_2x2(float* dst, const float* a, const float* b)
	{
        // Result is 2x2
		__m128 vA, vB, vResult;

		vA = _mm_load_ps(a);
		vB = _mm_load_ps(b);

		vResult = _mm_mul_ps(
			_mm_shuffle_ps(vA, vA, _MM_SHUFFLE(2, 2, 0, 0)),
			_mm_shuffle_ps(vB, vB, _MM_SHUFFLE(1, 0, 1, 0))
		);

		vResult = _mm_add_ps(vResult, _mm_mul_ps(
			_mm_shuffle_ps(vA, vA, _MM_SHUFFLE(3, 3, 1, 1)),
			_mm_shuffle_ps(vB, vB, _MM_SHUFFLE(3, 2, 3, 2)))
		);
		
		_mm_store_ps(dst, vResult);
	}

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

		_mm_store_si128((__m128i*)dst, vResult);
	}


    inline void mulMatrix_2x3_3x2(float* dst, const float* a, const float* b)
    {
		// Result is 2x2
        mulMatrix_1x3_3x2(&dst[0], &a[0], b);
        mulMatrix_1x3_3x2(&dst[2], &a[3], b);
    }

    inline void mulMatrix_2x3_3x2(int* dst, const int* a, const int* b)
	{
        // Result is 2x2
		mulMatrix_1x3_3x2(&dst[0], &a[0], b);
		mulMatrix_1x3_3x2(&dst[2], &a[3], b);
    }


    inline void mulMatrix_2x4_4x2(float* dst, const float* a, const float* b)
    {
		// Result is 2x2
        mulMatrix_1x4_4x2(&dst[0], &a[0], b);
        mulMatrix_1x4_4x2(&dst[2], &a[4], b);
    }

    inline void mulMatrix_2x4_4x2(int* dst, const int* a, const int* b)
    {
        // Result is 2x2
        mulMatrix_1x4_4x2(&dst[0], &a[0], b);
        mulMatrix_1x4_4x2(&dst[2], &a[4], b);
    }



	// --- 3x2 result ----------------------------------------------------------

    inline void mulMatrix_3x2_2x2(float* dst, const float* a, const float* b)
    {
        // Result is 3x2
        mulMatrix_2x2_2x2(&dst[0], &a[0], b);
        mulMatrix_1x2_2x2(&dst[4], &a[4], b);
    }

    inline void mulMatrix_3x2_2x2(int* dst, const int* a, const int* b)
	{
		// Result is 3x2
		mulMatrix_2x2_2x2(&dst[0], &a[0], b);
		mulMatrix_1x2_2x2(&dst[4], &a[4], b);
	}


    inline void mulMatrix_3x3_3x2(float* dst, const float* a, const float* b)
    {
        // Result is 3x2
        mulMatrix_1x3_3x2(&dst[0], &a[0], b);
        mulMatrix_1x3_3x2(&dst[2], &a[3], b);
        mulMatrix_1x3_3x2(&dst[4], &a[6], b);
    }

    inline void mulMatrix_3x3_3x2(int* dst, const int* a, const int* b)
	{
		// Result is 3x2
		mulMatrix_1x3_3x2(&dst[0], &a[0], b);
		mulMatrix_1x3_3x2(&dst[2], &a[3], b);
		mulMatrix_1x3_3x2(&dst[4], &a[6], b);
	}


    inline void mulMatrix_3x4_4x2(float* dst, const float* a, const float* b)
    {
        // Result is 3x2
        mulMatrix_1x4_4x2(&dst[0], &a[0], b);
        mulMatrix_1x4_4x2(&dst[2], &a[4], b);
        mulMatrix_1x4_4x2(&dst[4], &a[8], b);
    }

    inline void mulMatrix_3x4_4x2(int* dst, const int* a, const int* b)
    {
        // Result is 3x2
        mulMatrix_1x4_4x2(&dst[0], &a[0], b);
        mulMatrix_1x4_4x2(&dst[2], &a[4], b);
        mulMatrix_1x4_4x2(&dst[4], &a[8], b);
    }



	// --- 4x2 result ----------------------------------------------------------

    inline void mulMatrix_4x2_2x2(float* dst, const float* a, const float* b)
    {
		// Result is 4x2
		mulMatrix_2x2_2x2(&dst[0], &a[0], b);
		mulMatrix_2x2_2x2(&dst[4], &a[4], b);
    }

    inline void mulMatrix_4x2_2x2(int* dst, const int* a, const int* b)
	{
		// Result is 4x2
		mulMatrix_2x2_2x2(&dst[0], &a[0], b);
		mulMatrix_2x2_2x2(&dst[4], &a[4], b);
	}


    inline void mulMatrix_4x3_3x2(float* dst, const float* a, const float* b)
    {
        // Result is 4x2
        mulMatrix_1x3_3x2(&dst[0], &a[0], b);
        mulMatrix_1x3_3x2(&dst[2], &a[3], b);
        mulMatrix_1x3_3x2(&dst[4], &a[6], b);
        mulMatrix_1x3_3x2(&dst[6], &a[9], b);
    }

    inline void mulMatrix_4x3_3x2(int* dst, const int* a, const int* b)
    {
        // Result is 4x2
        mulMatrix_1x3_3x2(&dst[0], &a[0], b);
        mulMatrix_1x3_3x2(&dst[2], &a[3], b);
        mulMatrix_1x3_3x2(&dst[4], &a[6], b);
        mulMatrix_1x3_3x2(&dst[6], &a[9], b);
    }


    inline void mulMatrix_4x4_4x2(float* dst, const float* a, const float* b)
    {
        // Result is 4x2
        mulMatrix_1x4_4x2(&dst[0], &a[0], b);
        mulMatrix_1x4_4x2(&dst[2], &a[4], b);
        mulMatrix_1x4_4x2(&dst[4], &a[8], b);
        mulMatrix_1x4_4x2(&dst[6], &a[12], b);
    }

    inline void mulMatrix_4x4_4x2(int* dst, const int* a, const int* b)
	{
		// Result is 4x2
		mulMatrix_1x4_4x2(&dst[0], &a[0], b);
		mulMatrix_1x4_4x2(&dst[2], &a[4], b);
		mulMatrix_1x4_4x2(&dst[4], &a[8], b);
		mulMatrix_1x4_4x2(&dst[6], &a[12], b);
	}



	// --- 1x3 result ----------------------------------------------------------

    inline void mulMatrix_1x2_2x3(float* dst, const float* a, const float* b)
    {
        // Result is 1x3
        __m128 vB, vResult;

        // Row 0 of b
        vB = _mm_set_ps(b[0], b[1], b[2], 0.0f);
        vResult = _mm_mul_ps(
            _mm_load_ps1(&a[0]),
            vB
        );
        // Row 1 of b
        vB = _mm_set_ps(b[3], b[4], b[5], 0.0f);
        vResult = _mm_add_ps(vResult, _mm_mul_ps(
            _mm_load_ps1(&a[1]),
            vB
        ));

        float tmp[4];
        _mm_storer_ps(tmp, vResult);
        memcpy(dst, tmp, sizeof(float) * 3);
    }

    inline void mulMatrix_1x2_2x3(int* dst, const int* a, const int* b)
    {
		// Result is 1x3
		__m128i vB, vResult;
		
		// Row 0 of b
		vB = _mm_set_epi32(0, b[2], b[1], b[0]);
		vResult = _mm_mullo_epi32(
			_mm_set1_epi32(a[0]),
			vB
		);
		// Row 1 of b
		vB = _mm_set_epi32(0, b[5], b[4], b[3]);
		vResult = _mm_add_epi32(vResult, _mm_mullo_epi32(
			_mm_set1_epi32(a[1]),
			vB
		));

		int tmp[4];
		_mm_store_si128((__m128i*)tmp, vResult);
		memcpy(dst, tmp, sizeof(int) * 3);
    }


    inline void mulMatrix_1x3_3x3(float* dst, const float* a, const float* b)
    {
		// Result is 1x3
		__m128 vB, vResult;

        // Row 0 of b
        vB = _mm_set_ps(b[0], b[1], b[2], 0.0f);
        vResult = _mm_mul_ps(
            _mm_load_ps1(&a[0]),
            vB
        );
        // Row 1 of b
		vB = _mm_set_ps(b[3], b[4], b[5], 0.0f);
        vResult = _mm_add_ps(vResult, _mm_mul_ps(
            _mm_load_ps1(&a[1]),
            vB
        ));
        // Row 2 of b
		vB = _mm_set_ps(b[6], b[7], b[8], 0.0f);
        vResult = _mm_add_ps(vResult, _mm_mul_ps(
            _mm_load_ps1(&a[2]),
            vB
        ));
		
		float tmp[4];
		_mm_storer_ps(tmp, vResult);
		memcpy(dst, tmp, sizeof(float) * 3);
    }

    inline void mulMatrix_1x3_3x3(int* dst, const int* a, const int* b)
	{
        // Result is 1x3
		__m128i vB, vResult;

		// Row 0 of b
		vB = _mm_set_epi32(0, b[2], b[1], b[0]);
		vResult = _mm_mullo_epi32(
			_mm_set1_epi32(a[0]),
			vB
		);
		// Row 1 of b
		vB = _mm_set_epi32(0, b[5], b[4], b[3]);
		vResult = _mm_add_epi32(vResult, _mm_mullo_epi32(
			_mm_set1_epi32(a[1]),
			vB
		));
		// Row 2 of b
		vB = _mm_set_epi32(0, b[8], b[7], b[6]);
		vResult = _mm_add_epi32(vResult, _mm_mullo_epi32(
			_mm_set1_epi32(a[2]),
			vB
		));

		int tmp[4];
		_mm_store_si128((__m128i*)tmp, vResult);
		memcpy(dst, tmp, sizeof(int) * 3);
	}

	
    inline void mulMatrix_1x4_4x3(float* dst, const float* a, const float* b)
    {
		// Result is 1x3
		__m128 vB, vResult;

		// Row 0 of b
		vB = _mm_set_ps(b[0], b[1], b[2], 0.0f);
		vResult = _mm_mul_ps(
			_mm_load_ps1(&a[0]),
			vB
		);
		// Row 1 of b
		vB = _mm_set_ps(b[3], b[4], b[5], 0.0f);
		vResult = _mm_add_ps(vResult, _mm_mul_ps(
			_mm_load_ps1(&a[1]),
			vB
		));
		// Row 2 of b
		vB = _mm_set_ps(b[6], b[7], b[8], 0.0f);
		vResult = _mm_add_ps(vResult, _mm_mul_ps(
			_mm_load_ps1(&a[2]),
			vB
		));
		// Row 3 of b
		vB = _mm_set_ps(b[9], b[10], b[11], 0.0f);
		vResult = _mm_add_ps(vResult, _mm_mul_ps(
			_mm_load_ps1(&a[3]),
			vB
		));

		float tmp[4];
		_mm_storer_ps(tmp, vResult);
		memcpy(dst, tmp, sizeof(float) * 3);
    }

    inline void mulMatrix_1x4_4x3(int* dst, const int* a, const int* b)
	{
        // Result is 1x3
        __m128i vB, vResult;

		// Row 0 of b
		vB = _mm_set_epi32(0, b[2], b[1], b[0]);
		vResult = _mm_mullo_epi32(
			_mm_set1_epi32(a[0]),
			vB
		);
		// Row 1 of b
		vB = _mm_set_epi32(0, b[5], b[4], b[3]);
		vResult = _mm_add_epi32(vResult, _mm_mullo_epi32(
			_mm_set1_epi32(a[1]),
			vB
		));
		// Row 2 of b
		vB = _mm_set_epi32(0, b[8], b[7], b[6]);
		vResult = _mm_add_epi32(vResult, _mm_mullo_epi32(
			_mm_set1_epi32(a[2]),
			vB
		));
		// Row 3 of b
		vB = _mm_set_epi32(0, b[11], b[10], b[9]);
		vResult = _mm_add_epi32(vResult, _mm_mullo_epi32(
			_mm_set1_epi32(a[3]),
			vB
		));

		int tmp[4];
		_mm_store_si128((__m128i*)tmp, vResult);
		memcpy(dst, tmp, sizeof(int) * 3);
	}



	// --- 2x3 result ----------------------------------------------------------

    inline void mulMatrix_2x2_2x3(float* dst, const float* a, const float* b)
    {
        // Result is 2x3 
        mulMatrix_1x2_2x3(&dst[0], &a[0], b);
        mulMatrix_1x2_2x3(&dst[3], &a[2], b);
    }

    inline void mulMatrix_2x2_2x3(int* dst, const int* a, const int* b)
    {
        // Result is 2x3 
        mulMatrix_1x2_2x3(&dst[0], &a[0], b);
        mulMatrix_1x2_2x3(&dst[3], &a[2], b);
    }

	
    inline void mulMatrix_2x3_3x3(float* dst, const float* a, const float* b)
    {
        // Result is 2x3 
        mulMatrix_1x3_3x3(&dst[0], &a[0], b);
        mulMatrix_1x3_3x3(&dst[3], &a[3], b);
    }

    inline void mulMatrix_2x3_3x3(int* dst, const int* a, const int* b)
    {
        // Result is 2x3 
        mulMatrix_1x3_3x3(&dst[0], &a[0], b);
        mulMatrix_1x3_3x3(&dst[3], &a[3], b);
    }


	inline void mulMatrix_2x4_4x3(float* dst, const float* a, const float* b)
	{
		// Result is 2x3 
		mulMatrix_1x4_4x3(&dst[0], &a[0], b);
		mulMatrix_1x4_4x3(&dst[3], &a[4], b);
	}

    inline void mulMatrix_2x4_4x3(int* dst, const int* a, const int* b)
	{
		// Result is 2x3 
		mulMatrix_1x4_4x3(&dst[0], &a[0], b);
		mulMatrix_1x4_4x3(&dst[3], &a[4], b);
	}



	// --- 3x3 result ----------------------------------------------------------

	inline void mulMatrix_3x2_2x3(float* dst, const float* a, const float* b)
	{
		// Result is 3x3 
		mulMatrix_1x2_2x3(&dst[0], &a[0], b);
		mulMatrix_1x2_2x3(&dst[3], &a[2], b);
		mulMatrix_1x2_2x3(&dst[6], &a[4], b);
	}

    inline void mulMatrix_3x2_2x3(int* dst, const int* a, const int* b)
    {
        // Result is 3x3 
        mulMatrix_1x2_2x3(&dst[0], &a[0], b);
        mulMatrix_1x2_2x3(&dst[3], &a[2], b);
        mulMatrix_1x2_2x3(&dst[6], &a[4], b);
    }


    inline void mulMatrix_3x3_3x3(float* dst, const float* a, const float* b)
    {
        // Result is 3x3 
		mulMatrix_1x3_3x3(&dst[0], &a[0], b);
		mulMatrix_1x3_3x3(&dst[3], &a[3], b);
		mulMatrix_1x3_3x3(&dst[6], &a[6], b);
    }

    inline void mulMatrix_3x3_3x3(int* dst, const int* a, const int* b)
    {
        // Result is 3x3 
        mulMatrix_1x3_3x3(&dst[0], &a[0], b);
        mulMatrix_1x3_3x3(&dst[3], &a[3], b);
        mulMatrix_1x3_3x3(&dst[6], &a[6], b);
    }


    inline void mulMatrix_3x4_4x3(float* dst, const float* a, const float* b)
    {
		// Result is 3x3
		mulMatrix_1x4_4x3(&dst[0], &a[0], b);
		mulMatrix_1x4_4x3(&dst[3], &a[4], b);
		mulMatrix_1x4_4x3(&dst[6], &a[8], b);
    }

    inline void mulMatrix_3x4_4x3(int* dst, const int* a, const int* b)
	{
		// Result is 3x3
		mulMatrix_1x4_4x3(&dst[0], &a[0], b);
		mulMatrix_1x4_4x3(&dst[3], &a[4], b);
		mulMatrix_1x4_4x3(&dst[6], &a[8], b);
	}



	// --- 4x3 result ----------------------------------------------------------
	
    inline void mulMatrix_4x2_2x3(float* dst, const float* a, const float* b)
    {
		// Result is 4x3
		mulMatrix_2x2_2x3(&dst[0], &a[0], b);
		mulMatrix_2x2_2x3(&dst[6], &a[4], b);
    }

    inline void mulMatrix_4x2_2x3(int* dst, const int* a, const int* b)
    {
        // Result is 4x3
        mulMatrix_2x2_2x3(&dst[0], &a[0], b);
        mulMatrix_2x2_2x3(&dst[6], &a[4], b);
    }


	inline void mulMatrix_4x3_3x3(float* dst, const float* a, const float* b)
	{
		// Result is 4x3 
		mulMatrix_1x3_3x3(&dst[0], &a[0], b);
		mulMatrix_1x3_3x3(&dst[3], &a[3], b);
		mulMatrix_1x3_3x3(&dst[6], &a[6], b);
		mulMatrix_1x3_3x3(&dst[9], &a[9], b);
	}

    inline void mulMatrix_4x3_3x3(int* dst, const int* a, const int* b)
	{
		// Result is 4x3 
		mulMatrix_1x3_3x3(&dst[0], &a[0], b);
		mulMatrix_1x3_3x3(&dst[3], &a[3], b);
		mulMatrix_1x3_3x3(&dst[6], &a[6], b);
		mulMatrix_1x3_3x3(&dst[9], &a[9], b);
	}


    inline void mulMatrix_4x4_4x3(float* dst, const float* a, const float* b)
    {
		// Result is 4x3
        mulMatrix_1x4_4x3(&dst[0], &a[0], b);
        mulMatrix_1x4_4x3(&dst[3], &a[4], b);
        mulMatrix_1x4_4x3(&dst[6], &a[8], b);
        mulMatrix_1x4_4x3(&dst[9], &a[12], b);
    }

    inline void mulMatrix_4x4_4x3(int* dst, const int* a, const int* b)
    {
		// Result is 4x3
		mulMatrix_1x4_4x3(&dst[0], &a[0], b);
		mulMatrix_1x4_4x3(&dst[3], &a[4], b);
		mulMatrix_1x4_4x3(&dst[6], &a[8], b);
		mulMatrix_1x4_4x3(&dst[9], &a[12], b);
    }



	// --- 1x4 result ----------------------------------------------------------

    inline void mulMatrix_1x2_2x4(float* dst, const float* a, const float* b)
    {
		// Result is 1x4
		__m128 vB, vResult;

        // Row 0 of b
        vB = _mm_load_ps(&b[0]);
        vResult = _mm_mul_ps(
			_mm_load_ps1(&a[0]),    // The register is filled with the first element of a
            vB
        );
        // Row 1 of b
        vB = _mm_load_ps(&b[4]);
        vResult = _mm_add_ps(vResult, _mm_mul_ps(
            _mm_load_ps1(&a[1]),
            vB
        ));

		_mm_store_ps(dst, vResult);
    }

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

		_mm_store_si128((__m128i*)dst, vResult);
	}


    inline void mulMatrix_1x3_3x4(float* dst, const float* a, const float* b)
    {
        // Result is 1x4
        __m128 vB, vResult;

        // Row 0 of b
        vB = _mm_load_ps(&b[0]);
        vResult = _mm_mul_ps(
            _mm_load_ps1(&a[0]),
            vB
        );
        // Row 1 of b
        vB = _mm_load_ps(&b[4]);
        vResult = _mm_add_ps(vResult, _mm_mul_ps(
            _mm_load_ps1(&a[1]),
            vB
        ));
        // Row 2 of b
        vB = _mm_load_ps(&b[8]);
        vResult = _mm_add_ps(vResult, _mm_mul_ps(
            _mm_load_ps1(&a[2]),
            vB
        ));

        _mm_store_ps(dst, vResult);
    }

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

		_mm_store_si128((__m128i*)dst, vResult);
    }


    inline void mulMatrix_1x4_4x4(float* dst, const float* a, const float* b)
    {
        // Result is 1x4
		__m128 vB, vResult;
		
		// Row 0 of b
		vB = _mm_load_ps(&b[0]);
        vResult = _mm_mul_ps(
            _mm_load_ps1(&a[0]),
            vB
        );
        // Row 1 of b
        vB = _mm_load_ps(&b[4]);
        vResult = _mm_add_ps(vResult, _mm_mul_ps(
            _mm_load_ps1(&a[1]),
            vB
        ));
        // Row 2 of b
        vB = _mm_load_ps(&b[8]);
        vResult = _mm_add_ps(vResult, _mm_mul_ps(
            _mm_load_ps1(&a[2]),
            vB
        ));
        // Row 3 of b
        vB = _mm_load_ps(&b[12]);
        vResult = _mm_add_ps(vResult, _mm_mul_ps(
            _mm_load_ps1(&a[3]),
            vB
        ));
		
        _mm_store_ps(dst, vResult);
    }

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

		_mm_store_si128((__m128i*)dst, vResult);
	}



	// --- 2x4 result ----------------------------------------------------------

    inline void mulMatrix_2x2_2x4(float* dst, const float* a, const float* b)
    {
		// Result is 2x4
        // We calculate row by row.
        mulMatrix_1x2_2x4(&dst[0], &a[0], b);
		mulMatrix_1x2_2x4(&dst[4], &a[2], b);
    }

	inline void mulMatrix_2x2_2x4(int* dst, const int* a, const int* b)
	{
		// Result is 2x4
		// We calculate row by row.
		mulMatrix_1x2_2x4(&dst[0], &a[0], b);
		mulMatrix_1x2_2x4(&dst[4], &a[2], b);
	}


	inline void mulMatrix_2x3_3x4(float* dst, const float* a, const float* b)
	{
		// Result is 2x4
        // We calculate row by row.
        mulMatrix_1x3_3x4(&dst[0], &a[0], b);
		mulMatrix_1x3_3x4(&dst[4], &a[3], b);
	}

	inline void mulMatrix_2x3_3x4(int* dst, const int* a, const int* b)
	{
		// Result is 2x4
		// We calculate row by row.
		mulMatrix_1x3_3x4(&dst[0], &a[0], b);
		mulMatrix_1x3_3x4(&dst[4], &a[3], b);
	}


    inline void mulMatrix_2x4_4x4(float* dst, const float* a, const float* b)
    {
        // Result is 2x4
        // We calculate row by row.
        mulMatrix_1x4_4x4(&dst[0], &a[0], b);
        mulMatrix_1x4_4x4(&dst[4], &a[4], b);
    }

	inline void mulMatrix_2x4_4x4(int* dst, const int* a, const int* b)
	{
		// Result is 2x4
		// We calculate row by row.
		mulMatrix_1x4_4x4(&dst[0], &a[0], b);
		mulMatrix_1x4_4x4(&dst[4], &a[4], b);
	}

	
	// --- 3x4 result ----------------------------------------------------------

    inline void mulMatrix_3x2_2x4(float* dst, const float* a, const float* b)
    {
		// Result is 3x4
		// We calculate row by row.
		mulMatrix_1x2_2x4(&dst[0], &a[0], b);
		mulMatrix_1x2_2x4(&dst[4], &a[2], b);
		mulMatrix_1x2_2x4(&dst[8], &a[4], b);
    }

	inline void mulMatrix_3x2_2x4(int* dst, const int* a, const int* b)
	{
		// Result is 3x4
		// We calculate row by row.
		mulMatrix_1x2_2x4(&dst[0], &a[0], b);
		mulMatrix_1x2_2x4(&dst[4], &a[2], b);
		mulMatrix_1x2_2x4(&dst[8], &a[4], b);
	}


    inline void mulMatrix_3x3_3x4(float* dst, const float* a, const float* b)
    {
		// Result is 3x4
		// We calculate row by row.
		mulMatrix_1x3_3x4(&dst[0], &a[0], b);
		mulMatrix_1x3_3x4(&dst[4], &a[3], b);
		mulMatrix_1x3_3x4(&dst[8], &a[6], b);
	}

	inline void mulMatrix_3x3_3x4(int* dst, const int* a, const int* b)
	{
		// Result is 3x4
		// We calculate row by row.
		mulMatrix_1x3_3x4(&dst[0], &a[0], b);
		mulMatrix_1x3_3x4(&dst[4], &a[3], b);
		mulMatrix_1x3_3x4(&dst[8], &a[6], b);
	}


    inline void mulMatrix_3x4_4x4(float* dst, const float* a, const float* b)
    {
        // Result is 3x4
        // We calculate row by row.
        mulMatrix_1x4_4x4(&dst[0], &a[0], b);
        mulMatrix_1x4_4x4(&dst[4], &a[4], b);
        mulMatrix_1x4_4x4(&dst[8], &a[8], b);
    }

	inline void mulMatrix_3x4_4x4(int* dst, const int* a, const int* b)
	{
		// Result is 3x4
		// We calculate row by row.
		mulMatrix_1x4_4x4(&dst[0], &a[0], b);
		mulMatrix_1x4_4x4(&dst[4], &a[4], b);
		mulMatrix_1x4_4x4(&dst[8], &a[8], b);
	}
	


	// --- 4x4 result ----------------------------------------------------------
	
    inline void mulMatrix_4x2_2x4(float* dst, const float* a, const float* b)
    {
		// Result is 4x4
		// We calculate 2-rows blocks each at a time.
		mulMatrix_2x2_2x4(&dst[0], &a[0], b);
		mulMatrix_2x2_2x4(&dst[8], &a[4], b);
    }

	inline void mulMatrix_4x2_2x4(int* dst, const int* a, const int* b)
	{
		// Result is 4x4
		// We calculate 2-rows blocks each at a time.
		mulMatrix_2x2_2x4(&dst[0], &a[0], b);
		mulMatrix_2x2_2x4(&dst[8], &a[4], b);
	}


    inline void mulMatrix_4x3_3x4(float* dst, const float* a, const float* b)
    {
		// Result is 4x4
        // We calculate row by row.
        mulMatrix_1x3_3x4(&dst[0], &a[0], b);
        mulMatrix_1x3_3x4(&dst[4], &a[3], b);
        mulMatrix_1x3_3x4(&dst[8], &a[6], b);
        mulMatrix_1x3_3x4(&dst[12], &a[9], b);
    }

	inline void mulMatrix_4x3_3x4(int* dst, const int* a, const int* b)
	{
		// Result is 4x4
		// We calculate row by row.
		mulMatrix_1x3_3x4(&dst[0], &a[0], b);
		mulMatrix_1x3_3x4(&dst[4], &a[3], b);
		mulMatrix_1x3_3x4(&dst[8], &a[6], b);
		mulMatrix_1x3_3x4(&dst[12], &a[9], b);
	}


    inline void mulMatrix_4x4_4x4(float* dst, const float* a, const float* b)
    {
        // Result is 4x4
        // We calculate row by row.
        mulMatrix_1x4_4x4(&dst[0], &a[0], b);
        mulMatrix_1x4_4x4(&dst[4], &a[4], b);
        mulMatrix_1x4_4x4(&dst[8], &a[8], b);
        mulMatrix_1x4_4x4(&dst[12], &a[12], b);
    }
	
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
