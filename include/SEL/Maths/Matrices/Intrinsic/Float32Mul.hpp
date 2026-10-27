// Specialized small matrix kernels retained after generic-backend comparisons.
#pragma once

#include <immintrin.h>
#include <cstddef>
#include <cstring>

namespace sel::utils {

	/// @brief Multiply 1x2 by 2x2 using the small float SIMD kernel.
	inline void mulMatrix_1x2_2x2(float* dst, const float* a, const float* b)
    {
        // Result is 1x2
        __m128 vResult;     // 4 floats

        vResult = _mm_mul_ps(
            _mm_set_ps(a[1], a[1], a[0], a[0]),
            _mm_loadu_ps(b)      // 3, 2, 1, 0
        );
		
		// Add 0 & 2 and 1 & 3
		// Note: Computations are done twice.
		vResult = _mm_add_ps(
			vResult,
			_mm_shuffle_ps(vResult, vResult, _MM_SHUFFLE(1, 0, 3, 2))
		);
		
        float tmp[4];
        _mm_storeu_ps(tmp, vResult);
        std::memcpy(dst, tmp, sizeof(float) * 2);
    }

	/// @brief Multiply 1x4 by 4x2 using the small float SIMD kernel.
	inline void mulMatrix_1x4_4x2(float* dst, const float* a, const float* b)
    {
		// Result is 1x2
        // Matrices are cut in half, 1x2 for a and 2x2 for b.
		__m128 vResult, vResult1, vResult2;

        vResult1 = _mm_mul_ps(
            _mm_set_ps(a[1], a[1], a[0], a[0]),
            _mm_loadu_ps(b)      // 3, 2, 1, 0
        );

        vResult2 = _mm_mul_ps(
            _mm_set_ps(a[3], a[3], a[2], a[2]),
            _mm_loadu_ps(&b[4])      // 3, 2, 1, 0
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
        _mm_storeu_ps(tmp, vResult);
        std::memcpy(dst, tmp, sizeof(float) * 2);
	}

	/// @brief Multiply 2x2 by 2x2 using the small float SIMD kernel.
	inline void mulMatrix_2x2_2x2(float* dst, const float* a, const float* b)
	{
        // Result is 2x2
		__m128 vA, vB, vResult;

		vA = _mm_loadu_ps(a);
		vB = _mm_loadu_ps(b);

		vResult = _mm_mul_ps(
			_mm_shuffle_ps(vA, vA, _MM_SHUFFLE(2, 2, 0, 0)),
			_mm_shuffle_ps(vB, vB, _MM_SHUFFLE(1, 0, 1, 0))
		);

		vResult = _mm_add_ps(vResult, _mm_mul_ps(
			_mm_shuffle_ps(vA, vA, _MM_SHUFFLE(3, 3, 1, 1)),
			_mm_shuffle_ps(vB, vB, _MM_SHUFFLE(3, 2, 3, 2)))
		);
		
		_mm_storeu_ps(dst, vResult);
	}

	/// @brief Multiply 2x4 by 4x2 using the small float SIMD kernel.
	inline void mulMatrix_2x4_4x2(float* dst, const float* a, const float* b)
    {
		// Result is 2x2
        mulMatrix_1x4_4x2(&dst[0], &a[0], b);
        mulMatrix_1x4_4x2(&dst[2], &a[4], b);
    }

	/// @brief Multiply 3x2 by 2x2 using the small float SIMD kernel.
	inline void mulMatrix_3x2_2x2(float* dst, const float* a, const float* b)
    {
        // Result is 3x2
        mulMatrix_2x2_2x2(&dst[0], &a[0], b);
        mulMatrix_1x2_2x2(&dst[4], &a[4], b);
    }

	/// @brief Multiply 3x4 by 4x2 using the small float SIMD kernel.
	inline void mulMatrix_3x4_4x2(float* dst, const float* a, const float* b)
    {
        // Result is 3x2
        mulMatrix_1x4_4x2(&dst[0], &a[0], b);
        mulMatrix_1x4_4x2(&dst[2], &a[4], b);
        mulMatrix_1x4_4x2(&dst[4], &a[8], b);
    }

	/// @brief Multiply 4x2 by 2x2 using the small float SIMD kernel.
	inline void mulMatrix_4x2_2x2(float* dst, const float* a, const float* b)
    {
		// Result is 4x2
		mulMatrix_2x2_2x2(&dst[0], &a[0], b);
		mulMatrix_2x2_2x2(&dst[4], &a[4], b);
    }

	/// @brief Multiply 1x2 by 2x4 using the small float SIMD kernel.
	inline void mulMatrix_1x2_2x4(float* dst, const float* a, const float* b)
    {
		// Result is 1x4
		__m128 vB, vResult;

        // Row 0 of b
        vB = _mm_loadu_ps(&b[0]);
        vResult = _mm_mul_ps(
			_mm_load_ps1(&a[0]),    // The register is filled with the first element of a
            vB
        );
        // Row 1 of b
        vB = _mm_loadu_ps(&b[4]);
        vResult = _mm_add_ps(vResult, _mm_mul_ps(
            _mm_load_ps1(&a[1]),
            vB
        ));

		_mm_storeu_ps(dst, vResult);
    }

	/// @brief Multiply 1x3 by 3x4 using the small float SIMD kernel.
	inline void mulMatrix_1x3_3x4(float* dst, const float* a, const float* b)
    {
        // Result is 1x4
        __m128 vB, vResult;

        // Row 0 of b
        vB = _mm_loadu_ps(&b[0]);
        vResult = _mm_mul_ps(
            _mm_load_ps1(&a[0]),
            vB
        );
        // Row 1 of b
        vB = _mm_loadu_ps(&b[4]);
        vResult = _mm_add_ps(vResult, _mm_mul_ps(
            _mm_load_ps1(&a[1]),
            vB
        ));
        // Row 2 of b
        vB = _mm_loadu_ps(&b[8]);
        vResult = _mm_add_ps(vResult, _mm_mul_ps(
            _mm_load_ps1(&a[2]),
            vB
        ));

        _mm_storeu_ps(dst, vResult);
    }

	/// @brief Multiply 1x4 by 4x4 using the small float SIMD kernel.
	inline void mulMatrix_1x4_4x4(float* dst, const float* a, const float* b)
    {
        // Result is 1x4
		__m128 vB, vResult;
		
		// Row 0 of b
		vB = _mm_loadu_ps(&b[0]);
        vResult = _mm_mul_ps(
            _mm_load_ps1(&a[0]),
            vB
        );
        // Row 1 of b
        vB = _mm_loadu_ps(&b[4]);
        vResult = _mm_add_ps(vResult, _mm_mul_ps(
            _mm_load_ps1(&a[1]),
            vB
        ));
        // Row 2 of b
        vB = _mm_loadu_ps(&b[8]);
        vResult = _mm_add_ps(vResult, _mm_mul_ps(
            _mm_load_ps1(&a[2]),
            vB
        ));
        // Row 3 of b
        vB = _mm_loadu_ps(&b[12]);
        vResult = _mm_add_ps(vResult, _mm_mul_ps(
            _mm_load_ps1(&a[3]),
            vB
        ));
		
        _mm_storeu_ps(dst, vResult);
    }

	/// @brief Multiply 2x2 by 2x4 using the small float SIMD kernel.
	inline void mulMatrix_2x2_2x4(float* dst, const float* a, const float* b)
    {
		// Result is 2x4
        // We calculate row by row.
        mulMatrix_1x2_2x4(&dst[0], &a[0], b);
		mulMatrix_1x2_2x4(&dst[4], &a[2], b);
    }

	/// @brief Multiply 2x3 by 3x4 using the small float SIMD kernel.
	inline void mulMatrix_2x3_3x4(float* dst, const float* a, const float* b)
	{
		// Result is 2x4
        // We calculate row by row.
        mulMatrix_1x3_3x4(&dst[0], &a[0], b);
		mulMatrix_1x3_3x4(&dst[4], &a[3], b);
	}

	/// @brief Multiply 2x4 by 4x4 using the small float SIMD kernel.
	inline void mulMatrix_2x4_4x4(float* dst, const float* a, const float* b)
    {
        // Result is 2x4
        // We calculate row by row.
        mulMatrix_1x4_4x4(&dst[0], &a[0], b);
        mulMatrix_1x4_4x4(&dst[4], &a[4], b);
    }

	/// @brief Multiply 3x2 by 2x4 using the small float SIMD kernel.
	inline void mulMatrix_3x2_2x4(float* dst, const float* a, const float* b)
    {
		// Result is 3x4
		// We calculate row by row.
		mulMatrix_1x2_2x4(&dst[0], &a[0], b);
		mulMatrix_1x2_2x4(&dst[4], &a[2], b);
		mulMatrix_1x2_2x4(&dst[8], &a[4], b);
    }

	/// @brief Multiply 3x3 by 3x4 using the small float SIMD kernel.
	inline void mulMatrix_3x3_3x4(float* dst, const float* a, const float* b)
    {
		// Result is 3x4
		// We calculate row by row.
		mulMatrix_1x3_3x4(&dst[0], &a[0], b);
		mulMatrix_1x3_3x4(&dst[4], &a[3], b);
		mulMatrix_1x3_3x4(&dst[8], &a[6], b);
	}

	/// @brief Multiply 3x4 by 4x4 using the small float SIMD kernel.
	inline void mulMatrix_3x4_4x4(float* dst, const float* a, const float* b)
    {
        // Result is 3x4
        // We calculate row by row.
        mulMatrix_1x4_4x4(&dst[0], &a[0], b);
        mulMatrix_1x4_4x4(&dst[4], &a[4], b);
        mulMatrix_1x4_4x4(&dst[8], &a[8], b);
    }

	/// @brief Multiply 4x2 by 2x4 using the small float SIMD kernel.
	inline void mulMatrix_4x2_2x4(float* dst, const float* a, const float* b)
    {
		// Result is 4x4
		// We calculate 2-rows blocks each at a time.
		mulMatrix_2x2_2x4(&dst[0], &a[0], b);
		mulMatrix_2x2_2x4(&dst[8], &a[4], b);
    }

	/// @brief Multiply 4x3 by 3x4 using the small float SIMD kernel.
	inline void mulMatrix_4x3_3x4(float* dst, const float* a, const float* b)
    {
		// Result is 4x4
        // We calculate row by row.
        mulMatrix_1x3_3x4(&dst[0], &a[0], b);
        mulMatrix_1x3_3x4(&dst[4], &a[3], b);
        mulMatrix_1x3_3x4(&dst[8], &a[6], b);
        mulMatrix_1x3_3x4(&dst[12], &a[9], b);
    }

	/// @brief Multiply 4x4 by 4x4 using the small float SIMD kernel.
	inline void mulMatrix_4x4_4x4(float* dst, const float* a, const float* b)
    {
        // Result is 4x4
        // We calculate row by row.
        mulMatrix_1x4_4x4(&dst[0], &a[0], b);
        mulMatrix_1x4_4x4(&dst[4], &a[4], b);
        mulMatrix_1x4_4x4(&dst[8], &a[8], b);
        mulMatrix_1x4_4x4(&dst[12], &a[12], b);
    }

}
