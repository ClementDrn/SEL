#pragma once

#include <cstdint>

#include "PackedInt4Matrix.hpp"

#include <cstddef>


namespace sel {

	/// @brief Representation of a 16x16 matrix.
	/// 
	/// @tparam T is the type of the matrix's values.
	///  
	template <typename T>
	class Mat16x16
	{
	public:

		/// @brief Default constructor.
		///
		/// This constructor sets matrix's values to default.
		/// 
		Mat16x16() = default;

		/// @brief Constructor.
		/// 
		/// @param scalar is the value to set to the diagonal to.
		/// 
		Mat16x16(T scalar)
			: m_data{
				{ scalar, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				{ 0, scalar, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				{ 0, 0, scalar, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, scalar, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, scalar, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, scalar, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, scalar, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 0, scalar, 0, 0, 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, scalar, 0, 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, scalar, 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, scalar, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, scalar, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, scalar, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, scalar, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, scalar, 0 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, scalar }
			} {}

		/// @brief Constructor.
		///
		/// This constructor sets matrix's values to the given ones.
		/// 
		/// @param m0_0 is the value of row 0, column 0.
		/// @param m0_1 is the value of row 0, column 1.
		/// @param m0_2 is the value of row 0, column 2.
		/// @param m0_3 is the value of row 0, column 3.
		/// @param m0_4 is the value of row 0, column 4.
		/// @param m0_5 is the value of row 0, column 5.
		/// @param m0_6 is the value of row 0, column 6.
		/// @param m0_7 is the value of row 0, column 7.
		/// @param m0_8 is the value of row 0, column 8.
		/// @param m0_9 is the value of row 0, column 9.
		/// @param m0_10 is the value of row 0, column 10.
		/// @param m0_11 is the value of row 0, column 11.
		/// @param m0_12 is the value of row 0, column 12.
		/// @param m0_13 is the value of row 0, column 13.
		/// @param m0_14 is the value of row 0, column 14.
		/// @param m0_15 is the value of row 0, column 15.
		/// @param m1_0 is the value of row 1, column 0.
		/// @param m1_1 is the value of row 1, column 1.
		/// @param m1_2 is the value of row 1, column 2.
		/// @param m1_3 is the value of row 1, column 3.
		/// @param m1_4 is the value of row 1, column 4.
		/// @param m1_5 is the value of row 1, column 5.
		/// @param m1_6 is the value of row 1, column 6.
		/// @param m1_7 is the value of row 1, column 7.
		/// @param m1_8 is the value of row 1, column 8.
		/// @param m1_9 is the value of row 1, column 9.
		/// @param m1_10 is the value of row 1, column 10.
		/// @param m1_11 is the value of row 1, column 11.
		/// @param m1_12 is the value of row 1, column 12.
		/// @param m1_13 is the value of row 1, column 13.
		/// @param m1_14 is the value of row 1, column 14.
		/// @param m1_15 is the value of row 1, column 15.
		/// @param m2_0 is the value of row 2, column 0.
		/// @param m2_1 is the value of row 2, column 1.
		/// @param m2_2 is the value of row 2, column 2.
		/// @param m2_3 is the value of row 2, column 3.
		/// @param m2_4 is the value of row 2, column 4.
		/// @param m2_5 is the value of row 2, column 5.
		/// @param m2_6 is the value of row 2, column 6.
		/// @param m2_7 is the value of row 2, column 7.
		/// @param m2_8 is the value of row 2, column 8.
		/// @param m2_9 is the value of row 2, column 9.
		/// @param m2_10 is the value of row 2, column 10.
		/// @param m2_11 is the value of row 2, column 11.
		/// @param m2_12 is the value of row 2, column 12.
		/// @param m2_13 is the value of row 2, column 13.
		/// @param m2_14 is the value of row 2, column 14.
		/// @param m2_15 is the value of row 2, column 15.
		/// @param m3_0 is the value of row 3, column 0.
		/// @param m3_1 is the value of row 3, column 1.
		/// @param m3_2 is the value of row 3, column 2.
		/// @param m3_3 is the value of row 3, column 3.
		/// @param m3_4 is the value of row 3, column 4.
		/// @param m3_5 is the value of row 3, column 5.
		/// @param m3_6 is the value of row 3, column 6.
		/// @param m3_7 is the value of row 3, column 7.
		/// @param m3_8 is the value of row 3, column 8.
		/// @param m3_9 is the value of row 3, column 9.
		/// @param m3_10 is the value of row 3, column 10.
		/// @param m3_11 is the value of row 3, column 11.
		/// @param m3_12 is the value of row 3, column 12.
		/// @param m3_13 is the value of row 3, column 13.
		/// @param m3_14 is the value of row 3, column 14.
		/// @param m3_15 is the value of row 3, column 15.
		/// @param m4_0 is the value of row 4, column 0.
		/// @param m4_1 is the value of row 4, column 1.
		/// @param m4_2 is the value of row 4, column 2.
		/// @param m4_3 is the value of row 4, column 3.
		/// @param m4_4 is the value of row 4, column 4.
		/// @param m4_5 is the value of row 4, column 5.
		/// @param m4_6 is the value of row 4, column 6.
		/// @param m4_7 is the value of row 4, column 7.
		/// @param m4_8 is the value of row 4, column 8.
		/// @param m4_9 is the value of row 4, column 9.
		/// @param m4_10 is the value of row 4, column 10.
		/// @param m4_11 is the value of row 4, column 11.
		/// @param m4_12 is the value of row 4, column 12.
		/// @param m4_13 is the value of row 4, column 13.
		/// @param m4_14 is the value of row 4, column 14.
		/// @param m4_15 is the value of row 4, column 15.
		/// @param m5_0 is the value of row 5, column 0.
		/// @param m5_1 is the value of row 5, column 1.
		/// @param m5_2 is the value of row 5, column 2.
		/// @param m5_3 is the value of row 5, column 3.
		/// @param m5_4 is the value of row 5, column 4.
		/// @param m5_5 is the value of row 5, column 5.
		/// @param m5_6 is the value of row 5, column 6.
		/// @param m5_7 is the value of row 5, column 7.
		/// @param m5_8 is the value of row 5, column 8.
		/// @param m5_9 is the value of row 5, column 9.
		/// @param m5_10 is the value of row 5, column 10.
		/// @param m5_11 is the value of row 5, column 11.
		/// @param m5_12 is the value of row 5, column 12.
		/// @param m5_13 is the value of row 5, column 13.
		/// @param m5_14 is the value of row 5, column 14.
		/// @param m5_15 is the value of row 5, column 15.
		/// @param m6_0 is the value of row 6, column 0.
		/// @param m6_1 is the value of row 6, column 1.
		/// @param m6_2 is the value of row 6, column 2.
		/// @param m6_3 is the value of row 6, column 3.
		/// @param m6_4 is the value of row 6, column 4.
		/// @param m6_5 is the value of row 6, column 5.
		/// @param m6_6 is the value of row 6, column 6.
		/// @param m6_7 is the value of row 6, column 7.
		/// @param m6_8 is the value of row 6, column 8.
		/// @param m6_9 is the value of row 6, column 9.
		/// @param m6_10 is the value of row 6, column 10.
		/// @param m6_11 is the value of row 6, column 11.
		/// @param m6_12 is the value of row 6, column 12.
		/// @param m6_13 is the value of row 6, column 13.
		/// @param m6_14 is the value of row 6, column 14.
		/// @param m6_15 is the value of row 6, column 15.
		/// @param m7_0 is the value of row 7, column 0.
		/// @param m7_1 is the value of row 7, column 1.
		/// @param m7_2 is the value of row 7, column 2.
		/// @param m7_3 is the value of row 7, column 3.
		/// @param m7_4 is the value of row 7, column 4.
		/// @param m7_5 is the value of row 7, column 5.
		/// @param m7_6 is the value of row 7, column 6.
		/// @param m7_7 is the value of row 7, column 7.
		/// @param m7_8 is the value of row 7, column 8.
		/// @param m7_9 is the value of row 7, column 9.
		/// @param m7_10 is the value of row 7, column 10.
		/// @param m7_11 is the value of row 7, column 11.
		/// @param m7_12 is the value of row 7, column 12.
		/// @param m7_13 is the value of row 7, column 13.
		/// @param m7_14 is the value of row 7, column 14.
		/// @param m7_15 is the value of row 7, column 15.
		/// @param m8_0 is the value of row 8, column 0.
		/// @param m8_1 is the value of row 8, column 1.
		/// @param m8_2 is the value of row 8, column 2.
		/// @param m8_3 is the value of row 8, column 3.
		/// @param m8_4 is the value of row 8, column 4.
		/// @param m8_5 is the value of row 8, column 5.
		/// @param m8_6 is the value of row 8, column 6.
		/// @param m8_7 is the value of row 8, column 7.
		/// @param m8_8 is the value of row 8, column 8.
		/// @param m8_9 is the value of row 8, column 9.
		/// @param m8_10 is the value of row 8, column 10.
		/// @param m8_11 is the value of row 8, column 11.
		/// @param m8_12 is the value of row 8, column 12.
		/// @param m8_13 is the value of row 8, column 13.
		/// @param m8_14 is the value of row 8, column 14.
		/// @param m8_15 is the value of row 8, column 15.
		/// @param m9_0 is the value of row 9, column 0.
		/// @param m9_1 is the value of row 9, column 1.
		/// @param m9_2 is the value of row 9, column 2.
		/// @param m9_3 is the value of row 9, column 3.
		/// @param m9_4 is the value of row 9, column 4.
		/// @param m9_5 is the value of row 9, column 5.
		/// @param m9_6 is the value of row 9, column 6.
		/// @param m9_7 is the value of row 9, column 7.
		/// @param m9_8 is the value of row 9, column 8.
		/// @param m9_9 is the value of row 9, column 9.
		/// @param m9_10 is the value of row 9, column 10.
		/// @param m9_11 is the value of row 9, column 11.
		/// @param m9_12 is the value of row 9, column 12.
		/// @param m9_13 is the value of row 9, column 13.
		/// @param m9_14 is the value of row 9, column 14.
		/// @param m9_15 is the value of row 9, column 15.
		/// @param m10_0 is the value of row 10, column 0.
		/// @param m10_1 is the value of row 10, column 1.
		/// @param m10_2 is the value of row 10, column 2.
		/// @param m10_3 is the value of row 10, column 3.
		/// @param m10_4 is the value of row 10, column 4.
		/// @param m10_5 is the value of row 10, column 5.
		/// @param m10_6 is the value of row 10, column 6.
		/// @param m10_7 is the value of row 10, column 7.
		/// @param m10_8 is the value of row 10, column 8.
		/// @param m10_9 is the value of row 10, column 9.
		/// @param m10_10 is the value of row 10, column 10.
		/// @param m10_11 is the value of row 10, column 11.
		/// @param m10_12 is the value of row 10, column 12.
		/// @param m10_13 is the value of row 10, column 13.
		/// @param m10_14 is the value of row 10, column 14.
		/// @param m10_15 is the value of row 10, column 15.
		/// @param m11_0 is the value of row 11, column 0.
		/// @param m11_1 is the value of row 11, column 1.
		/// @param m11_2 is the value of row 11, column 2.
		/// @param m11_3 is the value of row 11, column 3.
		/// @param m11_4 is the value of row 11, column 4.
		/// @param m11_5 is the value of row 11, column 5.
		/// @param m11_6 is the value of row 11, column 6.
		/// @param m11_7 is the value of row 11, column 7.
		/// @param m11_8 is the value of row 11, column 8.
		/// @param m11_9 is the value of row 11, column 9.
		/// @param m11_10 is the value of row 11, column 10.
		/// @param m11_11 is the value of row 11, column 11.
		/// @param m11_12 is the value of row 11, column 12.
		/// @param m11_13 is the value of row 11, column 13.
		/// @param m11_14 is the value of row 11, column 14.
		/// @param m11_15 is the value of row 11, column 15.
		/// @param m12_0 is the value of row 12, column 0.
		/// @param m12_1 is the value of row 12, column 1.
		/// @param m12_2 is the value of row 12, column 2.
		/// @param m12_3 is the value of row 12, column 3.
		/// @param m12_4 is the value of row 12, column 4.
		/// @param m12_5 is the value of row 12, column 5.
		/// @param m12_6 is the value of row 12, column 6.
		/// @param m12_7 is the value of row 12, column 7.
		/// @param m12_8 is the value of row 12, column 8.
		/// @param m12_9 is the value of row 12, column 9.
		/// @param m12_10 is the value of row 12, column 10.
		/// @param m12_11 is the value of row 12, column 11.
		/// @param m12_12 is the value of row 12, column 12.
		/// @param m12_13 is the value of row 12, column 13.
		/// @param m12_14 is the value of row 12, column 14.
		/// @param m12_15 is the value of row 12, column 15.
		/// @param m13_0 is the value of row 13, column 0.
		/// @param m13_1 is the value of row 13, column 1.
		/// @param m13_2 is the value of row 13, column 2.
		/// @param m13_3 is the value of row 13, column 3.
		/// @param m13_4 is the value of row 13, column 4.
		/// @param m13_5 is the value of row 13, column 5.
		/// @param m13_6 is the value of row 13, column 6.
		/// @param m13_7 is the value of row 13, column 7.
		/// @param m13_8 is the value of row 13, column 8.
		/// @param m13_9 is the value of row 13, column 9.
		/// @param m13_10 is the value of row 13, column 10.
		/// @param m13_11 is the value of row 13, column 11.
		/// @param m13_12 is the value of row 13, column 12.
		/// @param m13_13 is the value of row 13, column 13.
		/// @param m13_14 is the value of row 13, column 14.
		/// @param m13_15 is the value of row 13, column 15.
		/// @param m14_0 is the value of row 14, column 0.
		/// @param m14_1 is the value of row 14, column 1.
		/// @param m14_2 is the value of row 14, column 2.
		/// @param m14_3 is the value of row 14, column 3.
		/// @param m14_4 is the value of row 14, column 4.
		/// @param m14_5 is the value of row 14, column 5.
		/// @param m14_6 is the value of row 14, column 6.
		/// @param m14_7 is the value of row 14, column 7.
		/// @param m14_8 is the value of row 14, column 8.
		/// @param m14_9 is the value of row 14, column 9.
		/// @param m14_10 is the value of row 14, column 10.
		/// @param m14_11 is the value of row 14, column 11.
		/// @param m14_12 is the value of row 14, column 12.
		/// @param m14_13 is the value of row 14, column 13.
		/// @param m14_14 is the value of row 14, column 14.
		/// @param m14_15 is the value of row 14, column 15.
		/// @param m15_0 is the value of row 15, column 0.
		/// @param m15_1 is the value of row 15, column 1.
		/// @param m15_2 is the value of row 15, column 2.
		/// @param m15_3 is the value of row 15, column 3.
		/// @param m15_4 is the value of row 15, column 4.
		/// @param m15_5 is the value of row 15, column 5.
		/// @param m15_6 is the value of row 15, column 6.
		/// @param m15_7 is the value of row 15, column 7.
		/// @param m15_8 is the value of row 15, column 8.
		/// @param m15_9 is the value of row 15, column 9.
		/// @param m15_10 is the value of row 15, column 10.
		/// @param m15_11 is the value of row 15, column 11.
		/// @param m15_12 is the value of row 15, column 12.
		/// @param m15_13 is the value of row 15, column 13.
		/// @param m15_14 is the value of row 15, column 14.
		/// @param m15_15 is the value of row 15, column 15.
		/// 
		Mat16x16(
			T m0_0, T m0_1, T m0_2, T m0_3, T m0_4, T m0_5, T m0_6, T m0_7, T m0_8, T m0_9, T m0_10, T m0_11, T m0_12, T m0_13, T m0_14, T m0_15,
			T m1_0, T m1_1, T m1_2, T m1_3, T m1_4, T m1_5, T m1_6, T m1_7, T m1_8, T m1_9, T m1_10, T m1_11, T m1_12, T m1_13, T m1_14, T m1_15,
			T m2_0, T m2_1, T m2_2, T m2_3, T m2_4, T m2_5, T m2_6, T m2_7, T m2_8, T m2_9, T m2_10, T m2_11, T m2_12, T m2_13, T m2_14, T m2_15,
			T m3_0, T m3_1, T m3_2, T m3_3, T m3_4, T m3_5, T m3_6, T m3_7, T m3_8, T m3_9, T m3_10, T m3_11, T m3_12, T m3_13, T m3_14, T m3_15,
			T m4_0, T m4_1, T m4_2, T m4_3, T m4_4, T m4_5, T m4_6, T m4_7, T m4_8, T m4_9, T m4_10, T m4_11, T m4_12, T m4_13, T m4_14, T m4_15,
			T m5_0, T m5_1, T m5_2, T m5_3, T m5_4, T m5_5, T m5_6, T m5_7, T m5_8, T m5_9, T m5_10, T m5_11, T m5_12, T m5_13, T m5_14, T m5_15,
			T m6_0, T m6_1, T m6_2, T m6_3, T m6_4, T m6_5, T m6_6, T m6_7, T m6_8, T m6_9, T m6_10, T m6_11, T m6_12, T m6_13, T m6_14, T m6_15,
			T m7_0, T m7_1, T m7_2, T m7_3, T m7_4, T m7_5, T m7_6, T m7_7, T m7_8, T m7_9, T m7_10, T m7_11, T m7_12, T m7_13, T m7_14, T m7_15,
			T m8_0, T m8_1, T m8_2, T m8_3, T m8_4, T m8_5, T m8_6, T m8_7, T m8_8, T m8_9, T m8_10, T m8_11, T m8_12, T m8_13, T m8_14, T m8_15,
			T m9_0, T m9_1, T m9_2, T m9_3, T m9_4, T m9_5, T m9_6, T m9_7, T m9_8, T m9_9, T m9_10, T m9_11, T m9_12, T m9_13, T m9_14, T m9_15,
			T m10_0, T m10_1, T m10_2, T m10_3, T m10_4, T m10_5, T m10_6, T m10_7, T m10_8, T m10_9, T m10_10, T m10_11, T m10_12, T m10_13, T m10_14, T m10_15,
			T m11_0, T m11_1, T m11_2, T m11_3, T m11_4, T m11_5, T m11_6, T m11_7, T m11_8, T m11_9, T m11_10, T m11_11, T m11_12, T m11_13, T m11_14, T m11_15,
			T m12_0, T m12_1, T m12_2, T m12_3, T m12_4, T m12_5, T m12_6, T m12_7, T m12_8, T m12_9, T m12_10, T m12_11, T m12_12, T m12_13, T m12_14, T m12_15,
			T m13_0, T m13_1, T m13_2, T m13_3, T m13_4, T m13_5, T m13_6, T m13_7, T m13_8, T m13_9, T m13_10, T m13_11, T m13_12, T m13_13, T m13_14, T m13_15,
			T m14_0, T m14_1, T m14_2, T m14_3, T m14_4, T m14_5, T m14_6, T m14_7, T m14_8, T m14_9, T m14_10, T m14_11, T m14_12, T m14_13, T m14_14, T m14_15,
			T m15_0, T m15_1, T m15_2, T m15_3, T m15_4, T m15_5, T m15_6, T m15_7, T m15_8, T m15_9, T m15_10, T m15_11, T m15_12, T m15_13, T m15_14, T m15_15)
			: m_data{
				{ m0_0, m0_1, m0_2, m0_3, m0_4, m0_5, m0_6, m0_7, m0_8, m0_9, m0_10, m0_11, m0_12, m0_13, m0_14, m0_15 },
				{ m1_0, m1_1, m1_2, m1_3, m1_4, m1_5, m1_6, m1_7, m1_8, m1_9, m1_10, m1_11, m1_12, m1_13, m1_14, m1_15 },
				{ m2_0, m2_1, m2_2, m2_3, m2_4, m2_5, m2_6, m2_7, m2_8, m2_9, m2_10, m2_11, m2_12, m2_13, m2_14, m2_15 },
				{ m3_0, m3_1, m3_2, m3_3, m3_4, m3_5, m3_6, m3_7, m3_8, m3_9, m3_10, m3_11, m3_12, m3_13, m3_14, m3_15 },
				{ m4_0, m4_1, m4_2, m4_3, m4_4, m4_5, m4_6, m4_7, m4_8, m4_9, m4_10, m4_11, m4_12, m4_13, m4_14, m4_15 },
				{ m5_0, m5_1, m5_2, m5_3, m5_4, m5_5, m5_6, m5_7, m5_8, m5_9, m5_10, m5_11, m5_12, m5_13, m5_14, m5_15 },
				{ m6_0, m6_1, m6_2, m6_3, m6_4, m6_5, m6_6, m6_7, m6_8, m6_9, m6_10, m6_11, m6_12, m6_13, m6_14, m6_15 },
				{ m7_0, m7_1, m7_2, m7_3, m7_4, m7_5, m7_6, m7_7, m7_8, m7_9, m7_10, m7_11, m7_12, m7_13, m7_14, m7_15 },
				{ m8_0, m8_1, m8_2, m8_3, m8_4, m8_5, m8_6, m8_7, m8_8, m8_9, m8_10, m8_11, m8_12, m8_13, m8_14, m8_15 },
				{ m9_0, m9_1, m9_2, m9_3, m9_4, m9_5, m9_6, m9_7, m9_8, m9_9, m9_10, m9_11, m9_12, m9_13, m9_14, m9_15 },
				{ m10_0, m10_1, m10_2, m10_3, m10_4, m10_5, m10_6, m10_7, m10_8, m10_9, m10_10, m10_11, m10_12, m10_13, m10_14, m10_15 },
				{ m11_0, m11_1, m11_2, m11_3, m11_4, m11_5, m11_6, m11_7, m11_8, m11_9, m11_10, m11_11, m11_12, m11_13, m11_14, m11_15 },
				{ m12_0, m12_1, m12_2, m12_3, m12_4, m12_5, m12_6, m12_7, m12_8, m12_9, m12_10, m12_11, m12_12, m12_13, m12_14, m12_15 },
				{ m13_0, m13_1, m13_2, m13_3, m13_4, m13_5, m13_6, m13_7, m13_8, m13_9, m13_10, m13_11, m13_12, m13_13, m13_14, m13_15 },
				{ m14_0, m14_1, m14_2, m14_3, m14_4, m14_5, m14_6, m14_7, m14_8, m14_9, m14_10, m14_11, m14_12, m14_13, m14_14, m14_15 },
				{ m15_0, m15_1, m15_2, m15_3, m15_4, m15_5, m15_6, m15_7, m15_8, m15_9, m15_10, m15_11, m15_12, m15_13, m15_14, m15_15 }
			} {}

		/// @brief Copy constructor.
		///
		/// This constructor copies the input matrix.
		/// 
		/// @param other is the matrix to copy.
		/// 
		Mat16x16(const Mat16x16& other)
			: m_data{
				{ other[0][0], other[0][1], other[0][2], other[0][3], other[0][4], other[0][5], other[0][6], other[0][7], other[0][8], other[0][9], other[0][10], other[0][11], other[0][12], other[0][13], other[0][14], other[0][15] },
				{ other[1][0], other[1][1], other[1][2], other[1][3], other[1][4], other[1][5], other[1][6], other[1][7], other[1][8], other[1][9], other[1][10], other[1][11], other[1][12], other[1][13], other[1][14], other[1][15] },
				{ other[2][0], other[2][1], other[2][2], other[2][3], other[2][4], other[2][5], other[2][6], other[2][7], other[2][8], other[2][9], other[2][10], other[2][11], other[2][12], other[2][13], other[2][14], other[2][15] },
				{ other[3][0], other[3][1], other[3][2], other[3][3], other[3][4], other[3][5], other[3][6], other[3][7], other[3][8], other[3][9], other[3][10], other[3][11], other[3][12], other[3][13], other[3][14], other[3][15] },
				{ other[4][0], other[4][1], other[4][2], other[4][3], other[4][4], other[4][5], other[4][6], other[4][7], other[4][8], other[4][9], other[4][10], other[4][11], other[4][12], other[4][13], other[4][14], other[4][15] },
				{ other[5][0], other[5][1], other[5][2], other[5][3], other[5][4], other[5][5], other[5][6], other[5][7], other[5][8], other[5][9], other[5][10], other[5][11], other[5][12], other[5][13], other[5][14], other[5][15] },
				{ other[6][0], other[6][1], other[6][2], other[6][3], other[6][4], other[6][5], other[6][6], other[6][7], other[6][8], other[6][9], other[6][10], other[6][11], other[6][12], other[6][13], other[6][14], other[6][15] },
				{ other[7][0], other[7][1], other[7][2], other[7][3], other[7][4], other[7][5], other[7][6], other[7][7], other[7][8], other[7][9], other[7][10], other[7][11], other[7][12], other[7][13], other[7][14], other[7][15] },
				{ other[8][0], other[8][1], other[8][2], other[8][3], other[8][4], other[8][5], other[8][6], other[8][7], other[8][8], other[8][9], other[8][10], other[8][11], other[8][12], other[8][13], other[8][14], other[8][15] },
				{ other[9][0], other[9][1], other[9][2], other[9][3], other[9][4], other[9][5], other[9][6], other[9][7], other[9][8], other[9][9], other[9][10], other[9][11], other[9][12], other[9][13], other[9][14], other[9][15] },
				{ other[10][0], other[10][1], other[10][2], other[10][3], other[10][4], other[10][5], other[10][6], other[10][7], other[10][8], other[10][9], other[10][10], other[10][11], other[10][12], other[10][13], other[10][14], other[10][15] },
				{ other[11][0], other[11][1], other[11][2], other[11][3], other[11][4], other[11][5], other[11][6], other[11][7], other[11][8], other[11][9], other[11][10], other[11][11], other[11][12], other[11][13], other[11][14], other[11][15] },
				{ other[12][0], other[12][1], other[12][2], other[12][3], other[12][4], other[12][5], other[12][6], other[12][7], other[12][8], other[12][9], other[12][10], other[12][11], other[12][12], other[12][13], other[12][14], other[12][15] },
				{ other[13][0], other[13][1], other[13][2], other[13][3], other[13][4], other[13][5], other[13][6], other[13][7], other[13][8], other[13][9], other[13][10], other[13][11], other[13][12], other[13][13], other[13][14], other[13][15] },
				{ other[14][0], other[14][1], other[14][2], other[14][3], other[14][4], other[14][5], other[14][6], other[14][7], other[14][8], other[14][9], other[14][10], other[14][11], other[14][12], other[14][13], other[14][14], other[14][15] },
				{ other[15][0], other[15][1], other[15][2], other[15][3], other[15][4], other[15][5], other[15][6], other[15][7], other[15][8], other[15][9], other[15][10], other[15][11], other[15][12], other[15][13], other[15][14], other[15][15] }
			} {}


		/// @return the identity matrix.
		/// 
		static Mat16x16<T> identity()
		{
			return Mat16x16<T>(1);
		}
		

		/// @brief Access specified matrix row.
		/// 
		/// Returns the column at specified location index (idx). No bounds checking is performed.
		/// To access a specific value of the matrix, first retrieve a row, then access to one of its values 
		/// by providing another index, you will end up with a two coordinate access.
		/// 
		/// @param idx is the index of the matrix row to retrieve.
		/// 
		/// @return The specified matrix row.
		/// 
		constexpr T* operator[](std::size_t idx) { return m_data[idx]; }
		constexpr const T* operator[](std::size_t idx) const { return m_data[idx]; }


		/// @brief Overload of += binary arithmetic operator.
		/// 
		/// The other matrix is added to the instance.
		/// 
		/// @param rhs is the matrix which must be added to the instance.
		/// 
		/// @return The reference to the updated matrix.
		/// 
		Mat16x16& operator+=(const Mat16x16& rhs)
		{
			m_data[0][0] += rhs[0][0];
			m_data[0][1] += rhs[0][1];
			m_data[0][2] += rhs[0][2];
			m_data[0][3] += rhs[0][3];
			m_data[0][4] += rhs[0][4];
			m_data[0][5] += rhs[0][5];
			m_data[0][6] += rhs[0][6];
			m_data[0][7] += rhs[0][7];
			m_data[0][8] += rhs[0][8];
			m_data[0][9] += rhs[0][9];
			m_data[0][10] += rhs[0][10];
			m_data[0][11] += rhs[0][11];
			m_data[0][12] += rhs[0][12];
			m_data[0][13] += rhs[0][13];
			m_data[0][14] += rhs[0][14];
			m_data[0][15] += rhs[0][15];

			m_data[1][0] += rhs[1][0];
			m_data[1][1] += rhs[1][1];
			m_data[1][2] += rhs[1][2];
			m_data[1][3] += rhs[1][3];
			m_data[1][4] += rhs[1][4];
			m_data[1][5] += rhs[1][5];
			m_data[1][6] += rhs[1][6];
			m_data[1][7] += rhs[1][7];
			m_data[1][8] += rhs[1][8];
			m_data[1][9] += rhs[1][9];
			m_data[1][10] += rhs[1][10];
			m_data[1][11] += rhs[1][11];
			m_data[1][12] += rhs[1][12];
			m_data[1][13] += rhs[1][13];
			m_data[1][14] += rhs[1][14];
			m_data[1][15] += rhs[1][15];

			m_data[2][0] += rhs[2][0];
			m_data[2][1] += rhs[2][1];
			m_data[2][2] += rhs[2][2];
			m_data[2][3] += rhs[2][3];
			m_data[2][4] += rhs[2][4];
			m_data[2][5] += rhs[2][5];
			m_data[2][6] += rhs[2][6];
			m_data[2][7] += rhs[2][7];
			m_data[2][8] += rhs[2][8];
			m_data[2][9] += rhs[2][9];
			m_data[2][10] += rhs[2][10];
			m_data[2][11] += rhs[2][11];
			m_data[2][12] += rhs[2][12];
			m_data[2][13] += rhs[2][13];
			m_data[2][14] += rhs[2][14];
			m_data[2][15] += rhs[2][15];

			m_data[3][0] += rhs[3][0];
			m_data[3][1] += rhs[3][1];
			m_data[3][2] += rhs[3][2];
			m_data[3][3] += rhs[3][3];
			m_data[3][4] += rhs[3][4];
			m_data[3][5] += rhs[3][5];
			m_data[3][6] += rhs[3][6];
			m_data[3][7] += rhs[3][7];
			m_data[3][8] += rhs[3][8];
			m_data[3][9] += rhs[3][9];
			m_data[3][10] += rhs[3][10];
			m_data[3][11] += rhs[3][11];
			m_data[3][12] += rhs[3][12];
			m_data[3][13] += rhs[3][13];
			m_data[3][14] += rhs[3][14];
			m_data[3][15] += rhs[3][15];

			m_data[4][0] += rhs[4][0];
			m_data[4][1] += rhs[4][1];
			m_data[4][2] += rhs[4][2];
			m_data[4][3] += rhs[4][3];
			m_data[4][4] += rhs[4][4];
			m_data[4][5] += rhs[4][5];
			m_data[4][6] += rhs[4][6];
			m_data[4][7] += rhs[4][7];
			m_data[4][8] += rhs[4][8];
			m_data[4][9] += rhs[4][9];
			m_data[4][10] += rhs[4][10];
			m_data[4][11] += rhs[4][11];
			m_data[4][12] += rhs[4][12];
			m_data[4][13] += rhs[4][13];
			m_data[4][14] += rhs[4][14];
			m_data[4][15] += rhs[4][15];

			m_data[5][0] += rhs[5][0];
			m_data[5][1] += rhs[5][1];
			m_data[5][2] += rhs[5][2];
			m_data[5][3] += rhs[5][3];
			m_data[5][4] += rhs[5][4];
			m_data[5][5] += rhs[5][5];
			m_data[5][6] += rhs[5][6];
			m_data[5][7] += rhs[5][7];
			m_data[5][8] += rhs[5][8];
			m_data[5][9] += rhs[5][9];
			m_data[5][10] += rhs[5][10];
			m_data[5][11] += rhs[5][11];
			m_data[5][12] += rhs[5][12];
			m_data[5][13] += rhs[5][13];
			m_data[5][14] += rhs[5][14];
			m_data[5][15] += rhs[5][15];

			m_data[6][0] += rhs[6][0];
			m_data[6][1] += rhs[6][1];
			m_data[6][2] += rhs[6][2];
			m_data[6][3] += rhs[6][3];
			m_data[6][4] += rhs[6][4];
			m_data[6][5] += rhs[6][5];
			m_data[6][6] += rhs[6][6];
			m_data[6][7] += rhs[6][7];
			m_data[6][8] += rhs[6][8];
			m_data[6][9] += rhs[6][9];
			m_data[6][10] += rhs[6][10];
			m_data[6][11] += rhs[6][11];
			m_data[6][12] += rhs[6][12];
			m_data[6][13] += rhs[6][13];
			m_data[6][14] += rhs[6][14];
			m_data[6][15] += rhs[6][15];

			m_data[7][0] += rhs[7][0];
			m_data[7][1] += rhs[7][1];
			m_data[7][2] += rhs[7][2];
			m_data[7][3] += rhs[7][3];
			m_data[7][4] += rhs[7][4];
			m_data[7][5] += rhs[7][5];
			m_data[7][6] += rhs[7][6];
			m_data[7][7] += rhs[7][7];
			m_data[7][8] += rhs[7][8];
			m_data[7][9] += rhs[7][9];
			m_data[7][10] += rhs[7][10];
			m_data[7][11] += rhs[7][11];
			m_data[7][12] += rhs[7][12];
			m_data[7][13] += rhs[7][13];
			m_data[7][14] += rhs[7][14];
			m_data[7][15] += rhs[7][15];

			m_data[8][0] += rhs[8][0];
			m_data[8][1] += rhs[8][1];
			m_data[8][2] += rhs[8][2];
			m_data[8][3] += rhs[8][3];
			m_data[8][4] += rhs[8][4];
			m_data[8][5] += rhs[8][5];
			m_data[8][6] += rhs[8][6];
			m_data[8][7] += rhs[8][7];
			m_data[8][8] += rhs[8][8];
			m_data[8][9] += rhs[8][9];
			m_data[8][10] += rhs[8][10];
			m_data[8][11] += rhs[8][11];
			m_data[8][12] += rhs[8][12];
			m_data[8][13] += rhs[8][13];
			m_data[8][14] += rhs[8][14];
			m_data[8][15] += rhs[8][15];

			m_data[9][0] += rhs[9][0];
			m_data[9][1] += rhs[9][1];
			m_data[9][2] += rhs[9][2];
			m_data[9][3] += rhs[9][3];
			m_data[9][4] += rhs[9][4];
			m_data[9][5] += rhs[9][5];
			m_data[9][6] += rhs[9][6];
			m_data[9][7] += rhs[9][7];
			m_data[9][8] += rhs[9][8];
			m_data[9][9] += rhs[9][9];
			m_data[9][10] += rhs[9][10];
			m_data[9][11] += rhs[9][11];
			m_data[9][12] += rhs[9][12];
			m_data[9][13] += rhs[9][13];
			m_data[9][14] += rhs[9][14];
			m_data[9][15] += rhs[9][15];

			m_data[10][0] += rhs[10][0];
			m_data[10][1] += rhs[10][1];
			m_data[10][2] += rhs[10][2];
			m_data[10][3] += rhs[10][3];
			m_data[10][4] += rhs[10][4];
			m_data[10][5] += rhs[10][5];
			m_data[10][6] += rhs[10][6];
			m_data[10][7] += rhs[10][7];
			m_data[10][8] += rhs[10][8];
			m_data[10][9] += rhs[10][9];
			m_data[10][10] += rhs[10][10];
			m_data[10][11] += rhs[10][11];
			m_data[10][12] += rhs[10][12];
			m_data[10][13] += rhs[10][13];
			m_data[10][14] += rhs[10][14];
			m_data[10][15] += rhs[10][15];

			m_data[11][0] += rhs[11][0];
			m_data[11][1] += rhs[11][1];
			m_data[11][2] += rhs[11][2];
			m_data[11][3] += rhs[11][3];
			m_data[11][4] += rhs[11][4];
			m_data[11][5] += rhs[11][5];
			m_data[11][6] += rhs[11][6];
			m_data[11][7] += rhs[11][7];
			m_data[11][8] += rhs[11][8];
			m_data[11][9] += rhs[11][9];
			m_data[11][10] += rhs[11][10];
			m_data[11][11] += rhs[11][11];
			m_data[11][12] += rhs[11][12];
			m_data[11][13] += rhs[11][13];
			m_data[11][14] += rhs[11][14];
			m_data[11][15] += rhs[11][15];

			m_data[12][0] += rhs[12][0];
			m_data[12][1] += rhs[12][1];
			m_data[12][2] += rhs[12][2];
			m_data[12][3] += rhs[12][3];
			m_data[12][4] += rhs[12][4];
			m_data[12][5] += rhs[12][5];
			m_data[12][6] += rhs[12][6];
			m_data[12][7] += rhs[12][7];
			m_data[12][8] += rhs[12][8];
			m_data[12][9] += rhs[12][9];
			m_data[12][10] += rhs[12][10];
			m_data[12][11] += rhs[12][11];
			m_data[12][12] += rhs[12][12];
			m_data[12][13] += rhs[12][13];
			m_data[12][14] += rhs[12][14];
			m_data[12][15] += rhs[12][15];

			m_data[13][0] += rhs[13][0];
			m_data[13][1] += rhs[13][1];
			m_data[13][2] += rhs[13][2];
			m_data[13][3] += rhs[13][3];
			m_data[13][4] += rhs[13][4];
			m_data[13][5] += rhs[13][5];
			m_data[13][6] += rhs[13][6];
			m_data[13][7] += rhs[13][7];
			m_data[13][8] += rhs[13][8];
			m_data[13][9] += rhs[13][9];
			m_data[13][10] += rhs[13][10];
			m_data[13][11] += rhs[13][11];
			m_data[13][12] += rhs[13][12];
			m_data[13][13] += rhs[13][13];
			m_data[13][14] += rhs[13][14];
			m_data[13][15] += rhs[13][15];

			m_data[14][0] += rhs[14][0];
			m_data[14][1] += rhs[14][1];
			m_data[14][2] += rhs[14][2];
			m_data[14][3] += rhs[14][3];
			m_data[14][4] += rhs[14][4];
			m_data[14][5] += rhs[14][5];
			m_data[14][6] += rhs[14][6];
			m_data[14][7] += rhs[14][7];
			m_data[14][8] += rhs[14][8];
			m_data[14][9] += rhs[14][9];
			m_data[14][10] += rhs[14][10];
			m_data[14][11] += rhs[14][11];
			m_data[14][12] += rhs[14][12];
			m_data[14][13] += rhs[14][13];
			m_data[14][14] += rhs[14][14];
			m_data[14][15] += rhs[14][15];

			m_data[15][0] += rhs[15][0];
			m_data[15][1] += rhs[15][1];
			m_data[15][2] += rhs[15][2];
			m_data[15][3] += rhs[15][3];
			m_data[15][4] += rhs[15][4];
			m_data[15][5] += rhs[15][5];
			m_data[15][6] += rhs[15][6];
			m_data[15][7] += rhs[15][7];
			m_data[15][8] += rhs[15][8];
			m_data[15][9] += rhs[15][9];
			m_data[15][10] += rhs[15][10];
			m_data[15][11] += rhs[15][11];
			m_data[15][12] += rhs[15][12];
			m_data[15][13] += rhs[15][13];
			m_data[15][14] += rhs[15][14];
			m_data[15][15] += rhs[15][15];

			return *this;
		}

		/// @brief Overload of -= binary arithmetic operator.
		/// 
		/// The instance is substracted by the other matrix.
		/// 
		/// @param rhs is the matrix which must be substract the instance.
		/// 
		/// @return The reference to the updated matrix.
		/// 
		Mat16x16& operator-=(const Mat16x16& rhs)
		{
			m_data[0][0] -= rhs[0][0];
			m_data[0][1] -= rhs[0][1];
			m_data[0][2] -= rhs[0][2];
			m_data[0][3] -= rhs[0][3];
			m_data[0][4] -= rhs[0][4];
			m_data[0][5] -= rhs[0][5];
			m_data[0][6] -= rhs[0][6];
			m_data[0][7] -= rhs[0][7];
			m_data[0][8] -= rhs[0][8];
			m_data[0][9] -= rhs[0][9];
			m_data[0][10] -= rhs[0][10];
			m_data[0][11] -= rhs[0][11];
			m_data[0][12] -= rhs[0][12];
			m_data[0][13] -= rhs[0][13];
			m_data[0][14] -= rhs[0][14];
			m_data[0][15] -= rhs[0][15];

			m_data[1][0] -= rhs[1][0];
			m_data[1][1] -= rhs[1][1];
			m_data[1][2] -= rhs[1][2];
			m_data[1][3] -= rhs[1][3];
			m_data[1][4] -= rhs[1][4];
			m_data[1][5] -= rhs[1][5];
			m_data[1][6] -= rhs[1][6];
			m_data[1][7] -= rhs[1][7];
			m_data[1][8] -= rhs[1][8];
			m_data[1][9] -= rhs[1][9];
			m_data[1][10] -= rhs[1][10];
			m_data[1][11] -= rhs[1][11];
			m_data[1][12] -= rhs[1][12];
			m_data[1][13] -= rhs[1][13];
			m_data[1][14] -= rhs[1][14];
			m_data[1][15] -= rhs[1][15];

			m_data[2][0] -= rhs[2][0];
			m_data[2][1] -= rhs[2][1];
			m_data[2][2] -= rhs[2][2];
			m_data[2][3] -= rhs[2][3];
			m_data[2][4] -= rhs[2][4];
			m_data[2][5] -= rhs[2][5];
			m_data[2][6] -= rhs[2][6];
			m_data[2][7] -= rhs[2][7];
			m_data[2][8] -= rhs[2][8];
			m_data[2][9] -= rhs[2][9];
			m_data[2][10] -= rhs[2][10];
			m_data[2][11] -= rhs[2][11];
			m_data[2][12] -= rhs[2][12];
			m_data[2][13] -= rhs[2][13];
			m_data[2][14] -= rhs[2][14];
			m_data[2][15] -= rhs[2][15];

			m_data[3][0] -= rhs[3][0];
			m_data[3][1] -= rhs[3][1];
			m_data[3][2] -= rhs[3][2];
			m_data[3][3] -= rhs[3][3];
			m_data[3][4] -= rhs[3][4];
			m_data[3][5] -= rhs[3][5];
			m_data[3][6] -= rhs[3][6];
			m_data[3][7] -= rhs[3][7];
			m_data[3][8] -= rhs[3][8];
			m_data[3][9] -= rhs[3][9];
			m_data[3][10] -= rhs[3][10];
			m_data[3][11] -= rhs[3][11];
			m_data[3][12] -= rhs[3][12];
			m_data[3][13] -= rhs[3][13];
			m_data[3][14] -= rhs[3][14];
			m_data[3][15] -= rhs[3][15];

			m_data[4][0] -= rhs[4][0];
			m_data[4][1] -= rhs[4][1];
			m_data[4][2] -= rhs[4][2];
			m_data[4][3] -= rhs[4][3];
			m_data[4][4] -= rhs[4][4];
			m_data[4][5] -= rhs[4][5];
			m_data[4][6] -= rhs[4][6];
			m_data[4][7] -= rhs[4][7];
			m_data[4][8] -= rhs[4][8];
			m_data[4][9] -= rhs[4][9];
			m_data[4][10] -= rhs[4][10];
			m_data[4][11] -= rhs[4][11];
			m_data[4][12] -= rhs[4][12];
			m_data[4][13] -= rhs[4][13];
			m_data[4][14] -= rhs[4][14];
			m_data[4][15] -= rhs[4][15];

			m_data[5][0] -= rhs[5][0];
			m_data[5][1] -= rhs[5][1];
			m_data[5][2] -= rhs[5][2];
			m_data[5][3] -= rhs[5][3];
			m_data[5][4] -= rhs[5][4];
			m_data[5][5] -= rhs[5][5];
			m_data[5][6] -= rhs[5][6];
			m_data[5][7] -= rhs[5][7];
			m_data[5][8] -= rhs[5][8];
			m_data[5][9] -= rhs[5][9];
			m_data[5][10] -= rhs[5][10];
			m_data[5][11] -= rhs[5][11];
			m_data[5][12] -= rhs[5][12];
			m_data[5][13] -= rhs[5][13];
			m_data[5][14] -= rhs[5][14];
			m_data[5][15] -= rhs[5][15];

			m_data[6][0] -= rhs[6][0];
			m_data[6][1] -= rhs[6][1];
			m_data[6][2] -= rhs[6][2];
			m_data[6][3] -= rhs[6][3];
			m_data[6][4] -= rhs[6][4];
			m_data[6][5] -= rhs[6][5];
			m_data[6][6] -= rhs[6][6];
			m_data[6][7] -= rhs[6][7];
			m_data[6][8] -= rhs[6][8];
			m_data[6][9] -= rhs[6][9];
			m_data[6][10] -= rhs[6][10];
			m_data[6][11] -= rhs[6][11];
			m_data[6][12] -= rhs[6][12];
			m_data[6][13] -= rhs[6][13];
			m_data[6][14] -= rhs[6][14];
			m_data[6][15] -= rhs[6][15];

			m_data[7][0] -= rhs[7][0];
			m_data[7][1] -= rhs[7][1];
			m_data[7][2] -= rhs[7][2];
			m_data[7][3] -= rhs[7][3];
			m_data[7][4] -= rhs[7][4];
			m_data[7][5] -= rhs[7][5];
			m_data[7][6] -= rhs[7][6];
			m_data[7][7] -= rhs[7][7];
			m_data[7][8] -= rhs[7][8];
			m_data[7][9] -= rhs[7][9];
			m_data[7][10] -= rhs[7][10];
			m_data[7][11] -= rhs[7][11];
			m_data[7][12] -= rhs[7][12];
			m_data[7][13] -= rhs[7][13];
			m_data[7][14] -= rhs[7][14];
			m_data[7][15] -= rhs[7][15];

			m_data[8][0] -= rhs[8][0];
			m_data[8][1] -= rhs[8][1];
			m_data[8][2] -= rhs[8][2];
			m_data[8][3] -= rhs[8][3];
			m_data[8][4] -= rhs[8][4];
			m_data[8][5] -= rhs[8][5];
			m_data[8][6] -= rhs[8][6];
			m_data[8][7] -= rhs[8][7];
			m_data[8][8] -= rhs[8][8];
			m_data[8][9] -= rhs[8][9];
			m_data[8][10] -= rhs[8][10];
			m_data[8][11] -= rhs[8][11];
			m_data[8][12] -= rhs[8][12];
			m_data[8][13] -= rhs[8][13];
			m_data[8][14] -= rhs[8][14];
			m_data[8][15] -= rhs[8][15];

			m_data[9][0] -= rhs[9][0];
			m_data[9][1] -= rhs[9][1];
			m_data[9][2] -= rhs[9][2];
			m_data[9][3] -= rhs[9][3];
			m_data[9][4] -= rhs[9][4];
			m_data[9][5] -= rhs[9][5];
			m_data[9][6] -= rhs[9][6];
			m_data[9][7] -= rhs[9][7];
			m_data[9][8] -= rhs[9][8];
			m_data[9][9] -= rhs[9][9];
			m_data[9][10] -= rhs[9][10];
			m_data[9][11] -= rhs[9][11];
			m_data[9][12] -= rhs[9][12];
			m_data[9][13] -= rhs[9][13];
			m_data[9][14] -= rhs[9][14];
			m_data[9][15] -= rhs[9][15];

			m_data[10][0] -= rhs[10][0];
			m_data[10][1] -= rhs[10][1];
			m_data[10][2] -= rhs[10][2];
			m_data[10][3] -= rhs[10][3];
			m_data[10][4] -= rhs[10][4];
			m_data[10][5] -= rhs[10][5];
			m_data[10][6] -= rhs[10][6];
			m_data[10][7] -= rhs[10][7];
			m_data[10][8] -= rhs[10][8];
			m_data[10][9] -= rhs[10][9];
			m_data[10][10] -= rhs[10][10];
			m_data[10][11] -= rhs[10][11];
			m_data[10][12] -= rhs[10][12];
			m_data[10][13] -= rhs[10][13];
			m_data[10][14] -= rhs[10][14];
			m_data[10][15] -= rhs[10][15];

			m_data[11][0] -= rhs[11][0];
			m_data[11][1] -= rhs[11][1];
			m_data[11][2] -= rhs[11][2];
			m_data[11][3] -= rhs[11][3];
			m_data[11][4] -= rhs[11][4];
			m_data[11][5] -= rhs[11][5];
			m_data[11][6] -= rhs[11][6];
			m_data[11][7] -= rhs[11][7];
			m_data[11][8] -= rhs[11][8];
			m_data[11][9] -= rhs[11][9];
			m_data[11][10] -= rhs[11][10];
			m_data[11][11] -= rhs[11][11];
			m_data[11][12] -= rhs[11][12];
			m_data[11][13] -= rhs[11][13];
			m_data[11][14] -= rhs[11][14];
			m_data[11][15] -= rhs[11][15];

			m_data[12][0] -= rhs[12][0];
			m_data[12][1] -= rhs[12][1];
			m_data[12][2] -= rhs[12][2];
			m_data[12][3] -= rhs[12][3];
			m_data[12][4] -= rhs[12][4];
			m_data[12][5] -= rhs[12][5];
			m_data[12][6] -= rhs[12][6];
			m_data[12][7] -= rhs[12][7];
			m_data[12][8] -= rhs[12][8];
			m_data[12][9] -= rhs[12][9];
			m_data[12][10] -= rhs[12][10];
			m_data[12][11] -= rhs[12][11];
			m_data[12][12] -= rhs[12][12];
			m_data[12][13] -= rhs[12][13];
			m_data[12][14] -= rhs[12][14];
			m_data[12][15] -= rhs[12][15];

			m_data[13][0] -= rhs[13][0];
			m_data[13][1] -= rhs[13][1];
			m_data[13][2] -= rhs[13][2];
			m_data[13][3] -= rhs[13][3];
			m_data[13][4] -= rhs[13][4];
			m_data[13][5] -= rhs[13][5];
			m_data[13][6] -= rhs[13][6];
			m_data[13][7] -= rhs[13][7];
			m_data[13][8] -= rhs[13][8];
			m_data[13][9] -= rhs[13][9];
			m_data[13][10] -= rhs[13][10];
			m_data[13][11] -= rhs[13][11];
			m_data[13][12] -= rhs[13][12];
			m_data[13][13] -= rhs[13][13];
			m_data[13][14] -= rhs[13][14];
			m_data[13][15] -= rhs[13][15];

			m_data[14][0] -= rhs[14][0];
			m_data[14][1] -= rhs[14][1];
			m_data[14][2] -= rhs[14][2];
			m_data[14][3] -= rhs[14][3];
			m_data[14][4] -= rhs[14][4];
			m_data[14][5] -= rhs[14][5];
			m_data[14][6] -= rhs[14][6];
			m_data[14][7] -= rhs[14][7];
			m_data[14][8] -= rhs[14][8];
			m_data[14][9] -= rhs[14][9];
			m_data[14][10] -= rhs[14][10];
			m_data[14][11] -= rhs[14][11];
			m_data[14][12] -= rhs[14][12];
			m_data[14][13] -= rhs[14][13];
			m_data[14][14] -= rhs[14][14];
			m_data[14][15] -= rhs[14][15];

			m_data[15][0] -= rhs[15][0];
			m_data[15][1] -= rhs[15][1];
			m_data[15][2] -= rhs[15][2];
			m_data[15][3] -= rhs[15][3];
			m_data[15][4] -= rhs[15][4];
			m_data[15][5] -= rhs[15][5];
			m_data[15][6] -= rhs[15][6];
			m_data[15][7] -= rhs[15][7];
			m_data[15][8] -= rhs[15][8];
			m_data[15][9] -= rhs[15][9];
			m_data[15][10] -= rhs[15][10];
			m_data[15][11] -= rhs[15][11];
			m_data[15][12] -= rhs[15][12];
			m_data[15][13] -= rhs[15][13];
			m_data[15][14] -= rhs[15][14];
			m_data[15][15] -= rhs[15][15];

			return *this;
		}

		template <typename U>
		friend Mat16x16<U> operator*(const Mat16x16<U>& lhs, const Mat16x16<U>& rhs);
		

	private:

		T m_data[16][16] = {};
	};

	template <>
	class Mat16x16<int4> : public utils::PackedInt4Matrix<16, 16, Mat16x16<int4>>
	{
		using Base = utils::PackedInt4Matrix<16, 16, Mat16x16<int4>>;
	public:
		using Base::Base;
		constexpr Mat16x16() = default;
	};

	/// @brief Representation of a packed 16x16 signed four-bit matrix.
	using Mat16x16i4 = Mat16x16<int4>;

	/// @brief Representation of a 16x16 integer matrix.
	///
	using Mat16x16i = Mat16x16<int>;

	/// @brief Representation of a 16x16 signed 8-bit integer matrix.
	///
	using Mat16x16i8 = Mat16x16<std::int8_t>;

	/// @brief Representation of a 16x16 float matrix.
	///
	using Mat16x16f = Mat16x16<float>;

	/// @brief Representation of a 16x16 unsigned integer matrix.
	///
	using Mat16x16u = Mat16x16<unsigned int>;


	/// @brief Overload of + binary arithmetic operator.
	/// 
	/// @tparam T is the type of the matrices' values.
	/// @param lhs is the first matrix.
	/// @param rhs is the second matrix.
	/// 
	/// @return The matrix resulted by the addition of the two provided matrices.
	/// 
	template <class T>
	inline Mat16x16<T> operator+(Mat16x16<T> lhs, const Mat16x16<T>& rhs)
	{
		lhs += rhs;
		return lhs;
	}

	/// @brief Overload of - binary arithmetic operator.
	/// 
	/// @tparam T is the type of the matrices' values.
	/// @param lhs is the first matrix.
	/// @param rhs is the second matrix.
	/// 
	/// @return The matrix resulted by the substraction of the two provided matrices.
	/// 
	template <class T>
	inline Mat16x16<T> operator-(Mat16x16<T> lhs, const Mat16x16<T>& rhs)
	{
		lhs -= rhs;
		return lhs;
	}

}
