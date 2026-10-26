#pragma once

#include <cstdint>

#include <cstddef>


namespace sel {

	/// @brief Representation of a 32x32 matrix.
	/// 
	/// @tparam T is the type of the matrix's values.
	///  
	template <typename T>
	class Mat32x32
	{
	public:

		/// @brief Default constructor.
		///
		/// This constructor sets matrix's values to default.
		/// 
		Mat32x32() = default;

		/// @brief Constructor.
		/// 
		/// @param scalar is the value to set to the diagonal to.
		/// 
		Mat32x32(T scalar)
			: m_data{
				{ scalar, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				{ 0, scalar, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				{ 0, 0, scalar, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, scalar, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, scalar, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, scalar, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, scalar, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 0, scalar, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, scalar, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, scalar, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, scalar, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, scalar, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, scalar, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, scalar, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, scalar, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, scalar, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, scalar, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, scalar, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, scalar, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, scalar, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, scalar, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, scalar, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, scalar, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, scalar, 0, 0, 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, scalar, 0, 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, scalar, 0, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, scalar, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, scalar, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, scalar, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, scalar, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, scalar, 0 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, scalar }
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
		/// @param m0_16 is the value of row 0, column 16.
		/// @param m0_17 is the value of row 0, column 17.
		/// @param m0_18 is the value of row 0, column 18.
		/// @param m0_19 is the value of row 0, column 19.
		/// @param m0_20 is the value of row 0, column 20.
		/// @param m0_21 is the value of row 0, column 21.
		/// @param m0_22 is the value of row 0, column 22.
		/// @param m0_23 is the value of row 0, column 23.
		/// @param m0_24 is the value of row 0, column 24.
		/// @param m0_25 is the value of row 0, column 25.
		/// @param m0_26 is the value of row 0, column 26.
		/// @param m0_27 is the value of row 0, column 27.
		/// @param m0_28 is the value of row 0, column 28.
		/// @param m0_29 is the value of row 0, column 29.
		/// @param m0_30 is the value of row 0, column 30.
		/// @param m0_31 is the value of row 0, column 31.
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
		/// @param m1_16 is the value of row 1, column 16.
		/// @param m1_17 is the value of row 1, column 17.
		/// @param m1_18 is the value of row 1, column 18.
		/// @param m1_19 is the value of row 1, column 19.
		/// @param m1_20 is the value of row 1, column 20.
		/// @param m1_21 is the value of row 1, column 21.
		/// @param m1_22 is the value of row 1, column 22.
		/// @param m1_23 is the value of row 1, column 23.
		/// @param m1_24 is the value of row 1, column 24.
		/// @param m1_25 is the value of row 1, column 25.
		/// @param m1_26 is the value of row 1, column 26.
		/// @param m1_27 is the value of row 1, column 27.
		/// @param m1_28 is the value of row 1, column 28.
		/// @param m1_29 is the value of row 1, column 29.
		/// @param m1_30 is the value of row 1, column 30.
		/// @param m1_31 is the value of row 1, column 31.
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
		/// @param m2_16 is the value of row 2, column 16.
		/// @param m2_17 is the value of row 2, column 17.
		/// @param m2_18 is the value of row 2, column 18.
		/// @param m2_19 is the value of row 2, column 19.
		/// @param m2_20 is the value of row 2, column 20.
		/// @param m2_21 is the value of row 2, column 21.
		/// @param m2_22 is the value of row 2, column 22.
		/// @param m2_23 is the value of row 2, column 23.
		/// @param m2_24 is the value of row 2, column 24.
		/// @param m2_25 is the value of row 2, column 25.
		/// @param m2_26 is the value of row 2, column 26.
		/// @param m2_27 is the value of row 2, column 27.
		/// @param m2_28 is the value of row 2, column 28.
		/// @param m2_29 is the value of row 2, column 29.
		/// @param m2_30 is the value of row 2, column 30.
		/// @param m2_31 is the value of row 2, column 31.
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
		/// @param m3_16 is the value of row 3, column 16.
		/// @param m3_17 is the value of row 3, column 17.
		/// @param m3_18 is the value of row 3, column 18.
		/// @param m3_19 is the value of row 3, column 19.
		/// @param m3_20 is the value of row 3, column 20.
		/// @param m3_21 is the value of row 3, column 21.
		/// @param m3_22 is the value of row 3, column 22.
		/// @param m3_23 is the value of row 3, column 23.
		/// @param m3_24 is the value of row 3, column 24.
		/// @param m3_25 is the value of row 3, column 25.
		/// @param m3_26 is the value of row 3, column 26.
		/// @param m3_27 is the value of row 3, column 27.
		/// @param m3_28 is the value of row 3, column 28.
		/// @param m3_29 is the value of row 3, column 29.
		/// @param m3_30 is the value of row 3, column 30.
		/// @param m3_31 is the value of row 3, column 31.
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
		/// @param m4_16 is the value of row 4, column 16.
		/// @param m4_17 is the value of row 4, column 17.
		/// @param m4_18 is the value of row 4, column 18.
		/// @param m4_19 is the value of row 4, column 19.
		/// @param m4_20 is the value of row 4, column 20.
		/// @param m4_21 is the value of row 4, column 21.
		/// @param m4_22 is the value of row 4, column 22.
		/// @param m4_23 is the value of row 4, column 23.
		/// @param m4_24 is the value of row 4, column 24.
		/// @param m4_25 is the value of row 4, column 25.
		/// @param m4_26 is the value of row 4, column 26.
		/// @param m4_27 is the value of row 4, column 27.
		/// @param m4_28 is the value of row 4, column 28.
		/// @param m4_29 is the value of row 4, column 29.
		/// @param m4_30 is the value of row 4, column 30.
		/// @param m4_31 is the value of row 4, column 31.
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
		/// @param m5_16 is the value of row 5, column 16.
		/// @param m5_17 is the value of row 5, column 17.
		/// @param m5_18 is the value of row 5, column 18.
		/// @param m5_19 is the value of row 5, column 19.
		/// @param m5_20 is the value of row 5, column 20.
		/// @param m5_21 is the value of row 5, column 21.
		/// @param m5_22 is the value of row 5, column 22.
		/// @param m5_23 is the value of row 5, column 23.
		/// @param m5_24 is the value of row 5, column 24.
		/// @param m5_25 is the value of row 5, column 25.
		/// @param m5_26 is the value of row 5, column 26.
		/// @param m5_27 is the value of row 5, column 27.
		/// @param m5_28 is the value of row 5, column 28.
		/// @param m5_29 is the value of row 5, column 29.
		/// @param m5_30 is the value of row 5, column 30.
		/// @param m5_31 is the value of row 5, column 31.
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
		/// @param m6_16 is the value of row 6, column 16.
		/// @param m6_17 is the value of row 6, column 17.
		/// @param m6_18 is the value of row 6, column 18.
		/// @param m6_19 is the value of row 6, column 19.
		/// @param m6_20 is the value of row 6, column 20.
		/// @param m6_21 is the value of row 6, column 21.
		/// @param m6_22 is the value of row 6, column 22.
		/// @param m6_23 is the value of row 6, column 23.
		/// @param m6_24 is the value of row 6, column 24.
		/// @param m6_25 is the value of row 6, column 25.
		/// @param m6_26 is the value of row 6, column 26.
		/// @param m6_27 is the value of row 6, column 27.
		/// @param m6_28 is the value of row 6, column 28.
		/// @param m6_29 is the value of row 6, column 29.
		/// @param m6_30 is the value of row 6, column 30.
		/// @param m6_31 is the value of row 6, column 31.
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
		/// @param m7_16 is the value of row 7, column 16.
		/// @param m7_17 is the value of row 7, column 17.
		/// @param m7_18 is the value of row 7, column 18.
		/// @param m7_19 is the value of row 7, column 19.
		/// @param m7_20 is the value of row 7, column 20.
		/// @param m7_21 is the value of row 7, column 21.
		/// @param m7_22 is the value of row 7, column 22.
		/// @param m7_23 is the value of row 7, column 23.
		/// @param m7_24 is the value of row 7, column 24.
		/// @param m7_25 is the value of row 7, column 25.
		/// @param m7_26 is the value of row 7, column 26.
		/// @param m7_27 is the value of row 7, column 27.
		/// @param m7_28 is the value of row 7, column 28.
		/// @param m7_29 is the value of row 7, column 29.
		/// @param m7_30 is the value of row 7, column 30.
		/// @param m7_31 is the value of row 7, column 31.
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
		/// @param m8_16 is the value of row 8, column 16.
		/// @param m8_17 is the value of row 8, column 17.
		/// @param m8_18 is the value of row 8, column 18.
		/// @param m8_19 is the value of row 8, column 19.
		/// @param m8_20 is the value of row 8, column 20.
		/// @param m8_21 is the value of row 8, column 21.
		/// @param m8_22 is the value of row 8, column 22.
		/// @param m8_23 is the value of row 8, column 23.
		/// @param m8_24 is the value of row 8, column 24.
		/// @param m8_25 is the value of row 8, column 25.
		/// @param m8_26 is the value of row 8, column 26.
		/// @param m8_27 is the value of row 8, column 27.
		/// @param m8_28 is the value of row 8, column 28.
		/// @param m8_29 is the value of row 8, column 29.
		/// @param m8_30 is the value of row 8, column 30.
		/// @param m8_31 is the value of row 8, column 31.
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
		/// @param m9_16 is the value of row 9, column 16.
		/// @param m9_17 is the value of row 9, column 17.
		/// @param m9_18 is the value of row 9, column 18.
		/// @param m9_19 is the value of row 9, column 19.
		/// @param m9_20 is the value of row 9, column 20.
		/// @param m9_21 is the value of row 9, column 21.
		/// @param m9_22 is the value of row 9, column 22.
		/// @param m9_23 is the value of row 9, column 23.
		/// @param m9_24 is the value of row 9, column 24.
		/// @param m9_25 is the value of row 9, column 25.
		/// @param m9_26 is the value of row 9, column 26.
		/// @param m9_27 is the value of row 9, column 27.
		/// @param m9_28 is the value of row 9, column 28.
		/// @param m9_29 is the value of row 9, column 29.
		/// @param m9_30 is the value of row 9, column 30.
		/// @param m9_31 is the value of row 9, column 31.
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
		/// @param m10_16 is the value of row 10, column 16.
		/// @param m10_17 is the value of row 10, column 17.
		/// @param m10_18 is the value of row 10, column 18.
		/// @param m10_19 is the value of row 10, column 19.
		/// @param m10_20 is the value of row 10, column 20.
		/// @param m10_21 is the value of row 10, column 21.
		/// @param m10_22 is the value of row 10, column 22.
		/// @param m10_23 is the value of row 10, column 23.
		/// @param m10_24 is the value of row 10, column 24.
		/// @param m10_25 is the value of row 10, column 25.
		/// @param m10_26 is the value of row 10, column 26.
		/// @param m10_27 is the value of row 10, column 27.
		/// @param m10_28 is the value of row 10, column 28.
		/// @param m10_29 is the value of row 10, column 29.
		/// @param m10_30 is the value of row 10, column 30.
		/// @param m10_31 is the value of row 10, column 31.
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
		/// @param m11_16 is the value of row 11, column 16.
		/// @param m11_17 is the value of row 11, column 17.
		/// @param m11_18 is the value of row 11, column 18.
		/// @param m11_19 is the value of row 11, column 19.
		/// @param m11_20 is the value of row 11, column 20.
		/// @param m11_21 is the value of row 11, column 21.
		/// @param m11_22 is the value of row 11, column 22.
		/// @param m11_23 is the value of row 11, column 23.
		/// @param m11_24 is the value of row 11, column 24.
		/// @param m11_25 is the value of row 11, column 25.
		/// @param m11_26 is the value of row 11, column 26.
		/// @param m11_27 is the value of row 11, column 27.
		/// @param m11_28 is the value of row 11, column 28.
		/// @param m11_29 is the value of row 11, column 29.
		/// @param m11_30 is the value of row 11, column 30.
		/// @param m11_31 is the value of row 11, column 31.
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
		/// @param m12_16 is the value of row 12, column 16.
		/// @param m12_17 is the value of row 12, column 17.
		/// @param m12_18 is the value of row 12, column 18.
		/// @param m12_19 is the value of row 12, column 19.
		/// @param m12_20 is the value of row 12, column 20.
		/// @param m12_21 is the value of row 12, column 21.
		/// @param m12_22 is the value of row 12, column 22.
		/// @param m12_23 is the value of row 12, column 23.
		/// @param m12_24 is the value of row 12, column 24.
		/// @param m12_25 is the value of row 12, column 25.
		/// @param m12_26 is the value of row 12, column 26.
		/// @param m12_27 is the value of row 12, column 27.
		/// @param m12_28 is the value of row 12, column 28.
		/// @param m12_29 is the value of row 12, column 29.
		/// @param m12_30 is the value of row 12, column 30.
		/// @param m12_31 is the value of row 12, column 31.
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
		/// @param m13_16 is the value of row 13, column 16.
		/// @param m13_17 is the value of row 13, column 17.
		/// @param m13_18 is the value of row 13, column 18.
		/// @param m13_19 is the value of row 13, column 19.
		/// @param m13_20 is the value of row 13, column 20.
		/// @param m13_21 is the value of row 13, column 21.
		/// @param m13_22 is the value of row 13, column 22.
		/// @param m13_23 is the value of row 13, column 23.
		/// @param m13_24 is the value of row 13, column 24.
		/// @param m13_25 is the value of row 13, column 25.
		/// @param m13_26 is the value of row 13, column 26.
		/// @param m13_27 is the value of row 13, column 27.
		/// @param m13_28 is the value of row 13, column 28.
		/// @param m13_29 is the value of row 13, column 29.
		/// @param m13_30 is the value of row 13, column 30.
		/// @param m13_31 is the value of row 13, column 31.
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
		/// @param m14_16 is the value of row 14, column 16.
		/// @param m14_17 is the value of row 14, column 17.
		/// @param m14_18 is the value of row 14, column 18.
		/// @param m14_19 is the value of row 14, column 19.
		/// @param m14_20 is the value of row 14, column 20.
		/// @param m14_21 is the value of row 14, column 21.
		/// @param m14_22 is the value of row 14, column 22.
		/// @param m14_23 is the value of row 14, column 23.
		/// @param m14_24 is the value of row 14, column 24.
		/// @param m14_25 is the value of row 14, column 25.
		/// @param m14_26 is the value of row 14, column 26.
		/// @param m14_27 is the value of row 14, column 27.
		/// @param m14_28 is the value of row 14, column 28.
		/// @param m14_29 is the value of row 14, column 29.
		/// @param m14_30 is the value of row 14, column 30.
		/// @param m14_31 is the value of row 14, column 31.
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
		/// @param m15_16 is the value of row 15, column 16.
		/// @param m15_17 is the value of row 15, column 17.
		/// @param m15_18 is the value of row 15, column 18.
		/// @param m15_19 is the value of row 15, column 19.
		/// @param m15_20 is the value of row 15, column 20.
		/// @param m15_21 is the value of row 15, column 21.
		/// @param m15_22 is the value of row 15, column 22.
		/// @param m15_23 is the value of row 15, column 23.
		/// @param m15_24 is the value of row 15, column 24.
		/// @param m15_25 is the value of row 15, column 25.
		/// @param m15_26 is the value of row 15, column 26.
		/// @param m15_27 is the value of row 15, column 27.
		/// @param m15_28 is the value of row 15, column 28.
		/// @param m15_29 is the value of row 15, column 29.
		/// @param m15_30 is the value of row 15, column 30.
		/// @param m15_31 is the value of row 15, column 31.
		/// @param m16_0 is the value of row 16, column 0.
		/// @param m16_1 is the value of row 16, column 1.
		/// @param m16_2 is the value of row 16, column 2.
		/// @param m16_3 is the value of row 16, column 3.
		/// @param m16_4 is the value of row 16, column 4.
		/// @param m16_5 is the value of row 16, column 5.
		/// @param m16_6 is the value of row 16, column 6.
		/// @param m16_7 is the value of row 16, column 7.
		/// @param m16_8 is the value of row 16, column 8.
		/// @param m16_9 is the value of row 16, column 9.
		/// @param m16_10 is the value of row 16, column 10.
		/// @param m16_11 is the value of row 16, column 11.
		/// @param m16_12 is the value of row 16, column 12.
		/// @param m16_13 is the value of row 16, column 13.
		/// @param m16_14 is the value of row 16, column 14.
		/// @param m16_15 is the value of row 16, column 15.
		/// @param m16_16 is the value of row 16, column 16.
		/// @param m16_17 is the value of row 16, column 17.
		/// @param m16_18 is the value of row 16, column 18.
		/// @param m16_19 is the value of row 16, column 19.
		/// @param m16_20 is the value of row 16, column 20.
		/// @param m16_21 is the value of row 16, column 21.
		/// @param m16_22 is the value of row 16, column 22.
		/// @param m16_23 is the value of row 16, column 23.
		/// @param m16_24 is the value of row 16, column 24.
		/// @param m16_25 is the value of row 16, column 25.
		/// @param m16_26 is the value of row 16, column 26.
		/// @param m16_27 is the value of row 16, column 27.
		/// @param m16_28 is the value of row 16, column 28.
		/// @param m16_29 is the value of row 16, column 29.
		/// @param m16_30 is the value of row 16, column 30.
		/// @param m16_31 is the value of row 16, column 31.
		/// @param m17_0 is the value of row 17, column 0.
		/// @param m17_1 is the value of row 17, column 1.
		/// @param m17_2 is the value of row 17, column 2.
		/// @param m17_3 is the value of row 17, column 3.
		/// @param m17_4 is the value of row 17, column 4.
		/// @param m17_5 is the value of row 17, column 5.
		/// @param m17_6 is the value of row 17, column 6.
		/// @param m17_7 is the value of row 17, column 7.
		/// @param m17_8 is the value of row 17, column 8.
		/// @param m17_9 is the value of row 17, column 9.
		/// @param m17_10 is the value of row 17, column 10.
		/// @param m17_11 is the value of row 17, column 11.
		/// @param m17_12 is the value of row 17, column 12.
		/// @param m17_13 is the value of row 17, column 13.
		/// @param m17_14 is the value of row 17, column 14.
		/// @param m17_15 is the value of row 17, column 15.
		/// @param m17_16 is the value of row 17, column 16.
		/// @param m17_17 is the value of row 17, column 17.
		/// @param m17_18 is the value of row 17, column 18.
		/// @param m17_19 is the value of row 17, column 19.
		/// @param m17_20 is the value of row 17, column 20.
		/// @param m17_21 is the value of row 17, column 21.
		/// @param m17_22 is the value of row 17, column 22.
		/// @param m17_23 is the value of row 17, column 23.
		/// @param m17_24 is the value of row 17, column 24.
		/// @param m17_25 is the value of row 17, column 25.
		/// @param m17_26 is the value of row 17, column 26.
		/// @param m17_27 is the value of row 17, column 27.
		/// @param m17_28 is the value of row 17, column 28.
		/// @param m17_29 is the value of row 17, column 29.
		/// @param m17_30 is the value of row 17, column 30.
		/// @param m17_31 is the value of row 17, column 31.
		/// @param m18_0 is the value of row 18, column 0.
		/// @param m18_1 is the value of row 18, column 1.
		/// @param m18_2 is the value of row 18, column 2.
		/// @param m18_3 is the value of row 18, column 3.
		/// @param m18_4 is the value of row 18, column 4.
		/// @param m18_5 is the value of row 18, column 5.
		/// @param m18_6 is the value of row 18, column 6.
		/// @param m18_7 is the value of row 18, column 7.
		/// @param m18_8 is the value of row 18, column 8.
		/// @param m18_9 is the value of row 18, column 9.
		/// @param m18_10 is the value of row 18, column 10.
		/// @param m18_11 is the value of row 18, column 11.
		/// @param m18_12 is the value of row 18, column 12.
		/// @param m18_13 is the value of row 18, column 13.
		/// @param m18_14 is the value of row 18, column 14.
		/// @param m18_15 is the value of row 18, column 15.
		/// @param m18_16 is the value of row 18, column 16.
		/// @param m18_17 is the value of row 18, column 17.
		/// @param m18_18 is the value of row 18, column 18.
		/// @param m18_19 is the value of row 18, column 19.
		/// @param m18_20 is the value of row 18, column 20.
		/// @param m18_21 is the value of row 18, column 21.
		/// @param m18_22 is the value of row 18, column 22.
		/// @param m18_23 is the value of row 18, column 23.
		/// @param m18_24 is the value of row 18, column 24.
		/// @param m18_25 is the value of row 18, column 25.
		/// @param m18_26 is the value of row 18, column 26.
		/// @param m18_27 is the value of row 18, column 27.
		/// @param m18_28 is the value of row 18, column 28.
		/// @param m18_29 is the value of row 18, column 29.
		/// @param m18_30 is the value of row 18, column 30.
		/// @param m18_31 is the value of row 18, column 31.
		/// @param m19_0 is the value of row 19, column 0.
		/// @param m19_1 is the value of row 19, column 1.
		/// @param m19_2 is the value of row 19, column 2.
		/// @param m19_3 is the value of row 19, column 3.
		/// @param m19_4 is the value of row 19, column 4.
		/// @param m19_5 is the value of row 19, column 5.
		/// @param m19_6 is the value of row 19, column 6.
		/// @param m19_7 is the value of row 19, column 7.
		/// @param m19_8 is the value of row 19, column 8.
		/// @param m19_9 is the value of row 19, column 9.
		/// @param m19_10 is the value of row 19, column 10.
		/// @param m19_11 is the value of row 19, column 11.
		/// @param m19_12 is the value of row 19, column 12.
		/// @param m19_13 is the value of row 19, column 13.
		/// @param m19_14 is the value of row 19, column 14.
		/// @param m19_15 is the value of row 19, column 15.
		/// @param m19_16 is the value of row 19, column 16.
		/// @param m19_17 is the value of row 19, column 17.
		/// @param m19_18 is the value of row 19, column 18.
		/// @param m19_19 is the value of row 19, column 19.
		/// @param m19_20 is the value of row 19, column 20.
		/// @param m19_21 is the value of row 19, column 21.
		/// @param m19_22 is the value of row 19, column 22.
		/// @param m19_23 is the value of row 19, column 23.
		/// @param m19_24 is the value of row 19, column 24.
		/// @param m19_25 is the value of row 19, column 25.
		/// @param m19_26 is the value of row 19, column 26.
		/// @param m19_27 is the value of row 19, column 27.
		/// @param m19_28 is the value of row 19, column 28.
		/// @param m19_29 is the value of row 19, column 29.
		/// @param m19_30 is the value of row 19, column 30.
		/// @param m19_31 is the value of row 19, column 31.
		/// @param m20_0 is the value of row 20, column 0.
		/// @param m20_1 is the value of row 20, column 1.
		/// @param m20_2 is the value of row 20, column 2.
		/// @param m20_3 is the value of row 20, column 3.
		/// @param m20_4 is the value of row 20, column 4.
		/// @param m20_5 is the value of row 20, column 5.
		/// @param m20_6 is the value of row 20, column 6.
		/// @param m20_7 is the value of row 20, column 7.
		/// @param m20_8 is the value of row 20, column 8.
		/// @param m20_9 is the value of row 20, column 9.
		/// @param m20_10 is the value of row 20, column 10.
		/// @param m20_11 is the value of row 20, column 11.
		/// @param m20_12 is the value of row 20, column 12.
		/// @param m20_13 is the value of row 20, column 13.
		/// @param m20_14 is the value of row 20, column 14.
		/// @param m20_15 is the value of row 20, column 15.
		/// @param m20_16 is the value of row 20, column 16.
		/// @param m20_17 is the value of row 20, column 17.
		/// @param m20_18 is the value of row 20, column 18.
		/// @param m20_19 is the value of row 20, column 19.
		/// @param m20_20 is the value of row 20, column 20.
		/// @param m20_21 is the value of row 20, column 21.
		/// @param m20_22 is the value of row 20, column 22.
		/// @param m20_23 is the value of row 20, column 23.
		/// @param m20_24 is the value of row 20, column 24.
		/// @param m20_25 is the value of row 20, column 25.
		/// @param m20_26 is the value of row 20, column 26.
		/// @param m20_27 is the value of row 20, column 27.
		/// @param m20_28 is the value of row 20, column 28.
		/// @param m20_29 is the value of row 20, column 29.
		/// @param m20_30 is the value of row 20, column 30.
		/// @param m20_31 is the value of row 20, column 31.
		/// @param m21_0 is the value of row 21, column 0.
		/// @param m21_1 is the value of row 21, column 1.
		/// @param m21_2 is the value of row 21, column 2.
		/// @param m21_3 is the value of row 21, column 3.
		/// @param m21_4 is the value of row 21, column 4.
		/// @param m21_5 is the value of row 21, column 5.
		/// @param m21_6 is the value of row 21, column 6.
		/// @param m21_7 is the value of row 21, column 7.
		/// @param m21_8 is the value of row 21, column 8.
		/// @param m21_9 is the value of row 21, column 9.
		/// @param m21_10 is the value of row 21, column 10.
		/// @param m21_11 is the value of row 21, column 11.
		/// @param m21_12 is the value of row 21, column 12.
		/// @param m21_13 is the value of row 21, column 13.
		/// @param m21_14 is the value of row 21, column 14.
		/// @param m21_15 is the value of row 21, column 15.
		/// @param m21_16 is the value of row 21, column 16.
		/// @param m21_17 is the value of row 21, column 17.
		/// @param m21_18 is the value of row 21, column 18.
		/// @param m21_19 is the value of row 21, column 19.
		/// @param m21_20 is the value of row 21, column 20.
		/// @param m21_21 is the value of row 21, column 21.
		/// @param m21_22 is the value of row 21, column 22.
		/// @param m21_23 is the value of row 21, column 23.
		/// @param m21_24 is the value of row 21, column 24.
		/// @param m21_25 is the value of row 21, column 25.
		/// @param m21_26 is the value of row 21, column 26.
		/// @param m21_27 is the value of row 21, column 27.
		/// @param m21_28 is the value of row 21, column 28.
		/// @param m21_29 is the value of row 21, column 29.
		/// @param m21_30 is the value of row 21, column 30.
		/// @param m21_31 is the value of row 21, column 31.
		/// @param m22_0 is the value of row 22, column 0.
		/// @param m22_1 is the value of row 22, column 1.
		/// @param m22_2 is the value of row 22, column 2.
		/// @param m22_3 is the value of row 22, column 3.
		/// @param m22_4 is the value of row 22, column 4.
		/// @param m22_5 is the value of row 22, column 5.
		/// @param m22_6 is the value of row 22, column 6.
		/// @param m22_7 is the value of row 22, column 7.
		/// @param m22_8 is the value of row 22, column 8.
		/// @param m22_9 is the value of row 22, column 9.
		/// @param m22_10 is the value of row 22, column 10.
		/// @param m22_11 is the value of row 22, column 11.
		/// @param m22_12 is the value of row 22, column 12.
		/// @param m22_13 is the value of row 22, column 13.
		/// @param m22_14 is the value of row 22, column 14.
		/// @param m22_15 is the value of row 22, column 15.
		/// @param m22_16 is the value of row 22, column 16.
		/// @param m22_17 is the value of row 22, column 17.
		/// @param m22_18 is the value of row 22, column 18.
		/// @param m22_19 is the value of row 22, column 19.
		/// @param m22_20 is the value of row 22, column 20.
		/// @param m22_21 is the value of row 22, column 21.
		/// @param m22_22 is the value of row 22, column 22.
		/// @param m22_23 is the value of row 22, column 23.
		/// @param m22_24 is the value of row 22, column 24.
		/// @param m22_25 is the value of row 22, column 25.
		/// @param m22_26 is the value of row 22, column 26.
		/// @param m22_27 is the value of row 22, column 27.
		/// @param m22_28 is the value of row 22, column 28.
		/// @param m22_29 is the value of row 22, column 29.
		/// @param m22_30 is the value of row 22, column 30.
		/// @param m22_31 is the value of row 22, column 31.
		/// @param m23_0 is the value of row 23, column 0.
		/// @param m23_1 is the value of row 23, column 1.
		/// @param m23_2 is the value of row 23, column 2.
		/// @param m23_3 is the value of row 23, column 3.
		/// @param m23_4 is the value of row 23, column 4.
		/// @param m23_5 is the value of row 23, column 5.
		/// @param m23_6 is the value of row 23, column 6.
		/// @param m23_7 is the value of row 23, column 7.
		/// @param m23_8 is the value of row 23, column 8.
		/// @param m23_9 is the value of row 23, column 9.
		/// @param m23_10 is the value of row 23, column 10.
		/// @param m23_11 is the value of row 23, column 11.
		/// @param m23_12 is the value of row 23, column 12.
		/// @param m23_13 is the value of row 23, column 13.
		/// @param m23_14 is the value of row 23, column 14.
		/// @param m23_15 is the value of row 23, column 15.
		/// @param m23_16 is the value of row 23, column 16.
		/// @param m23_17 is the value of row 23, column 17.
		/// @param m23_18 is the value of row 23, column 18.
		/// @param m23_19 is the value of row 23, column 19.
		/// @param m23_20 is the value of row 23, column 20.
		/// @param m23_21 is the value of row 23, column 21.
		/// @param m23_22 is the value of row 23, column 22.
		/// @param m23_23 is the value of row 23, column 23.
		/// @param m23_24 is the value of row 23, column 24.
		/// @param m23_25 is the value of row 23, column 25.
		/// @param m23_26 is the value of row 23, column 26.
		/// @param m23_27 is the value of row 23, column 27.
		/// @param m23_28 is the value of row 23, column 28.
		/// @param m23_29 is the value of row 23, column 29.
		/// @param m23_30 is the value of row 23, column 30.
		/// @param m23_31 is the value of row 23, column 31.
		/// @param m24_0 is the value of row 24, column 0.
		/// @param m24_1 is the value of row 24, column 1.
		/// @param m24_2 is the value of row 24, column 2.
		/// @param m24_3 is the value of row 24, column 3.
		/// @param m24_4 is the value of row 24, column 4.
		/// @param m24_5 is the value of row 24, column 5.
		/// @param m24_6 is the value of row 24, column 6.
		/// @param m24_7 is the value of row 24, column 7.
		/// @param m24_8 is the value of row 24, column 8.
		/// @param m24_9 is the value of row 24, column 9.
		/// @param m24_10 is the value of row 24, column 10.
		/// @param m24_11 is the value of row 24, column 11.
		/// @param m24_12 is the value of row 24, column 12.
		/// @param m24_13 is the value of row 24, column 13.
		/// @param m24_14 is the value of row 24, column 14.
		/// @param m24_15 is the value of row 24, column 15.
		/// @param m24_16 is the value of row 24, column 16.
		/// @param m24_17 is the value of row 24, column 17.
		/// @param m24_18 is the value of row 24, column 18.
		/// @param m24_19 is the value of row 24, column 19.
		/// @param m24_20 is the value of row 24, column 20.
		/// @param m24_21 is the value of row 24, column 21.
		/// @param m24_22 is the value of row 24, column 22.
		/// @param m24_23 is the value of row 24, column 23.
		/// @param m24_24 is the value of row 24, column 24.
		/// @param m24_25 is the value of row 24, column 25.
		/// @param m24_26 is the value of row 24, column 26.
		/// @param m24_27 is the value of row 24, column 27.
		/// @param m24_28 is the value of row 24, column 28.
		/// @param m24_29 is the value of row 24, column 29.
		/// @param m24_30 is the value of row 24, column 30.
		/// @param m24_31 is the value of row 24, column 31.
		/// @param m25_0 is the value of row 25, column 0.
		/// @param m25_1 is the value of row 25, column 1.
		/// @param m25_2 is the value of row 25, column 2.
		/// @param m25_3 is the value of row 25, column 3.
		/// @param m25_4 is the value of row 25, column 4.
		/// @param m25_5 is the value of row 25, column 5.
		/// @param m25_6 is the value of row 25, column 6.
		/// @param m25_7 is the value of row 25, column 7.
		/// @param m25_8 is the value of row 25, column 8.
		/// @param m25_9 is the value of row 25, column 9.
		/// @param m25_10 is the value of row 25, column 10.
		/// @param m25_11 is the value of row 25, column 11.
		/// @param m25_12 is the value of row 25, column 12.
		/// @param m25_13 is the value of row 25, column 13.
		/// @param m25_14 is the value of row 25, column 14.
		/// @param m25_15 is the value of row 25, column 15.
		/// @param m25_16 is the value of row 25, column 16.
		/// @param m25_17 is the value of row 25, column 17.
		/// @param m25_18 is the value of row 25, column 18.
		/// @param m25_19 is the value of row 25, column 19.
		/// @param m25_20 is the value of row 25, column 20.
		/// @param m25_21 is the value of row 25, column 21.
		/// @param m25_22 is the value of row 25, column 22.
		/// @param m25_23 is the value of row 25, column 23.
		/// @param m25_24 is the value of row 25, column 24.
		/// @param m25_25 is the value of row 25, column 25.
		/// @param m25_26 is the value of row 25, column 26.
		/// @param m25_27 is the value of row 25, column 27.
		/// @param m25_28 is the value of row 25, column 28.
		/// @param m25_29 is the value of row 25, column 29.
		/// @param m25_30 is the value of row 25, column 30.
		/// @param m25_31 is the value of row 25, column 31.
		/// @param m26_0 is the value of row 26, column 0.
		/// @param m26_1 is the value of row 26, column 1.
		/// @param m26_2 is the value of row 26, column 2.
		/// @param m26_3 is the value of row 26, column 3.
		/// @param m26_4 is the value of row 26, column 4.
		/// @param m26_5 is the value of row 26, column 5.
		/// @param m26_6 is the value of row 26, column 6.
		/// @param m26_7 is the value of row 26, column 7.
		/// @param m26_8 is the value of row 26, column 8.
		/// @param m26_9 is the value of row 26, column 9.
		/// @param m26_10 is the value of row 26, column 10.
		/// @param m26_11 is the value of row 26, column 11.
		/// @param m26_12 is the value of row 26, column 12.
		/// @param m26_13 is the value of row 26, column 13.
		/// @param m26_14 is the value of row 26, column 14.
		/// @param m26_15 is the value of row 26, column 15.
		/// @param m26_16 is the value of row 26, column 16.
		/// @param m26_17 is the value of row 26, column 17.
		/// @param m26_18 is the value of row 26, column 18.
		/// @param m26_19 is the value of row 26, column 19.
		/// @param m26_20 is the value of row 26, column 20.
		/// @param m26_21 is the value of row 26, column 21.
		/// @param m26_22 is the value of row 26, column 22.
		/// @param m26_23 is the value of row 26, column 23.
		/// @param m26_24 is the value of row 26, column 24.
		/// @param m26_25 is the value of row 26, column 25.
		/// @param m26_26 is the value of row 26, column 26.
		/// @param m26_27 is the value of row 26, column 27.
		/// @param m26_28 is the value of row 26, column 28.
		/// @param m26_29 is the value of row 26, column 29.
		/// @param m26_30 is the value of row 26, column 30.
		/// @param m26_31 is the value of row 26, column 31.
		/// @param m27_0 is the value of row 27, column 0.
		/// @param m27_1 is the value of row 27, column 1.
		/// @param m27_2 is the value of row 27, column 2.
		/// @param m27_3 is the value of row 27, column 3.
		/// @param m27_4 is the value of row 27, column 4.
		/// @param m27_5 is the value of row 27, column 5.
		/// @param m27_6 is the value of row 27, column 6.
		/// @param m27_7 is the value of row 27, column 7.
		/// @param m27_8 is the value of row 27, column 8.
		/// @param m27_9 is the value of row 27, column 9.
		/// @param m27_10 is the value of row 27, column 10.
		/// @param m27_11 is the value of row 27, column 11.
		/// @param m27_12 is the value of row 27, column 12.
		/// @param m27_13 is the value of row 27, column 13.
		/// @param m27_14 is the value of row 27, column 14.
		/// @param m27_15 is the value of row 27, column 15.
		/// @param m27_16 is the value of row 27, column 16.
		/// @param m27_17 is the value of row 27, column 17.
		/// @param m27_18 is the value of row 27, column 18.
		/// @param m27_19 is the value of row 27, column 19.
		/// @param m27_20 is the value of row 27, column 20.
		/// @param m27_21 is the value of row 27, column 21.
		/// @param m27_22 is the value of row 27, column 22.
		/// @param m27_23 is the value of row 27, column 23.
		/// @param m27_24 is the value of row 27, column 24.
		/// @param m27_25 is the value of row 27, column 25.
		/// @param m27_26 is the value of row 27, column 26.
		/// @param m27_27 is the value of row 27, column 27.
		/// @param m27_28 is the value of row 27, column 28.
		/// @param m27_29 is the value of row 27, column 29.
		/// @param m27_30 is the value of row 27, column 30.
		/// @param m27_31 is the value of row 27, column 31.
		/// @param m28_0 is the value of row 28, column 0.
		/// @param m28_1 is the value of row 28, column 1.
		/// @param m28_2 is the value of row 28, column 2.
		/// @param m28_3 is the value of row 28, column 3.
		/// @param m28_4 is the value of row 28, column 4.
		/// @param m28_5 is the value of row 28, column 5.
		/// @param m28_6 is the value of row 28, column 6.
		/// @param m28_7 is the value of row 28, column 7.
		/// @param m28_8 is the value of row 28, column 8.
		/// @param m28_9 is the value of row 28, column 9.
		/// @param m28_10 is the value of row 28, column 10.
		/// @param m28_11 is the value of row 28, column 11.
		/// @param m28_12 is the value of row 28, column 12.
		/// @param m28_13 is the value of row 28, column 13.
		/// @param m28_14 is the value of row 28, column 14.
		/// @param m28_15 is the value of row 28, column 15.
		/// @param m28_16 is the value of row 28, column 16.
		/// @param m28_17 is the value of row 28, column 17.
		/// @param m28_18 is the value of row 28, column 18.
		/// @param m28_19 is the value of row 28, column 19.
		/// @param m28_20 is the value of row 28, column 20.
		/// @param m28_21 is the value of row 28, column 21.
		/// @param m28_22 is the value of row 28, column 22.
		/// @param m28_23 is the value of row 28, column 23.
		/// @param m28_24 is the value of row 28, column 24.
		/// @param m28_25 is the value of row 28, column 25.
		/// @param m28_26 is the value of row 28, column 26.
		/// @param m28_27 is the value of row 28, column 27.
		/// @param m28_28 is the value of row 28, column 28.
		/// @param m28_29 is the value of row 28, column 29.
		/// @param m28_30 is the value of row 28, column 30.
		/// @param m28_31 is the value of row 28, column 31.
		/// @param m29_0 is the value of row 29, column 0.
		/// @param m29_1 is the value of row 29, column 1.
		/// @param m29_2 is the value of row 29, column 2.
		/// @param m29_3 is the value of row 29, column 3.
		/// @param m29_4 is the value of row 29, column 4.
		/// @param m29_5 is the value of row 29, column 5.
		/// @param m29_6 is the value of row 29, column 6.
		/// @param m29_7 is the value of row 29, column 7.
		/// @param m29_8 is the value of row 29, column 8.
		/// @param m29_9 is the value of row 29, column 9.
		/// @param m29_10 is the value of row 29, column 10.
		/// @param m29_11 is the value of row 29, column 11.
		/// @param m29_12 is the value of row 29, column 12.
		/// @param m29_13 is the value of row 29, column 13.
		/// @param m29_14 is the value of row 29, column 14.
		/// @param m29_15 is the value of row 29, column 15.
		/// @param m29_16 is the value of row 29, column 16.
		/// @param m29_17 is the value of row 29, column 17.
		/// @param m29_18 is the value of row 29, column 18.
		/// @param m29_19 is the value of row 29, column 19.
		/// @param m29_20 is the value of row 29, column 20.
		/// @param m29_21 is the value of row 29, column 21.
		/// @param m29_22 is the value of row 29, column 22.
		/// @param m29_23 is the value of row 29, column 23.
		/// @param m29_24 is the value of row 29, column 24.
		/// @param m29_25 is the value of row 29, column 25.
		/// @param m29_26 is the value of row 29, column 26.
		/// @param m29_27 is the value of row 29, column 27.
		/// @param m29_28 is the value of row 29, column 28.
		/// @param m29_29 is the value of row 29, column 29.
		/// @param m29_30 is the value of row 29, column 30.
		/// @param m29_31 is the value of row 29, column 31.
		/// @param m30_0 is the value of row 30, column 0.
		/// @param m30_1 is the value of row 30, column 1.
		/// @param m30_2 is the value of row 30, column 2.
		/// @param m30_3 is the value of row 30, column 3.
		/// @param m30_4 is the value of row 30, column 4.
		/// @param m30_5 is the value of row 30, column 5.
		/// @param m30_6 is the value of row 30, column 6.
		/// @param m30_7 is the value of row 30, column 7.
		/// @param m30_8 is the value of row 30, column 8.
		/// @param m30_9 is the value of row 30, column 9.
		/// @param m30_10 is the value of row 30, column 10.
		/// @param m30_11 is the value of row 30, column 11.
		/// @param m30_12 is the value of row 30, column 12.
		/// @param m30_13 is the value of row 30, column 13.
		/// @param m30_14 is the value of row 30, column 14.
		/// @param m30_15 is the value of row 30, column 15.
		/// @param m30_16 is the value of row 30, column 16.
		/// @param m30_17 is the value of row 30, column 17.
		/// @param m30_18 is the value of row 30, column 18.
		/// @param m30_19 is the value of row 30, column 19.
		/// @param m30_20 is the value of row 30, column 20.
		/// @param m30_21 is the value of row 30, column 21.
		/// @param m30_22 is the value of row 30, column 22.
		/// @param m30_23 is the value of row 30, column 23.
		/// @param m30_24 is the value of row 30, column 24.
		/// @param m30_25 is the value of row 30, column 25.
		/// @param m30_26 is the value of row 30, column 26.
		/// @param m30_27 is the value of row 30, column 27.
		/// @param m30_28 is the value of row 30, column 28.
		/// @param m30_29 is the value of row 30, column 29.
		/// @param m30_30 is the value of row 30, column 30.
		/// @param m30_31 is the value of row 30, column 31.
		/// @param m31_0 is the value of row 31, column 0.
		/// @param m31_1 is the value of row 31, column 1.
		/// @param m31_2 is the value of row 31, column 2.
		/// @param m31_3 is the value of row 31, column 3.
		/// @param m31_4 is the value of row 31, column 4.
		/// @param m31_5 is the value of row 31, column 5.
		/// @param m31_6 is the value of row 31, column 6.
		/// @param m31_7 is the value of row 31, column 7.
		/// @param m31_8 is the value of row 31, column 8.
		/// @param m31_9 is the value of row 31, column 9.
		/// @param m31_10 is the value of row 31, column 10.
		/// @param m31_11 is the value of row 31, column 11.
		/// @param m31_12 is the value of row 31, column 12.
		/// @param m31_13 is the value of row 31, column 13.
		/// @param m31_14 is the value of row 31, column 14.
		/// @param m31_15 is the value of row 31, column 15.
		/// @param m31_16 is the value of row 31, column 16.
		/// @param m31_17 is the value of row 31, column 17.
		/// @param m31_18 is the value of row 31, column 18.
		/// @param m31_19 is the value of row 31, column 19.
		/// @param m31_20 is the value of row 31, column 20.
		/// @param m31_21 is the value of row 31, column 21.
		/// @param m31_22 is the value of row 31, column 22.
		/// @param m31_23 is the value of row 31, column 23.
		/// @param m31_24 is the value of row 31, column 24.
		/// @param m31_25 is the value of row 31, column 25.
		/// @param m31_26 is the value of row 31, column 26.
		/// @param m31_27 is the value of row 31, column 27.
		/// @param m31_28 is the value of row 31, column 28.
		/// @param m31_29 is the value of row 31, column 29.
		/// @param m31_30 is the value of row 31, column 30.
		/// @param m31_31 is the value of row 31, column 31.
		/// 
		Mat32x32(
			T m0_0, T m0_1, T m0_2, T m0_3, T m0_4, T m0_5, T m0_6, T m0_7, T m0_8, T m0_9, T m0_10, T m0_11, T m0_12, T m0_13, T m0_14, T m0_15, T m0_16, T m0_17, T m0_18, T m0_19, T m0_20, T m0_21, T m0_22, T m0_23, T m0_24, T m0_25, T m0_26, T m0_27, T m0_28, T m0_29, T m0_30, T m0_31,
			T m1_0, T m1_1, T m1_2, T m1_3, T m1_4, T m1_5, T m1_6, T m1_7, T m1_8, T m1_9, T m1_10, T m1_11, T m1_12, T m1_13, T m1_14, T m1_15, T m1_16, T m1_17, T m1_18, T m1_19, T m1_20, T m1_21, T m1_22, T m1_23, T m1_24, T m1_25, T m1_26, T m1_27, T m1_28, T m1_29, T m1_30, T m1_31,
			T m2_0, T m2_1, T m2_2, T m2_3, T m2_4, T m2_5, T m2_6, T m2_7, T m2_8, T m2_9, T m2_10, T m2_11, T m2_12, T m2_13, T m2_14, T m2_15, T m2_16, T m2_17, T m2_18, T m2_19, T m2_20, T m2_21, T m2_22, T m2_23, T m2_24, T m2_25, T m2_26, T m2_27, T m2_28, T m2_29, T m2_30, T m2_31,
			T m3_0, T m3_1, T m3_2, T m3_3, T m3_4, T m3_5, T m3_6, T m3_7, T m3_8, T m3_9, T m3_10, T m3_11, T m3_12, T m3_13, T m3_14, T m3_15, T m3_16, T m3_17, T m3_18, T m3_19, T m3_20, T m3_21, T m3_22, T m3_23, T m3_24, T m3_25, T m3_26, T m3_27, T m3_28, T m3_29, T m3_30, T m3_31,
			T m4_0, T m4_1, T m4_2, T m4_3, T m4_4, T m4_5, T m4_6, T m4_7, T m4_8, T m4_9, T m4_10, T m4_11, T m4_12, T m4_13, T m4_14, T m4_15, T m4_16, T m4_17, T m4_18, T m4_19, T m4_20, T m4_21, T m4_22, T m4_23, T m4_24, T m4_25, T m4_26, T m4_27, T m4_28, T m4_29, T m4_30, T m4_31,
			T m5_0, T m5_1, T m5_2, T m5_3, T m5_4, T m5_5, T m5_6, T m5_7, T m5_8, T m5_9, T m5_10, T m5_11, T m5_12, T m5_13, T m5_14, T m5_15, T m5_16, T m5_17, T m5_18, T m5_19, T m5_20, T m5_21, T m5_22, T m5_23, T m5_24, T m5_25, T m5_26, T m5_27, T m5_28, T m5_29, T m5_30, T m5_31,
			T m6_0, T m6_1, T m6_2, T m6_3, T m6_4, T m6_5, T m6_6, T m6_7, T m6_8, T m6_9, T m6_10, T m6_11, T m6_12, T m6_13, T m6_14, T m6_15, T m6_16, T m6_17, T m6_18, T m6_19, T m6_20, T m6_21, T m6_22, T m6_23, T m6_24, T m6_25, T m6_26, T m6_27, T m6_28, T m6_29, T m6_30, T m6_31,
			T m7_0, T m7_1, T m7_2, T m7_3, T m7_4, T m7_5, T m7_6, T m7_7, T m7_8, T m7_9, T m7_10, T m7_11, T m7_12, T m7_13, T m7_14, T m7_15, T m7_16, T m7_17, T m7_18, T m7_19, T m7_20, T m7_21, T m7_22, T m7_23, T m7_24, T m7_25, T m7_26, T m7_27, T m7_28, T m7_29, T m7_30, T m7_31,
			T m8_0, T m8_1, T m8_2, T m8_3, T m8_4, T m8_5, T m8_6, T m8_7, T m8_8, T m8_9, T m8_10, T m8_11, T m8_12, T m8_13, T m8_14, T m8_15, T m8_16, T m8_17, T m8_18, T m8_19, T m8_20, T m8_21, T m8_22, T m8_23, T m8_24, T m8_25, T m8_26, T m8_27, T m8_28, T m8_29, T m8_30, T m8_31,
			T m9_0, T m9_1, T m9_2, T m9_3, T m9_4, T m9_5, T m9_6, T m9_7, T m9_8, T m9_9, T m9_10, T m9_11, T m9_12, T m9_13, T m9_14, T m9_15, T m9_16, T m9_17, T m9_18, T m9_19, T m9_20, T m9_21, T m9_22, T m9_23, T m9_24, T m9_25, T m9_26, T m9_27, T m9_28, T m9_29, T m9_30, T m9_31,
			T m10_0, T m10_1, T m10_2, T m10_3, T m10_4, T m10_5, T m10_6, T m10_7, T m10_8, T m10_9, T m10_10, T m10_11, T m10_12, T m10_13, T m10_14, T m10_15, T m10_16, T m10_17, T m10_18, T m10_19, T m10_20, T m10_21, T m10_22, T m10_23, T m10_24, T m10_25, T m10_26, T m10_27, T m10_28, T m10_29, T m10_30, T m10_31,
			T m11_0, T m11_1, T m11_2, T m11_3, T m11_4, T m11_5, T m11_6, T m11_7, T m11_8, T m11_9, T m11_10, T m11_11, T m11_12, T m11_13, T m11_14, T m11_15, T m11_16, T m11_17, T m11_18, T m11_19, T m11_20, T m11_21, T m11_22, T m11_23, T m11_24, T m11_25, T m11_26, T m11_27, T m11_28, T m11_29, T m11_30, T m11_31,
			T m12_0, T m12_1, T m12_2, T m12_3, T m12_4, T m12_5, T m12_6, T m12_7, T m12_8, T m12_9, T m12_10, T m12_11, T m12_12, T m12_13, T m12_14, T m12_15, T m12_16, T m12_17, T m12_18, T m12_19, T m12_20, T m12_21, T m12_22, T m12_23, T m12_24, T m12_25, T m12_26, T m12_27, T m12_28, T m12_29, T m12_30, T m12_31,
			T m13_0, T m13_1, T m13_2, T m13_3, T m13_4, T m13_5, T m13_6, T m13_7, T m13_8, T m13_9, T m13_10, T m13_11, T m13_12, T m13_13, T m13_14, T m13_15, T m13_16, T m13_17, T m13_18, T m13_19, T m13_20, T m13_21, T m13_22, T m13_23, T m13_24, T m13_25, T m13_26, T m13_27, T m13_28, T m13_29, T m13_30, T m13_31,
			T m14_0, T m14_1, T m14_2, T m14_3, T m14_4, T m14_5, T m14_6, T m14_7, T m14_8, T m14_9, T m14_10, T m14_11, T m14_12, T m14_13, T m14_14, T m14_15, T m14_16, T m14_17, T m14_18, T m14_19, T m14_20, T m14_21, T m14_22, T m14_23, T m14_24, T m14_25, T m14_26, T m14_27, T m14_28, T m14_29, T m14_30, T m14_31,
			T m15_0, T m15_1, T m15_2, T m15_3, T m15_4, T m15_5, T m15_6, T m15_7, T m15_8, T m15_9, T m15_10, T m15_11, T m15_12, T m15_13, T m15_14, T m15_15, T m15_16, T m15_17, T m15_18, T m15_19, T m15_20, T m15_21, T m15_22, T m15_23, T m15_24, T m15_25, T m15_26, T m15_27, T m15_28, T m15_29, T m15_30, T m15_31,
			T m16_0, T m16_1, T m16_2, T m16_3, T m16_4, T m16_5, T m16_6, T m16_7, T m16_8, T m16_9, T m16_10, T m16_11, T m16_12, T m16_13, T m16_14, T m16_15, T m16_16, T m16_17, T m16_18, T m16_19, T m16_20, T m16_21, T m16_22, T m16_23, T m16_24, T m16_25, T m16_26, T m16_27, T m16_28, T m16_29, T m16_30, T m16_31,
			T m17_0, T m17_1, T m17_2, T m17_3, T m17_4, T m17_5, T m17_6, T m17_7, T m17_8, T m17_9, T m17_10, T m17_11, T m17_12, T m17_13, T m17_14, T m17_15, T m17_16, T m17_17, T m17_18, T m17_19, T m17_20, T m17_21, T m17_22, T m17_23, T m17_24, T m17_25, T m17_26, T m17_27, T m17_28, T m17_29, T m17_30, T m17_31,
			T m18_0, T m18_1, T m18_2, T m18_3, T m18_4, T m18_5, T m18_6, T m18_7, T m18_8, T m18_9, T m18_10, T m18_11, T m18_12, T m18_13, T m18_14, T m18_15, T m18_16, T m18_17, T m18_18, T m18_19, T m18_20, T m18_21, T m18_22, T m18_23, T m18_24, T m18_25, T m18_26, T m18_27, T m18_28, T m18_29, T m18_30, T m18_31,
			T m19_0, T m19_1, T m19_2, T m19_3, T m19_4, T m19_5, T m19_6, T m19_7, T m19_8, T m19_9, T m19_10, T m19_11, T m19_12, T m19_13, T m19_14, T m19_15, T m19_16, T m19_17, T m19_18, T m19_19, T m19_20, T m19_21, T m19_22, T m19_23, T m19_24, T m19_25, T m19_26, T m19_27, T m19_28, T m19_29, T m19_30, T m19_31,
			T m20_0, T m20_1, T m20_2, T m20_3, T m20_4, T m20_5, T m20_6, T m20_7, T m20_8, T m20_9, T m20_10, T m20_11, T m20_12, T m20_13, T m20_14, T m20_15, T m20_16, T m20_17, T m20_18, T m20_19, T m20_20, T m20_21, T m20_22, T m20_23, T m20_24, T m20_25, T m20_26, T m20_27, T m20_28, T m20_29, T m20_30, T m20_31,
			T m21_0, T m21_1, T m21_2, T m21_3, T m21_4, T m21_5, T m21_6, T m21_7, T m21_8, T m21_9, T m21_10, T m21_11, T m21_12, T m21_13, T m21_14, T m21_15, T m21_16, T m21_17, T m21_18, T m21_19, T m21_20, T m21_21, T m21_22, T m21_23, T m21_24, T m21_25, T m21_26, T m21_27, T m21_28, T m21_29, T m21_30, T m21_31,
			T m22_0, T m22_1, T m22_2, T m22_3, T m22_4, T m22_5, T m22_6, T m22_7, T m22_8, T m22_9, T m22_10, T m22_11, T m22_12, T m22_13, T m22_14, T m22_15, T m22_16, T m22_17, T m22_18, T m22_19, T m22_20, T m22_21, T m22_22, T m22_23, T m22_24, T m22_25, T m22_26, T m22_27, T m22_28, T m22_29, T m22_30, T m22_31,
			T m23_0, T m23_1, T m23_2, T m23_3, T m23_4, T m23_5, T m23_6, T m23_7, T m23_8, T m23_9, T m23_10, T m23_11, T m23_12, T m23_13, T m23_14, T m23_15, T m23_16, T m23_17, T m23_18, T m23_19, T m23_20, T m23_21, T m23_22, T m23_23, T m23_24, T m23_25, T m23_26, T m23_27, T m23_28, T m23_29, T m23_30, T m23_31,
			T m24_0, T m24_1, T m24_2, T m24_3, T m24_4, T m24_5, T m24_6, T m24_7, T m24_8, T m24_9, T m24_10, T m24_11, T m24_12, T m24_13, T m24_14, T m24_15, T m24_16, T m24_17, T m24_18, T m24_19, T m24_20, T m24_21, T m24_22, T m24_23, T m24_24, T m24_25, T m24_26, T m24_27, T m24_28, T m24_29, T m24_30, T m24_31,
			T m25_0, T m25_1, T m25_2, T m25_3, T m25_4, T m25_5, T m25_6, T m25_7, T m25_8, T m25_9, T m25_10, T m25_11, T m25_12, T m25_13, T m25_14, T m25_15, T m25_16, T m25_17, T m25_18, T m25_19, T m25_20, T m25_21, T m25_22, T m25_23, T m25_24, T m25_25, T m25_26, T m25_27, T m25_28, T m25_29, T m25_30, T m25_31,
			T m26_0, T m26_1, T m26_2, T m26_3, T m26_4, T m26_5, T m26_6, T m26_7, T m26_8, T m26_9, T m26_10, T m26_11, T m26_12, T m26_13, T m26_14, T m26_15, T m26_16, T m26_17, T m26_18, T m26_19, T m26_20, T m26_21, T m26_22, T m26_23, T m26_24, T m26_25, T m26_26, T m26_27, T m26_28, T m26_29, T m26_30, T m26_31,
			T m27_0, T m27_1, T m27_2, T m27_3, T m27_4, T m27_5, T m27_6, T m27_7, T m27_8, T m27_9, T m27_10, T m27_11, T m27_12, T m27_13, T m27_14, T m27_15, T m27_16, T m27_17, T m27_18, T m27_19, T m27_20, T m27_21, T m27_22, T m27_23, T m27_24, T m27_25, T m27_26, T m27_27, T m27_28, T m27_29, T m27_30, T m27_31,
			T m28_0, T m28_1, T m28_2, T m28_3, T m28_4, T m28_5, T m28_6, T m28_7, T m28_8, T m28_9, T m28_10, T m28_11, T m28_12, T m28_13, T m28_14, T m28_15, T m28_16, T m28_17, T m28_18, T m28_19, T m28_20, T m28_21, T m28_22, T m28_23, T m28_24, T m28_25, T m28_26, T m28_27, T m28_28, T m28_29, T m28_30, T m28_31,
			T m29_0, T m29_1, T m29_2, T m29_3, T m29_4, T m29_5, T m29_6, T m29_7, T m29_8, T m29_9, T m29_10, T m29_11, T m29_12, T m29_13, T m29_14, T m29_15, T m29_16, T m29_17, T m29_18, T m29_19, T m29_20, T m29_21, T m29_22, T m29_23, T m29_24, T m29_25, T m29_26, T m29_27, T m29_28, T m29_29, T m29_30, T m29_31,
			T m30_0, T m30_1, T m30_2, T m30_3, T m30_4, T m30_5, T m30_6, T m30_7, T m30_8, T m30_9, T m30_10, T m30_11, T m30_12, T m30_13, T m30_14, T m30_15, T m30_16, T m30_17, T m30_18, T m30_19, T m30_20, T m30_21, T m30_22, T m30_23, T m30_24, T m30_25, T m30_26, T m30_27, T m30_28, T m30_29, T m30_30, T m30_31,
			T m31_0, T m31_1, T m31_2, T m31_3, T m31_4, T m31_5, T m31_6, T m31_7, T m31_8, T m31_9, T m31_10, T m31_11, T m31_12, T m31_13, T m31_14, T m31_15, T m31_16, T m31_17, T m31_18, T m31_19, T m31_20, T m31_21, T m31_22, T m31_23, T m31_24, T m31_25, T m31_26, T m31_27, T m31_28, T m31_29, T m31_30, T m31_31)
			: m_data{
				{ m0_0, m0_1, m0_2, m0_3, m0_4, m0_5, m0_6, m0_7, m0_8, m0_9, m0_10, m0_11, m0_12, m0_13, m0_14, m0_15, m0_16, m0_17, m0_18, m0_19, m0_20, m0_21, m0_22, m0_23, m0_24, m0_25, m0_26, m0_27, m0_28, m0_29, m0_30, m0_31 },
				{ m1_0, m1_1, m1_2, m1_3, m1_4, m1_5, m1_6, m1_7, m1_8, m1_9, m1_10, m1_11, m1_12, m1_13, m1_14, m1_15, m1_16, m1_17, m1_18, m1_19, m1_20, m1_21, m1_22, m1_23, m1_24, m1_25, m1_26, m1_27, m1_28, m1_29, m1_30, m1_31 },
				{ m2_0, m2_1, m2_2, m2_3, m2_4, m2_5, m2_6, m2_7, m2_8, m2_9, m2_10, m2_11, m2_12, m2_13, m2_14, m2_15, m2_16, m2_17, m2_18, m2_19, m2_20, m2_21, m2_22, m2_23, m2_24, m2_25, m2_26, m2_27, m2_28, m2_29, m2_30, m2_31 },
				{ m3_0, m3_1, m3_2, m3_3, m3_4, m3_5, m3_6, m3_7, m3_8, m3_9, m3_10, m3_11, m3_12, m3_13, m3_14, m3_15, m3_16, m3_17, m3_18, m3_19, m3_20, m3_21, m3_22, m3_23, m3_24, m3_25, m3_26, m3_27, m3_28, m3_29, m3_30, m3_31 },
				{ m4_0, m4_1, m4_2, m4_3, m4_4, m4_5, m4_6, m4_7, m4_8, m4_9, m4_10, m4_11, m4_12, m4_13, m4_14, m4_15, m4_16, m4_17, m4_18, m4_19, m4_20, m4_21, m4_22, m4_23, m4_24, m4_25, m4_26, m4_27, m4_28, m4_29, m4_30, m4_31 },
				{ m5_0, m5_1, m5_2, m5_3, m5_4, m5_5, m5_6, m5_7, m5_8, m5_9, m5_10, m5_11, m5_12, m5_13, m5_14, m5_15, m5_16, m5_17, m5_18, m5_19, m5_20, m5_21, m5_22, m5_23, m5_24, m5_25, m5_26, m5_27, m5_28, m5_29, m5_30, m5_31 },
				{ m6_0, m6_1, m6_2, m6_3, m6_4, m6_5, m6_6, m6_7, m6_8, m6_9, m6_10, m6_11, m6_12, m6_13, m6_14, m6_15, m6_16, m6_17, m6_18, m6_19, m6_20, m6_21, m6_22, m6_23, m6_24, m6_25, m6_26, m6_27, m6_28, m6_29, m6_30, m6_31 },
				{ m7_0, m7_1, m7_2, m7_3, m7_4, m7_5, m7_6, m7_7, m7_8, m7_9, m7_10, m7_11, m7_12, m7_13, m7_14, m7_15, m7_16, m7_17, m7_18, m7_19, m7_20, m7_21, m7_22, m7_23, m7_24, m7_25, m7_26, m7_27, m7_28, m7_29, m7_30, m7_31 },
				{ m8_0, m8_1, m8_2, m8_3, m8_4, m8_5, m8_6, m8_7, m8_8, m8_9, m8_10, m8_11, m8_12, m8_13, m8_14, m8_15, m8_16, m8_17, m8_18, m8_19, m8_20, m8_21, m8_22, m8_23, m8_24, m8_25, m8_26, m8_27, m8_28, m8_29, m8_30, m8_31 },
				{ m9_0, m9_1, m9_2, m9_3, m9_4, m9_5, m9_6, m9_7, m9_8, m9_9, m9_10, m9_11, m9_12, m9_13, m9_14, m9_15, m9_16, m9_17, m9_18, m9_19, m9_20, m9_21, m9_22, m9_23, m9_24, m9_25, m9_26, m9_27, m9_28, m9_29, m9_30, m9_31 },
				{ m10_0, m10_1, m10_2, m10_3, m10_4, m10_5, m10_6, m10_7, m10_8, m10_9, m10_10, m10_11, m10_12, m10_13, m10_14, m10_15, m10_16, m10_17, m10_18, m10_19, m10_20, m10_21, m10_22, m10_23, m10_24, m10_25, m10_26, m10_27, m10_28, m10_29, m10_30, m10_31 },
				{ m11_0, m11_1, m11_2, m11_3, m11_4, m11_5, m11_6, m11_7, m11_8, m11_9, m11_10, m11_11, m11_12, m11_13, m11_14, m11_15, m11_16, m11_17, m11_18, m11_19, m11_20, m11_21, m11_22, m11_23, m11_24, m11_25, m11_26, m11_27, m11_28, m11_29, m11_30, m11_31 },
				{ m12_0, m12_1, m12_2, m12_3, m12_4, m12_5, m12_6, m12_7, m12_8, m12_9, m12_10, m12_11, m12_12, m12_13, m12_14, m12_15, m12_16, m12_17, m12_18, m12_19, m12_20, m12_21, m12_22, m12_23, m12_24, m12_25, m12_26, m12_27, m12_28, m12_29, m12_30, m12_31 },
				{ m13_0, m13_1, m13_2, m13_3, m13_4, m13_5, m13_6, m13_7, m13_8, m13_9, m13_10, m13_11, m13_12, m13_13, m13_14, m13_15, m13_16, m13_17, m13_18, m13_19, m13_20, m13_21, m13_22, m13_23, m13_24, m13_25, m13_26, m13_27, m13_28, m13_29, m13_30, m13_31 },
				{ m14_0, m14_1, m14_2, m14_3, m14_4, m14_5, m14_6, m14_7, m14_8, m14_9, m14_10, m14_11, m14_12, m14_13, m14_14, m14_15, m14_16, m14_17, m14_18, m14_19, m14_20, m14_21, m14_22, m14_23, m14_24, m14_25, m14_26, m14_27, m14_28, m14_29, m14_30, m14_31 },
				{ m15_0, m15_1, m15_2, m15_3, m15_4, m15_5, m15_6, m15_7, m15_8, m15_9, m15_10, m15_11, m15_12, m15_13, m15_14, m15_15, m15_16, m15_17, m15_18, m15_19, m15_20, m15_21, m15_22, m15_23, m15_24, m15_25, m15_26, m15_27, m15_28, m15_29, m15_30, m15_31 },
				{ m16_0, m16_1, m16_2, m16_3, m16_4, m16_5, m16_6, m16_7, m16_8, m16_9, m16_10, m16_11, m16_12, m16_13, m16_14, m16_15, m16_16, m16_17, m16_18, m16_19, m16_20, m16_21, m16_22, m16_23, m16_24, m16_25, m16_26, m16_27, m16_28, m16_29, m16_30, m16_31 },
				{ m17_0, m17_1, m17_2, m17_3, m17_4, m17_5, m17_6, m17_7, m17_8, m17_9, m17_10, m17_11, m17_12, m17_13, m17_14, m17_15, m17_16, m17_17, m17_18, m17_19, m17_20, m17_21, m17_22, m17_23, m17_24, m17_25, m17_26, m17_27, m17_28, m17_29, m17_30, m17_31 },
				{ m18_0, m18_1, m18_2, m18_3, m18_4, m18_5, m18_6, m18_7, m18_8, m18_9, m18_10, m18_11, m18_12, m18_13, m18_14, m18_15, m18_16, m18_17, m18_18, m18_19, m18_20, m18_21, m18_22, m18_23, m18_24, m18_25, m18_26, m18_27, m18_28, m18_29, m18_30, m18_31 },
				{ m19_0, m19_1, m19_2, m19_3, m19_4, m19_5, m19_6, m19_7, m19_8, m19_9, m19_10, m19_11, m19_12, m19_13, m19_14, m19_15, m19_16, m19_17, m19_18, m19_19, m19_20, m19_21, m19_22, m19_23, m19_24, m19_25, m19_26, m19_27, m19_28, m19_29, m19_30, m19_31 },
				{ m20_0, m20_1, m20_2, m20_3, m20_4, m20_5, m20_6, m20_7, m20_8, m20_9, m20_10, m20_11, m20_12, m20_13, m20_14, m20_15, m20_16, m20_17, m20_18, m20_19, m20_20, m20_21, m20_22, m20_23, m20_24, m20_25, m20_26, m20_27, m20_28, m20_29, m20_30, m20_31 },
				{ m21_0, m21_1, m21_2, m21_3, m21_4, m21_5, m21_6, m21_7, m21_8, m21_9, m21_10, m21_11, m21_12, m21_13, m21_14, m21_15, m21_16, m21_17, m21_18, m21_19, m21_20, m21_21, m21_22, m21_23, m21_24, m21_25, m21_26, m21_27, m21_28, m21_29, m21_30, m21_31 },
				{ m22_0, m22_1, m22_2, m22_3, m22_4, m22_5, m22_6, m22_7, m22_8, m22_9, m22_10, m22_11, m22_12, m22_13, m22_14, m22_15, m22_16, m22_17, m22_18, m22_19, m22_20, m22_21, m22_22, m22_23, m22_24, m22_25, m22_26, m22_27, m22_28, m22_29, m22_30, m22_31 },
				{ m23_0, m23_1, m23_2, m23_3, m23_4, m23_5, m23_6, m23_7, m23_8, m23_9, m23_10, m23_11, m23_12, m23_13, m23_14, m23_15, m23_16, m23_17, m23_18, m23_19, m23_20, m23_21, m23_22, m23_23, m23_24, m23_25, m23_26, m23_27, m23_28, m23_29, m23_30, m23_31 },
				{ m24_0, m24_1, m24_2, m24_3, m24_4, m24_5, m24_6, m24_7, m24_8, m24_9, m24_10, m24_11, m24_12, m24_13, m24_14, m24_15, m24_16, m24_17, m24_18, m24_19, m24_20, m24_21, m24_22, m24_23, m24_24, m24_25, m24_26, m24_27, m24_28, m24_29, m24_30, m24_31 },
				{ m25_0, m25_1, m25_2, m25_3, m25_4, m25_5, m25_6, m25_7, m25_8, m25_9, m25_10, m25_11, m25_12, m25_13, m25_14, m25_15, m25_16, m25_17, m25_18, m25_19, m25_20, m25_21, m25_22, m25_23, m25_24, m25_25, m25_26, m25_27, m25_28, m25_29, m25_30, m25_31 },
				{ m26_0, m26_1, m26_2, m26_3, m26_4, m26_5, m26_6, m26_7, m26_8, m26_9, m26_10, m26_11, m26_12, m26_13, m26_14, m26_15, m26_16, m26_17, m26_18, m26_19, m26_20, m26_21, m26_22, m26_23, m26_24, m26_25, m26_26, m26_27, m26_28, m26_29, m26_30, m26_31 },
				{ m27_0, m27_1, m27_2, m27_3, m27_4, m27_5, m27_6, m27_7, m27_8, m27_9, m27_10, m27_11, m27_12, m27_13, m27_14, m27_15, m27_16, m27_17, m27_18, m27_19, m27_20, m27_21, m27_22, m27_23, m27_24, m27_25, m27_26, m27_27, m27_28, m27_29, m27_30, m27_31 },
				{ m28_0, m28_1, m28_2, m28_3, m28_4, m28_5, m28_6, m28_7, m28_8, m28_9, m28_10, m28_11, m28_12, m28_13, m28_14, m28_15, m28_16, m28_17, m28_18, m28_19, m28_20, m28_21, m28_22, m28_23, m28_24, m28_25, m28_26, m28_27, m28_28, m28_29, m28_30, m28_31 },
				{ m29_0, m29_1, m29_2, m29_3, m29_4, m29_5, m29_6, m29_7, m29_8, m29_9, m29_10, m29_11, m29_12, m29_13, m29_14, m29_15, m29_16, m29_17, m29_18, m29_19, m29_20, m29_21, m29_22, m29_23, m29_24, m29_25, m29_26, m29_27, m29_28, m29_29, m29_30, m29_31 },
				{ m30_0, m30_1, m30_2, m30_3, m30_4, m30_5, m30_6, m30_7, m30_8, m30_9, m30_10, m30_11, m30_12, m30_13, m30_14, m30_15, m30_16, m30_17, m30_18, m30_19, m30_20, m30_21, m30_22, m30_23, m30_24, m30_25, m30_26, m30_27, m30_28, m30_29, m30_30, m30_31 },
				{ m31_0, m31_1, m31_2, m31_3, m31_4, m31_5, m31_6, m31_7, m31_8, m31_9, m31_10, m31_11, m31_12, m31_13, m31_14, m31_15, m31_16, m31_17, m31_18, m31_19, m31_20, m31_21, m31_22, m31_23, m31_24, m31_25, m31_26, m31_27, m31_28, m31_29, m31_30, m31_31 }
			} {}

		/// @brief Copy constructor.
		///
		/// This constructor copies the input matrix.
		/// 
		/// @param other is the matrix to copy.
		/// 
		Mat32x32(const Mat32x32& other)
			: m_data{
				{ other[0][0], other[0][1], other[0][2], other[0][3], other[0][4], other[0][5], other[0][6], other[0][7], other[0][8], other[0][9], other[0][10], other[0][11], other[0][12], other[0][13], other[0][14], other[0][15], other[0][16], other[0][17], other[0][18], other[0][19], other[0][20], other[0][21], other[0][22], other[0][23], other[0][24], other[0][25], other[0][26], other[0][27], other[0][28], other[0][29], other[0][30], other[0][31] },
				{ other[1][0], other[1][1], other[1][2], other[1][3], other[1][4], other[1][5], other[1][6], other[1][7], other[1][8], other[1][9], other[1][10], other[1][11], other[1][12], other[1][13], other[1][14], other[1][15], other[1][16], other[1][17], other[1][18], other[1][19], other[1][20], other[1][21], other[1][22], other[1][23], other[1][24], other[1][25], other[1][26], other[1][27], other[1][28], other[1][29], other[1][30], other[1][31] },
				{ other[2][0], other[2][1], other[2][2], other[2][3], other[2][4], other[2][5], other[2][6], other[2][7], other[2][8], other[2][9], other[2][10], other[2][11], other[2][12], other[2][13], other[2][14], other[2][15], other[2][16], other[2][17], other[2][18], other[2][19], other[2][20], other[2][21], other[2][22], other[2][23], other[2][24], other[2][25], other[2][26], other[2][27], other[2][28], other[2][29], other[2][30], other[2][31] },
				{ other[3][0], other[3][1], other[3][2], other[3][3], other[3][4], other[3][5], other[3][6], other[3][7], other[3][8], other[3][9], other[3][10], other[3][11], other[3][12], other[3][13], other[3][14], other[3][15], other[3][16], other[3][17], other[3][18], other[3][19], other[3][20], other[3][21], other[3][22], other[3][23], other[3][24], other[3][25], other[3][26], other[3][27], other[3][28], other[3][29], other[3][30], other[3][31] },
				{ other[4][0], other[4][1], other[4][2], other[4][3], other[4][4], other[4][5], other[4][6], other[4][7], other[4][8], other[4][9], other[4][10], other[4][11], other[4][12], other[4][13], other[4][14], other[4][15], other[4][16], other[4][17], other[4][18], other[4][19], other[4][20], other[4][21], other[4][22], other[4][23], other[4][24], other[4][25], other[4][26], other[4][27], other[4][28], other[4][29], other[4][30], other[4][31] },
				{ other[5][0], other[5][1], other[5][2], other[5][3], other[5][4], other[5][5], other[5][6], other[5][7], other[5][8], other[5][9], other[5][10], other[5][11], other[5][12], other[5][13], other[5][14], other[5][15], other[5][16], other[5][17], other[5][18], other[5][19], other[5][20], other[5][21], other[5][22], other[5][23], other[5][24], other[5][25], other[5][26], other[5][27], other[5][28], other[5][29], other[5][30], other[5][31] },
				{ other[6][0], other[6][1], other[6][2], other[6][3], other[6][4], other[6][5], other[6][6], other[6][7], other[6][8], other[6][9], other[6][10], other[6][11], other[6][12], other[6][13], other[6][14], other[6][15], other[6][16], other[6][17], other[6][18], other[6][19], other[6][20], other[6][21], other[6][22], other[6][23], other[6][24], other[6][25], other[6][26], other[6][27], other[6][28], other[6][29], other[6][30], other[6][31] },
				{ other[7][0], other[7][1], other[7][2], other[7][3], other[7][4], other[7][5], other[7][6], other[7][7], other[7][8], other[7][9], other[7][10], other[7][11], other[7][12], other[7][13], other[7][14], other[7][15], other[7][16], other[7][17], other[7][18], other[7][19], other[7][20], other[7][21], other[7][22], other[7][23], other[7][24], other[7][25], other[7][26], other[7][27], other[7][28], other[7][29], other[7][30], other[7][31] },
				{ other[8][0], other[8][1], other[8][2], other[8][3], other[8][4], other[8][5], other[8][6], other[8][7], other[8][8], other[8][9], other[8][10], other[8][11], other[8][12], other[8][13], other[8][14], other[8][15], other[8][16], other[8][17], other[8][18], other[8][19], other[8][20], other[8][21], other[8][22], other[8][23], other[8][24], other[8][25], other[8][26], other[8][27], other[8][28], other[8][29], other[8][30], other[8][31] },
				{ other[9][0], other[9][1], other[9][2], other[9][3], other[9][4], other[9][5], other[9][6], other[9][7], other[9][8], other[9][9], other[9][10], other[9][11], other[9][12], other[9][13], other[9][14], other[9][15], other[9][16], other[9][17], other[9][18], other[9][19], other[9][20], other[9][21], other[9][22], other[9][23], other[9][24], other[9][25], other[9][26], other[9][27], other[9][28], other[9][29], other[9][30], other[9][31] },
				{ other[10][0], other[10][1], other[10][2], other[10][3], other[10][4], other[10][5], other[10][6], other[10][7], other[10][8], other[10][9], other[10][10], other[10][11], other[10][12], other[10][13], other[10][14], other[10][15], other[10][16], other[10][17], other[10][18], other[10][19], other[10][20], other[10][21], other[10][22], other[10][23], other[10][24], other[10][25], other[10][26], other[10][27], other[10][28], other[10][29], other[10][30], other[10][31] },
				{ other[11][0], other[11][1], other[11][2], other[11][3], other[11][4], other[11][5], other[11][6], other[11][7], other[11][8], other[11][9], other[11][10], other[11][11], other[11][12], other[11][13], other[11][14], other[11][15], other[11][16], other[11][17], other[11][18], other[11][19], other[11][20], other[11][21], other[11][22], other[11][23], other[11][24], other[11][25], other[11][26], other[11][27], other[11][28], other[11][29], other[11][30], other[11][31] },
				{ other[12][0], other[12][1], other[12][2], other[12][3], other[12][4], other[12][5], other[12][6], other[12][7], other[12][8], other[12][9], other[12][10], other[12][11], other[12][12], other[12][13], other[12][14], other[12][15], other[12][16], other[12][17], other[12][18], other[12][19], other[12][20], other[12][21], other[12][22], other[12][23], other[12][24], other[12][25], other[12][26], other[12][27], other[12][28], other[12][29], other[12][30], other[12][31] },
				{ other[13][0], other[13][1], other[13][2], other[13][3], other[13][4], other[13][5], other[13][6], other[13][7], other[13][8], other[13][9], other[13][10], other[13][11], other[13][12], other[13][13], other[13][14], other[13][15], other[13][16], other[13][17], other[13][18], other[13][19], other[13][20], other[13][21], other[13][22], other[13][23], other[13][24], other[13][25], other[13][26], other[13][27], other[13][28], other[13][29], other[13][30], other[13][31] },
				{ other[14][0], other[14][1], other[14][2], other[14][3], other[14][4], other[14][5], other[14][6], other[14][7], other[14][8], other[14][9], other[14][10], other[14][11], other[14][12], other[14][13], other[14][14], other[14][15], other[14][16], other[14][17], other[14][18], other[14][19], other[14][20], other[14][21], other[14][22], other[14][23], other[14][24], other[14][25], other[14][26], other[14][27], other[14][28], other[14][29], other[14][30], other[14][31] },
				{ other[15][0], other[15][1], other[15][2], other[15][3], other[15][4], other[15][5], other[15][6], other[15][7], other[15][8], other[15][9], other[15][10], other[15][11], other[15][12], other[15][13], other[15][14], other[15][15], other[15][16], other[15][17], other[15][18], other[15][19], other[15][20], other[15][21], other[15][22], other[15][23], other[15][24], other[15][25], other[15][26], other[15][27], other[15][28], other[15][29], other[15][30], other[15][31] },
				{ other[16][0], other[16][1], other[16][2], other[16][3], other[16][4], other[16][5], other[16][6], other[16][7], other[16][8], other[16][9], other[16][10], other[16][11], other[16][12], other[16][13], other[16][14], other[16][15], other[16][16], other[16][17], other[16][18], other[16][19], other[16][20], other[16][21], other[16][22], other[16][23], other[16][24], other[16][25], other[16][26], other[16][27], other[16][28], other[16][29], other[16][30], other[16][31] },
				{ other[17][0], other[17][1], other[17][2], other[17][3], other[17][4], other[17][5], other[17][6], other[17][7], other[17][8], other[17][9], other[17][10], other[17][11], other[17][12], other[17][13], other[17][14], other[17][15], other[17][16], other[17][17], other[17][18], other[17][19], other[17][20], other[17][21], other[17][22], other[17][23], other[17][24], other[17][25], other[17][26], other[17][27], other[17][28], other[17][29], other[17][30], other[17][31] },
				{ other[18][0], other[18][1], other[18][2], other[18][3], other[18][4], other[18][5], other[18][6], other[18][7], other[18][8], other[18][9], other[18][10], other[18][11], other[18][12], other[18][13], other[18][14], other[18][15], other[18][16], other[18][17], other[18][18], other[18][19], other[18][20], other[18][21], other[18][22], other[18][23], other[18][24], other[18][25], other[18][26], other[18][27], other[18][28], other[18][29], other[18][30], other[18][31] },
				{ other[19][0], other[19][1], other[19][2], other[19][3], other[19][4], other[19][5], other[19][6], other[19][7], other[19][8], other[19][9], other[19][10], other[19][11], other[19][12], other[19][13], other[19][14], other[19][15], other[19][16], other[19][17], other[19][18], other[19][19], other[19][20], other[19][21], other[19][22], other[19][23], other[19][24], other[19][25], other[19][26], other[19][27], other[19][28], other[19][29], other[19][30], other[19][31] },
				{ other[20][0], other[20][1], other[20][2], other[20][3], other[20][4], other[20][5], other[20][6], other[20][7], other[20][8], other[20][9], other[20][10], other[20][11], other[20][12], other[20][13], other[20][14], other[20][15], other[20][16], other[20][17], other[20][18], other[20][19], other[20][20], other[20][21], other[20][22], other[20][23], other[20][24], other[20][25], other[20][26], other[20][27], other[20][28], other[20][29], other[20][30], other[20][31] },
				{ other[21][0], other[21][1], other[21][2], other[21][3], other[21][4], other[21][5], other[21][6], other[21][7], other[21][8], other[21][9], other[21][10], other[21][11], other[21][12], other[21][13], other[21][14], other[21][15], other[21][16], other[21][17], other[21][18], other[21][19], other[21][20], other[21][21], other[21][22], other[21][23], other[21][24], other[21][25], other[21][26], other[21][27], other[21][28], other[21][29], other[21][30], other[21][31] },
				{ other[22][0], other[22][1], other[22][2], other[22][3], other[22][4], other[22][5], other[22][6], other[22][7], other[22][8], other[22][9], other[22][10], other[22][11], other[22][12], other[22][13], other[22][14], other[22][15], other[22][16], other[22][17], other[22][18], other[22][19], other[22][20], other[22][21], other[22][22], other[22][23], other[22][24], other[22][25], other[22][26], other[22][27], other[22][28], other[22][29], other[22][30], other[22][31] },
				{ other[23][0], other[23][1], other[23][2], other[23][3], other[23][4], other[23][5], other[23][6], other[23][7], other[23][8], other[23][9], other[23][10], other[23][11], other[23][12], other[23][13], other[23][14], other[23][15], other[23][16], other[23][17], other[23][18], other[23][19], other[23][20], other[23][21], other[23][22], other[23][23], other[23][24], other[23][25], other[23][26], other[23][27], other[23][28], other[23][29], other[23][30], other[23][31] },
				{ other[24][0], other[24][1], other[24][2], other[24][3], other[24][4], other[24][5], other[24][6], other[24][7], other[24][8], other[24][9], other[24][10], other[24][11], other[24][12], other[24][13], other[24][14], other[24][15], other[24][16], other[24][17], other[24][18], other[24][19], other[24][20], other[24][21], other[24][22], other[24][23], other[24][24], other[24][25], other[24][26], other[24][27], other[24][28], other[24][29], other[24][30], other[24][31] },
				{ other[25][0], other[25][1], other[25][2], other[25][3], other[25][4], other[25][5], other[25][6], other[25][7], other[25][8], other[25][9], other[25][10], other[25][11], other[25][12], other[25][13], other[25][14], other[25][15], other[25][16], other[25][17], other[25][18], other[25][19], other[25][20], other[25][21], other[25][22], other[25][23], other[25][24], other[25][25], other[25][26], other[25][27], other[25][28], other[25][29], other[25][30], other[25][31] },
				{ other[26][0], other[26][1], other[26][2], other[26][3], other[26][4], other[26][5], other[26][6], other[26][7], other[26][8], other[26][9], other[26][10], other[26][11], other[26][12], other[26][13], other[26][14], other[26][15], other[26][16], other[26][17], other[26][18], other[26][19], other[26][20], other[26][21], other[26][22], other[26][23], other[26][24], other[26][25], other[26][26], other[26][27], other[26][28], other[26][29], other[26][30], other[26][31] },
				{ other[27][0], other[27][1], other[27][2], other[27][3], other[27][4], other[27][5], other[27][6], other[27][7], other[27][8], other[27][9], other[27][10], other[27][11], other[27][12], other[27][13], other[27][14], other[27][15], other[27][16], other[27][17], other[27][18], other[27][19], other[27][20], other[27][21], other[27][22], other[27][23], other[27][24], other[27][25], other[27][26], other[27][27], other[27][28], other[27][29], other[27][30], other[27][31] },
				{ other[28][0], other[28][1], other[28][2], other[28][3], other[28][4], other[28][5], other[28][6], other[28][7], other[28][8], other[28][9], other[28][10], other[28][11], other[28][12], other[28][13], other[28][14], other[28][15], other[28][16], other[28][17], other[28][18], other[28][19], other[28][20], other[28][21], other[28][22], other[28][23], other[28][24], other[28][25], other[28][26], other[28][27], other[28][28], other[28][29], other[28][30], other[28][31] },
				{ other[29][0], other[29][1], other[29][2], other[29][3], other[29][4], other[29][5], other[29][6], other[29][7], other[29][8], other[29][9], other[29][10], other[29][11], other[29][12], other[29][13], other[29][14], other[29][15], other[29][16], other[29][17], other[29][18], other[29][19], other[29][20], other[29][21], other[29][22], other[29][23], other[29][24], other[29][25], other[29][26], other[29][27], other[29][28], other[29][29], other[29][30], other[29][31] },
				{ other[30][0], other[30][1], other[30][2], other[30][3], other[30][4], other[30][5], other[30][6], other[30][7], other[30][8], other[30][9], other[30][10], other[30][11], other[30][12], other[30][13], other[30][14], other[30][15], other[30][16], other[30][17], other[30][18], other[30][19], other[30][20], other[30][21], other[30][22], other[30][23], other[30][24], other[30][25], other[30][26], other[30][27], other[30][28], other[30][29], other[30][30], other[30][31] },
				{ other[31][0], other[31][1], other[31][2], other[31][3], other[31][4], other[31][5], other[31][6], other[31][7], other[31][8], other[31][9], other[31][10], other[31][11], other[31][12], other[31][13], other[31][14], other[31][15], other[31][16], other[31][17], other[31][18], other[31][19], other[31][20], other[31][21], other[31][22], other[31][23], other[31][24], other[31][25], other[31][26], other[31][27], other[31][28], other[31][29], other[31][30], other[31][31] }
			} {}


		/// @return the identity matrix.
		/// 
		static Mat32x32<T> identity()
		{
			return Mat32x32<T>(1);
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
		Mat32x32& operator+=(const Mat32x32& rhs)
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
			m_data[0][16] += rhs[0][16];
			m_data[0][17] += rhs[0][17];
			m_data[0][18] += rhs[0][18];
			m_data[0][19] += rhs[0][19];
			m_data[0][20] += rhs[0][20];
			m_data[0][21] += rhs[0][21];
			m_data[0][22] += rhs[0][22];
			m_data[0][23] += rhs[0][23];
			m_data[0][24] += rhs[0][24];
			m_data[0][25] += rhs[0][25];
			m_data[0][26] += rhs[0][26];
			m_data[0][27] += rhs[0][27];
			m_data[0][28] += rhs[0][28];
			m_data[0][29] += rhs[0][29];
			m_data[0][30] += rhs[0][30];
			m_data[0][31] += rhs[0][31];

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
			m_data[1][16] += rhs[1][16];
			m_data[1][17] += rhs[1][17];
			m_data[1][18] += rhs[1][18];
			m_data[1][19] += rhs[1][19];
			m_data[1][20] += rhs[1][20];
			m_data[1][21] += rhs[1][21];
			m_data[1][22] += rhs[1][22];
			m_data[1][23] += rhs[1][23];
			m_data[1][24] += rhs[1][24];
			m_data[1][25] += rhs[1][25];
			m_data[1][26] += rhs[1][26];
			m_data[1][27] += rhs[1][27];
			m_data[1][28] += rhs[1][28];
			m_data[1][29] += rhs[1][29];
			m_data[1][30] += rhs[1][30];
			m_data[1][31] += rhs[1][31];

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
			m_data[2][16] += rhs[2][16];
			m_data[2][17] += rhs[2][17];
			m_data[2][18] += rhs[2][18];
			m_data[2][19] += rhs[2][19];
			m_data[2][20] += rhs[2][20];
			m_data[2][21] += rhs[2][21];
			m_data[2][22] += rhs[2][22];
			m_data[2][23] += rhs[2][23];
			m_data[2][24] += rhs[2][24];
			m_data[2][25] += rhs[2][25];
			m_data[2][26] += rhs[2][26];
			m_data[2][27] += rhs[2][27];
			m_data[2][28] += rhs[2][28];
			m_data[2][29] += rhs[2][29];
			m_data[2][30] += rhs[2][30];
			m_data[2][31] += rhs[2][31];

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
			m_data[3][16] += rhs[3][16];
			m_data[3][17] += rhs[3][17];
			m_data[3][18] += rhs[3][18];
			m_data[3][19] += rhs[3][19];
			m_data[3][20] += rhs[3][20];
			m_data[3][21] += rhs[3][21];
			m_data[3][22] += rhs[3][22];
			m_data[3][23] += rhs[3][23];
			m_data[3][24] += rhs[3][24];
			m_data[3][25] += rhs[3][25];
			m_data[3][26] += rhs[3][26];
			m_data[3][27] += rhs[3][27];
			m_data[3][28] += rhs[3][28];
			m_data[3][29] += rhs[3][29];
			m_data[3][30] += rhs[3][30];
			m_data[3][31] += rhs[3][31];

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
			m_data[4][16] += rhs[4][16];
			m_data[4][17] += rhs[4][17];
			m_data[4][18] += rhs[4][18];
			m_data[4][19] += rhs[4][19];
			m_data[4][20] += rhs[4][20];
			m_data[4][21] += rhs[4][21];
			m_data[4][22] += rhs[4][22];
			m_data[4][23] += rhs[4][23];
			m_data[4][24] += rhs[4][24];
			m_data[4][25] += rhs[4][25];
			m_data[4][26] += rhs[4][26];
			m_data[4][27] += rhs[4][27];
			m_data[4][28] += rhs[4][28];
			m_data[4][29] += rhs[4][29];
			m_data[4][30] += rhs[4][30];
			m_data[4][31] += rhs[4][31];

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
			m_data[5][16] += rhs[5][16];
			m_data[5][17] += rhs[5][17];
			m_data[5][18] += rhs[5][18];
			m_data[5][19] += rhs[5][19];
			m_data[5][20] += rhs[5][20];
			m_data[5][21] += rhs[5][21];
			m_data[5][22] += rhs[5][22];
			m_data[5][23] += rhs[5][23];
			m_data[5][24] += rhs[5][24];
			m_data[5][25] += rhs[5][25];
			m_data[5][26] += rhs[5][26];
			m_data[5][27] += rhs[5][27];
			m_data[5][28] += rhs[5][28];
			m_data[5][29] += rhs[5][29];
			m_data[5][30] += rhs[5][30];
			m_data[5][31] += rhs[5][31];

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
			m_data[6][16] += rhs[6][16];
			m_data[6][17] += rhs[6][17];
			m_data[6][18] += rhs[6][18];
			m_data[6][19] += rhs[6][19];
			m_data[6][20] += rhs[6][20];
			m_data[6][21] += rhs[6][21];
			m_data[6][22] += rhs[6][22];
			m_data[6][23] += rhs[6][23];
			m_data[6][24] += rhs[6][24];
			m_data[6][25] += rhs[6][25];
			m_data[6][26] += rhs[6][26];
			m_data[6][27] += rhs[6][27];
			m_data[6][28] += rhs[6][28];
			m_data[6][29] += rhs[6][29];
			m_data[6][30] += rhs[6][30];
			m_data[6][31] += rhs[6][31];

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
			m_data[7][16] += rhs[7][16];
			m_data[7][17] += rhs[7][17];
			m_data[7][18] += rhs[7][18];
			m_data[7][19] += rhs[7][19];
			m_data[7][20] += rhs[7][20];
			m_data[7][21] += rhs[7][21];
			m_data[7][22] += rhs[7][22];
			m_data[7][23] += rhs[7][23];
			m_data[7][24] += rhs[7][24];
			m_data[7][25] += rhs[7][25];
			m_data[7][26] += rhs[7][26];
			m_data[7][27] += rhs[7][27];
			m_data[7][28] += rhs[7][28];
			m_data[7][29] += rhs[7][29];
			m_data[7][30] += rhs[7][30];
			m_data[7][31] += rhs[7][31];

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
			m_data[8][16] += rhs[8][16];
			m_data[8][17] += rhs[8][17];
			m_data[8][18] += rhs[8][18];
			m_data[8][19] += rhs[8][19];
			m_data[8][20] += rhs[8][20];
			m_data[8][21] += rhs[8][21];
			m_data[8][22] += rhs[8][22];
			m_data[8][23] += rhs[8][23];
			m_data[8][24] += rhs[8][24];
			m_data[8][25] += rhs[8][25];
			m_data[8][26] += rhs[8][26];
			m_data[8][27] += rhs[8][27];
			m_data[8][28] += rhs[8][28];
			m_data[8][29] += rhs[8][29];
			m_data[8][30] += rhs[8][30];
			m_data[8][31] += rhs[8][31];

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
			m_data[9][16] += rhs[9][16];
			m_data[9][17] += rhs[9][17];
			m_data[9][18] += rhs[9][18];
			m_data[9][19] += rhs[9][19];
			m_data[9][20] += rhs[9][20];
			m_data[9][21] += rhs[9][21];
			m_data[9][22] += rhs[9][22];
			m_data[9][23] += rhs[9][23];
			m_data[9][24] += rhs[9][24];
			m_data[9][25] += rhs[9][25];
			m_data[9][26] += rhs[9][26];
			m_data[9][27] += rhs[9][27];
			m_data[9][28] += rhs[9][28];
			m_data[9][29] += rhs[9][29];
			m_data[9][30] += rhs[9][30];
			m_data[9][31] += rhs[9][31];

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
			m_data[10][16] += rhs[10][16];
			m_data[10][17] += rhs[10][17];
			m_data[10][18] += rhs[10][18];
			m_data[10][19] += rhs[10][19];
			m_data[10][20] += rhs[10][20];
			m_data[10][21] += rhs[10][21];
			m_data[10][22] += rhs[10][22];
			m_data[10][23] += rhs[10][23];
			m_data[10][24] += rhs[10][24];
			m_data[10][25] += rhs[10][25];
			m_data[10][26] += rhs[10][26];
			m_data[10][27] += rhs[10][27];
			m_data[10][28] += rhs[10][28];
			m_data[10][29] += rhs[10][29];
			m_data[10][30] += rhs[10][30];
			m_data[10][31] += rhs[10][31];

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
			m_data[11][16] += rhs[11][16];
			m_data[11][17] += rhs[11][17];
			m_data[11][18] += rhs[11][18];
			m_data[11][19] += rhs[11][19];
			m_data[11][20] += rhs[11][20];
			m_data[11][21] += rhs[11][21];
			m_data[11][22] += rhs[11][22];
			m_data[11][23] += rhs[11][23];
			m_data[11][24] += rhs[11][24];
			m_data[11][25] += rhs[11][25];
			m_data[11][26] += rhs[11][26];
			m_data[11][27] += rhs[11][27];
			m_data[11][28] += rhs[11][28];
			m_data[11][29] += rhs[11][29];
			m_data[11][30] += rhs[11][30];
			m_data[11][31] += rhs[11][31];

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
			m_data[12][16] += rhs[12][16];
			m_data[12][17] += rhs[12][17];
			m_data[12][18] += rhs[12][18];
			m_data[12][19] += rhs[12][19];
			m_data[12][20] += rhs[12][20];
			m_data[12][21] += rhs[12][21];
			m_data[12][22] += rhs[12][22];
			m_data[12][23] += rhs[12][23];
			m_data[12][24] += rhs[12][24];
			m_data[12][25] += rhs[12][25];
			m_data[12][26] += rhs[12][26];
			m_data[12][27] += rhs[12][27];
			m_data[12][28] += rhs[12][28];
			m_data[12][29] += rhs[12][29];
			m_data[12][30] += rhs[12][30];
			m_data[12][31] += rhs[12][31];

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
			m_data[13][16] += rhs[13][16];
			m_data[13][17] += rhs[13][17];
			m_data[13][18] += rhs[13][18];
			m_data[13][19] += rhs[13][19];
			m_data[13][20] += rhs[13][20];
			m_data[13][21] += rhs[13][21];
			m_data[13][22] += rhs[13][22];
			m_data[13][23] += rhs[13][23];
			m_data[13][24] += rhs[13][24];
			m_data[13][25] += rhs[13][25];
			m_data[13][26] += rhs[13][26];
			m_data[13][27] += rhs[13][27];
			m_data[13][28] += rhs[13][28];
			m_data[13][29] += rhs[13][29];
			m_data[13][30] += rhs[13][30];
			m_data[13][31] += rhs[13][31];

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
			m_data[14][16] += rhs[14][16];
			m_data[14][17] += rhs[14][17];
			m_data[14][18] += rhs[14][18];
			m_data[14][19] += rhs[14][19];
			m_data[14][20] += rhs[14][20];
			m_data[14][21] += rhs[14][21];
			m_data[14][22] += rhs[14][22];
			m_data[14][23] += rhs[14][23];
			m_data[14][24] += rhs[14][24];
			m_data[14][25] += rhs[14][25];
			m_data[14][26] += rhs[14][26];
			m_data[14][27] += rhs[14][27];
			m_data[14][28] += rhs[14][28];
			m_data[14][29] += rhs[14][29];
			m_data[14][30] += rhs[14][30];
			m_data[14][31] += rhs[14][31];

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
			m_data[15][16] += rhs[15][16];
			m_data[15][17] += rhs[15][17];
			m_data[15][18] += rhs[15][18];
			m_data[15][19] += rhs[15][19];
			m_data[15][20] += rhs[15][20];
			m_data[15][21] += rhs[15][21];
			m_data[15][22] += rhs[15][22];
			m_data[15][23] += rhs[15][23];
			m_data[15][24] += rhs[15][24];
			m_data[15][25] += rhs[15][25];
			m_data[15][26] += rhs[15][26];
			m_data[15][27] += rhs[15][27];
			m_data[15][28] += rhs[15][28];
			m_data[15][29] += rhs[15][29];
			m_data[15][30] += rhs[15][30];
			m_data[15][31] += rhs[15][31];

			m_data[16][0] += rhs[16][0];
			m_data[16][1] += rhs[16][1];
			m_data[16][2] += rhs[16][2];
			m_data[16][3] += rhs[16][3];
			m_data[16][4] += rhs[16][4];
			m_data[16][5] += rhs[16][5];
			m_data[16][6] += rhs[16][6];
			m_data[16][7] += rhs[16][7];
			m_data[16][8] += rhs[16][8];
			m_data[16][9] += rhs[16][9];
			m_data[16][10] += rhs[16][10];
			m_data[16][11] += rhs[16][11];
			m_data[16][12] += rhs[16][12];
			m_data[16][13] += rhs[16][13];
			m_data[16][14] += rhs[16][14];
			m_data[16][15] += rhs[16][15];
			m_data[16][16] += rhs[16][16];
			m_data[16][17] += rhs[16][17];
			m_data[16][18] += rhs[16][18];
			m_data[16][19] += rhs[16][19];
			m_data[16][20] += rhs[16][20];
			m_data[16][21] += rhs[16][21];
			m_data[16][22] += rhs[16][22];
			m_data[16][23] += rhs[16][23];
			m_data[16][24] += rhs[16][24];
			m_data[16][25] += rhs[16][25];
			m_data[16][26] += rhs[16][26];
			m_data[16][27] += rhs[16][27];
			m_data[16][28] += rhs[16][28];
			m_data[16][29] += rhs[16][29];
			m_data[16][30] += rhs[16][30];
			m_data[16][31] += rhs[16][31];

			m_data[17][0] += rhs[17][0];
			m_data[17][1] += rhs[17][1];
			m_data[17][2] += rhs[17][2];
			m_data[17][3] += rhs[17][3];
			m_data[17][4] += rhs[17][4];
			m_data[17][5] += rhs[17][5];
			m_data[17][6] += rhs[17][6];
			m_data[17][7] += rhs[17][7];
			m_data[17][8] += rhs[17][8];
			m_data[17][9] += rhs[17][9];
			m_data[17][10] += rhs[17][10];
			m_data[17][11] += rhs[17][11];
			m_data[17][12] += rhs[17][12];
			m_data[17][13] += rhs[17][13];
			m_data[17][14] += rhs[17][14];
			m_data[17][15] += rhs[17][15];
			m_data[17][16] += rhs[17][16];
			m_data[17][17] += rhs[17][17];
			m_data[17][18] += rhs[17][18];
			m_data[17][19] += rhs[17][19];
			m_data[17][20] += rhs[17][20];
			m_data[17][21] += rhs[17][21];
			m_data[17][22] += rhs[17][22];
			m_data[17][23] += rhs[17][23];
			m_data[17][24] += rhs[17][24];
			m_data[17][25] += rhs[17][25];
			m_data[17][26] += rhs[17][26];
			m_data[17][27] += rhs[17][27];
			m_data[17][28] += rhs[17][28];
			m_data[17][29] += rhs[17][29];
			m_data[17][30] += rhs[17][30];
			m_data[17][31] += rhs[17][31];

			m_data[18][0] += rhs[18][0];
			m_data[18][1] += rhs[18][1];
			m_data[18][2] += rhs[18][2];
			m_data[18][3] += rhs[18][3];
			m_data[18][4] += rhs[18][4];
			m_data[18][5] += rhs[18][5];
			m_data[18][6] += rhs[18][6];
			m_data[18][7] += rhs[18][7];
			m_data[18][8] += rhs[18][8];
			m_data[18][9] += rhs[18][9];
			m_data[18][10] += rhs[18][10];
			m_data[18][11] += rhs[18][11];
			m_data[18][12] += rhs[18][12];
			m_data[18][13] += rhs[18][13];
			m_data[18][14] += rhs[18][14];
			m_data[18][15] += rhs[18][15];
			m_data[18][16] += rhs[18][16];
			m_data[18][17] += rhs[18][17];
			m_data[18][18] += rhs[18][18];
			m_data[18][19] += rhs[18][19];
			m_data[18][20] += rhs[18][20];
			m_data[18][21] += rhs[18][21];
			m_data[18][22] += rhs[18][22];
			m_data[18][23] += rhs[18][23];
			m_data[18][24] += rhs[18][24];
			m_data[18][25] += rhs[18][25];
			m_data[18][26] += rhs[18][26];
			m_data[18][27] += rhs[18][27];
			m_data[18][28] += rhs[18][28];
			m_data[18][29] += rhs[18][29];
			m_data[18][30] += rhs[18][30];
			m_data[18][31] += rhs[18][31];

			m_data[19][0] += rhs[19][0];
			m_data[19][1] += rhs[19][1];
			m_data[19][2] += rhs[19][2];
			m_data[19][3] += rhs[19][3];
			m_data[19][4] += rhs[19][4];
			m_data[19][5] += rhs[19][5];
			m_data[19][6] += rhs[19][6];
			m_data[19][7] += rhs[19][7];
			m_data[19][8] += rhs[19][8];
			m_data[19][9] += rhs[19][9];
			m_data[19][10] += rhs[19][10];
			m_data[19][11] += rhs[19][11];
			m_data[19][12] += rhs[19][12];
			m_data[19][13] += rhs[19][13];
			m_data[19][14] += rhs[19][14];
			m_data[19][15] += rhs[19][15];
			m_data[19][16] += rhs[19][16];
			m_data[19][17] += rhs[19][17];
			m_data[19][18] += rhs[19][18];
			m_data[19][19] += rhs[19][19];
			m_data[19][20] += rhs[19][20];
			m_data[19][21] += rhs[19][21];
			m_data[19][22] += rhs[19][22];
			m_data[19][23] += rhs[19][23];
			m_data[19][24] += rhs[19][24];
			m_data[19][25] += rhs[19][25];
			m_data[19][26] += rhs[19][26];
			m_data[19][27] += rhs[19][27];
			m_data[19][28] += rhs[19][28];
			m_data[19][29] += rhs[19][29];
			m_data[19][30] += rhs[19][30];
			m_data[19][31] += rhs[19][31];

			m_data[20][0] += rhs[20][0];
			m_data[20][1] += rhs[20][1];
			m_data[20][2] += rhs[20][2];
			m_data[20][3] += rhs[20][3];
			m_data[20][4] += rhs[20][4];
			m_data[20][5] += rhs[20][5];
			m_data[20][6] += rhs[20][6];
			m_data[20][7] += rhs[20][7];
			m_data[20][8] += rhs[20][8];
			m_data[20][9] += rhs[20][9];
			m_data[20][10] += rhs[20][10];
			m_data[20][11] += rhs[20][11];
			m_data[20][12] += rhs[20][12];
			m_data[20][13] += rhs[20][13];
			m_data[20][14] += rhs[20][14];
			m_data[20][15] += rhs[20][15];
			m_data[20][16] += rhs[20][16];
			m_data[20][17] += rhs[20][17];
			m_data[20][18] += rhs[20][18];
			m_data[20][19] += rhs[20][19];
			m_data[20][20] += rhs[20][20];
			m_data[20][21] += rhs[20][21];
			m_data[20][22] += rhs[20][22];
			m_data[20][23] += rhs[20][23];
			m_data[20][24] += rhs[20][24];
			m_data[20][25] += rhs[20][25];
			m_data[20][26] += rhs[20][26];
			m_data[20][27] += rhs[20][27];
			m_data[20][28] += rhs[20][28];
			m_data[20][29] += rhs[20][29];
			m_data[20][30] += rhs[20][30];
			m_data[20][31] += rhs[20][31];

			m_data[21][0] += rhs[21][0];
			m_data[21][1] += rhs[21][1];
			m_data[21][2] += rhs[21][2];
			m_data[21][3] += rhs[21][3];
			m_data[21][4] += rhs[21][4];
			m_data[21][5] += rhs[21][5];
			m_data[21][6] += rhs[21][6];
			m_data[21][7] += rhs[21][7];
			m_data[21][8] += rhs[21][8];
			m_data[21][9] += rhs[21][9];
			m_data[21][10] += rhs[21][10];
			m_data[21][11] += rhs[21][11];
			m_data[21][12] += rhs[21][12];
			m_data[21][13] += rhs[21][13];
			m_data[21][14] += rhs[21][14];
			m_data[21][15] += rhs[21][15];
			m_data[21][16] += rhs[21][16];
			m_data[21][17] += rhs[21][17];
			m_data[21][18] += rhs[21][18];
			m_data[21][19] += rhs[21][19];
			m_data[21][20] += rhs[21][20];
			m_data[21][21] += rhs[21][21];
			m_data[21][22] += rhs[21][22];
			m_data[21][23] += rhs[21][23];
			m_data[21][24] += rhs[21][24];
			m_data[21][25] += rhs[21][25];
			m_data[21][26] += rhs[21][26];
			m_data[21][27] += rhs[21][27];
			m_data[21][28] += rhs[21][28];
			m_data[21][29] += rhs[21][29];
			m_data[21][30] += rhs[21][30];
			m_data[21][31] += rhs[21][31];

			m_data[22][0] += rhs[22][0];
			m_data[22][1] += rhs[22][1];
			m_data[22][2] += rhs[22][2];
			m_data[22][3] += rhs[22][3];
			m_data[22][4] += rhs[22][4];
			m_data[22][5] += rhs[22][5];
			m_data[22][6] += rhs[22][6];
			m_data[22][7] += rhs[22][7];
			m_data[22][8] += rhs[22][8];
			m_data[22][9] += rhs[22][9];
			m_data[22][10] += rhs[22][10];
			m_data[22][11] += rhs[22][11];
			m_data[22][12] += rhs[22][12];
			m_data[22][13] += rhs[22][13];
			m_data[22][14] += rhs[22][14];
			m_data[22][15] += rhs[22][15];
			m_data[22][16] += rhs[22][16];
			m_data[22][17] += rhs[22][17];
			m_data[22][18] += rhs[22][18];
			m_data[22][19] += rhs[22][19];
			m_data[22][20] += rhs[22][20];
			m_data[22][21] += rhs[22][21];
			m_data[22][22] += rhs[22][22];
			m_data[22][23] += rhs[22][23];
			m_data[22][24] += rhs[22][24];
			m_data[22][25] += rhs[22][25];
			m_data[22][26] += rhs[22][26];
			m_data[22][27] += rhs[22][27];
			m_data[22][28] += rhs[22][28];
			m_data[22][29] += rhs[22][29];
			m_data[22][30] += rhs[22][30];
			m_data[22][31] += rhs[22][31];

			m_data[23][0] += rhs[23][0];
			m_data[23][1] += rhs[23][1];
			m_data[23][2] += rhs[23][2];
			m_data[23][3] += rhs[23][3];
			m_data[23][4] += rhs[23][4];
			m_data[23][5] += rhs[23][5];
			m_data[23][6] += rhs[23][6];
			m_data[23][7] += rhs[23][7];
			m_data[23][8] += rhs[23][8];
			m_data[23][9] += rhs[23][9];
			m_data[23][10] += rhs[23][10];
			m_data[23][11] += rhs[23][11];
			m_data[23][12] += rhs[23][12];
			m_data[23][13] += rhs[23][13];
			m_data[23][14] += rhs[23][14];
			m_data[23][15] += rhs[23][15];
			m_data[23][16] += rhs[23][16];
			m_data[23][17] += rhs[23][17];
			m_data[23][18] += rhs[23][18];
			m_data[23][19] += rhs[23][19];
			m_data[23][20] += rhs[23][20];
			m_data[23][21] += rhs[23][21];
			m_data[23][22] += rhs[23][22];
			m_data[23][23] += rhs[23][23];
			m_data[23][24] += rhs[23][24];
			m_data[23][25] += rhs[23][25];
			m_data[23][26] += rhs[23][26];
			m_data[23][27] += rhs[23][27];
			m_data[23][28] += rhs[23][28];
			m_data[23][29] += rhs[23][29];
			m_data[23][30] += rhs[23][30];
			m_data[23][31] += rhs[23][31];

			m_data[24][0] += rhs[24][0];
			m_data[24][1] += rhs[24][1];
			m_data[24][2] += rhs[24][2];
			m_data[24][3] += rhs[24][3];
			m_data[24][4] += rhs[24][4];
			m_data[24][5] += rhs[24][5];
			m_data[24][6] += rhs[24][6];
			m_data[24][7] += rhs[24][7];
			m_data[24][8] += rhs[24][8];
			m_data[24][9] += rhs[24][9];
			m_data[24][10] += rhs[24][10];
			m_data[24][11] += rhs[24][11];
			m_data[24][12] += rhs[24][12];
			m_data[24][13] += rhs[24][13];
			m_data[24][14] += rhs[24][14];
			m_data[24][15] += rhs[24][15];
			m_data[24][16] += rhs[24][16];
			m_data[24][17] += rhs[24][17];
			m_data[24][18] += rhs[24][18];
			m_data[24][19] += rhs[24][19];
			m_data[24][20] += rhs[24][20];
			m_data[24][21] += rhs[24][21];
			m_data[24][22] += rhs[24][22];
			m_data[24][23] += rhs[24][23];
			m_data[24][24] += rhs[24][24];
			m_data[24][25] += rhs[24][25];
			m_data[24][26] += rhs[24][26];
			m_data[24][27] += rhs[24][27];
			m_data[24][28] += rhs[24][28];
			m_data[24][29] += rhs[24][29];
			m_data[24][30] += rhs[24][30];
			m_data[24][31] += rhs[24][31];

			m_data[25][0] += rhs[25][0];
			m_data[25][1] += rhs[25][1];
			m_data[25][2] += rhs[25][2];
			m_data[25][3] += rhs[25][3];
			m_data[25][4] += rhs[25][4];
			m_data[25][5] += rhs[25][5];
			m_data[25][6] += rhs[25][6];
			m_data[25][7] += rhs[25][7];
			m_data[25][8] += rhs[25][8];
			m_data[25][9] += rhs[25][9];
			m_data[25][10] += rhs[25][10];
			m_data[25][11] += rhs[25][11];
			m_data[25][12] += rhs[25][12];
			m_data[25][13] += rhs[25][13];
			m_data[25][14] += rhs[25][14];
			m_data[25][15] += rhs[25][15];
			m_data[25][16] += rhs[25][16];
			m_data[25][17] += rhs[25][17];
			m_data[25][18] += rhs[25][18];
			m_data[25][19] += rhs[25][19];
			m_data[25][20] += rhs[25][20];
			m_data[25][21] += rhs[25][21];
			m_data[25][22] += rhs[25][22];
			m_data[25][23] += rhs[25][23];
			m_data[25][24] += rhs[25][24];
			m_data[25][25] += rhs[25][25];
			m_data[25][26] += rhs[25][26];
			m_data[25][27] += rhs[25][27];
			m_data[25][28] += rhs[25][28];
			m_data[25][29] += rhs[25][29];
			m_data[25][30] += rhs[25][30];
			m_data[25][31] += rhs[25][31];

			m_data[26][0] += rhs[26][0];
			m_data[26][1] += rhs[26][1];
			m_data[26][2] += rhs[26][2];
			m_data[26][3] += rhs[26][3];
			m_data[26][4] += rhs[26][4];
			m_data[26][5] += rhs[26][5];
			m_data[26][6] += rhs[26][6];
			m_data[26][7] += rhs[26][7];
			m_data[26][8] += rhs[26][8];
			m_data[26][9] += rhs[26][9];
			m_data[26][10] += rhs[26][10];
			m_data[26][11] += rhs[26][11];
			m_data[26][12] += rhs[26][12];
			m_data[26][13] += rhs[26][13];
			m_data[26][14] += rhs[26][14];
			m_data[26][15] += rhs[26][15];
			m_data[26][16] += rhs[26][16];
			m_data[26][17] += rhs[26][17];
			m_data[26][18] += rhs[26][18];
			m_data[26][19] += rhs[26][19];
			m_data[26][20] += rhs[26][20];
			m_data[26][21] += rhs[26][21];
			m_data[26][22] += rhs[26][22];
			m_data[26][23] += rhs[26][23];
			m_data[26][24] += rhs[26][24];
			m_data[26][25] += rhs[26][25];
			m_data[26][26] += rhs[26][26];
			m_data[26][27] += rhs[26][27];
			m_data[26][28] += rhs[26][28];
			m_data[26][29] += rhs[26][29];
			m_data[26][30] += rhs[26][30];
			m_data[26][31] += rhs[26][31];

			m_data[27][0] += rhs[27][0];
			m_data[27][1] += rhs[27][1];
			m_data[27][2] += rhs[27][2];
			m_data[27][3] += rhs[27][3];
			m_data[27][4] += rhs[27][4];
			m_data[27][5] += rhs[27][5];
			m_data[27][6] += rhs[27][6];
			m_data[27][7] += rhs[27][7];
			m_data[27][8] += rhs[27][8];
			m_data[27][9] += rhs[27][9];
			m_data[27][10] += rhs[27][10];
			m_data[27][11] += rhs[27][11];
			m_data[27][12] += rhs[27][12];
			m_data[27][13] += rhs[27][13];
			m_data[27][14] += rhs[27][14];
			m_data[27][15] += rhs[27][15];
			m_data[27][16] += rhs[27][16];
			m_data[27][17] += rhs[27][17];
			m_data[27][18] += rhs[27][18];
			m_data[27][19] += rhs[27][19];
			m_data[27][20] += rhs[27][20];
			m_data[27][21] += rhs[27][21];
			m_data[27][22] += rhs[27][22];
			m_data[27][23] += rhs[27][23];
			m_data[27][24] += rhs[27][24];
			m_data[27][25] += rhs[27][25];
			m_data[27][26] += rhs[27][26];
			m_data[27][27] += rhs[27][27];
			m_data[27][28] += rhs[27][28];
			m_data[27][29] += rhs[27][29];
			m_data[27][30] += rhs[27][30];
			m_data[27][31] += rhs[27][31];

			m_data[28][0] += rhs[28][0];
			m_data[28][1] += rhs[28][1];
			m_data[28][2] += rhs[28][2];
			m_data[28][3] += rhs[28][3];
			m_data[28][4] += rhs[28][4];
			m_data[28][5] += rhs[28][5];
			m_data[28][6] += rhs[28][6];
			m_data[28][7] += rhs[28][7];
			m_data[28][8] += rhs[28][8];
			m_data[28][9] += rhs[28][9];
			m_data[28][10] += rhs[28][10];
			m_data[28][11] += rhs[28][11];
			m_data[28][12] += rhs[28][12];
			m_data[28][13] += rhs[28][13];
			m_data[28][14] += rhs[28][14];
			m_data[28][15] += rhs[28][15];
			m_data[28][16] += rhs[28][16];
			m_data[28][17] += rhs[28][17];
			m_data[28][18] += rhs[28][18];
			m_data[28][19] += rhs[28][19];
			m_data[28][20] += rhs[28][20];
			m_data[28][21] += rhs[28][21];
			m_data[28][22] += rhs[28][22];
			m_data[28][23] += rhs[28][23];
			m_data[28][24] += rhs[28][24];
			m_data[28][25] += rhs[28][25];
			m_data[28][26] += rhs[28][26];
			m_data[28][27] += rhs[28][27];
			m_data[28][28] += rhs[28][28];
			m_data[28][29] += rhs[28][29];
			m_data[28][30] += rhs[28][30];
			m_data[28][31] += rhs[28][31];

			m_data[29][0] += rhs[29][0];
			m_data[29][1] += rhs[29][1];
			m_data[29][2] += rhs[29][2];
			m_data[29][3] += rhs[29][3];
			m_data[29][4] += rhs[29][4];
			m_data[29][5] += rhs[29][5];
			m_data[29][6] += rhs[29][6];
			m_data[29][7] += rhs[29][7];
			m_data[29][8] += rhs[29][8];
			m_data[29][9] += rhs[29][9];
			m_data[29][10] += rhs[29][10];
			m_data[29][11] += rhs[29][11];
			m_data[29][12] += rhs[29][12];
			m_data[29][13] += rhs[29][13];
			m_data[29][14] += rhs[29][14];
			m_data[29][15] += rhs[29][15];
			m_data[29][16] += rhs[29][16];
			m_data[29][17] += rhs[29][17];
			m_data[29][18] += rhs[29][18];
			m_data[29][19] += rhs[29][19];
			m_data[29][20] += rhs[29][20];
			m_data[29][21] += rhs[29][21];
			m_data[29][22] += rhs[29][22];
			m_data[29][23] += rhs[29][23];
			m_data[29][24] += rhs[29][24];
			m_data[29][25] += rhs[29][25];
			m_data[29][26] += rhs[29][26];
			m_data[29][27] += rhs[29][27];
			m_data[29][28] += rhs[29][28];
			m_data[29][29] += rhs[29][29];
			m_data[29][30] += rhs[29][30];
			m_data[29][31] += rhs[29][31];

			m_data[30][0] += rhs[30][0];
			m_data[30][1] += rhs[30][1];
			m_data[30][2] += rhs[30][2];
			m_data[30][3] += rhs[30][3];
			m_data[30][4] += rhs[30][4];
			m_data[30][5] += rhs[30][5];
			m_data[30][6] += rhs[30][6];
			m_data[30][7] += rhs[30][7];
			m_data[30][8] += rhs[30][8];
			m_data[30][9] += rhs[30][9];
			m_data[30][10] += rhs[30][10];
			m_data[30][11] += rhs[30][11];
			m_data[30][12] += rhs[30][12];
			m_data[30][13] += rhs[30][13];
			m_data[30][14] += rhs[30][14];
			m_data[30][15] += rhs[30][15];
			m_data[30][16] += rhs[30][16];
			m_data[30][17] += rhs[30][17];
			m_data[30][18] += rhs[30][18];
			m_data[30][19] += rhs[30][19];
			m_data[30][20] += rhs[30][20];
			m_data[30][21] += rhs[30][21];
			m_data[30][22] += rhs[30][22];
			m_data[30][23] += rhs[30][23];
			m_data[30][24] += rhs[30][24];
			m_data[30][25] += rhs[30][25];
			m_data[30][26] += rhs[30][26];
			m_data[30][27] += rhs[30][27];
			m_data[30][28] += rhs[30][28];
			m_data[30][29] += rhs[30][29];
			m_data[30][30] += rhs[30][30];
			m_data[30][31] += rhs[30][31];

			m_data[31][0] += rhs[31][0];
			m_data[31][1] += rhs[31][1];
			m_data[31][2] += rhs[31][2];
			m_data[31][3] += rhs[31][3];
			m_data[31][4] += rhs[31][4];
			m_data[31][5] += rhs[31][5];
			m_data[31][6] += rhs[31][6];
			m_data[31][7] += rhs[31][7];
			m_data[31][8] += rhs[31][8];
			m_data[31][9] += rhs[31][9];
			m_data[31][10] += rhs[31][10];
			m_data[31][11] += rhs[31][11];
			m_data[31][12] += rhs[31][12];
			m_data[31][13] += rhs[31][13];
			m_data[31][14] += rhs[31][14];
			m_data[31][15] += rhs[31][15];
			m_data[31][16] += rhs[31][16];
			m_data[31][17] += rhs[31][17];
			m_data[31][18] += rhs[31][18];
			m_data[31][19] += rhs[31][19];
			m_data[31][20] += rhs[31][20];
			m_data[31][21] += rhs[31][21];
			m_data[31][22] += rhs[31][22];
			m_data[31][23] += rhs[31][23];
			m_data[31][24] += rhs[31][24];
			m_data[31][25] += rhs[31][25];
			m_data[31][26] += rhs[31][26];
			m_data[31][27] += rhs[31][27];
			m_data[31][28] += rhs[31][28];
			m_data[31][29] += rhs[31][29];
			m_data[31][30] += rhs[31][30];
			m_data[31][31] += rhs[31][31];

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
		Mat32x32& operator-=(const Mat32x32& rhs)
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
			m_data[0][16] -= rhs[0][16];
			m_data[0][17] -= rhs[0][17];
			m_data[0][18] -= rhs[0][18];
			m_data[0][19] -= rhs[0][19];
			m_data[0][20] -= rhs[0][20];
			m_data[0][21] -= rhs[0][21];
			m_data[0][22] -= rhs[0][22];
			m_data[0][23] -= rhs[0][23];
			m_data[0][24] -= rhs[0][24];
			m_data[0][25] -= rhs[0][25];
			m_data[0][26] -= rhs[0][26];
			m_data[0][27] -= rhs[0][27];
			m_data[0][28] -= rhs[0][28];
			m_data[0][29] -= rhs[0][29];
			m_data[0][30] -= rhs[0][30];
			m_data[0][31] -= rhs[0][31];

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
			m_data[1][16] -= rhs[1][16];
			m_data[1][17] -= rhs[1][17];
			m_data[1][18] -= rhs[1][18];
			m_data[1][19] -= rhs[1][19];
			m_data[1][20] -= rhs[1][20];
			m_data[1][21] -= rhs[1][21];
			m_data[1][22] -= rhs[1][22];
			m_data[1][23] -= rhs[1][23];
			m_data[1][24] -= rhs[1][24];
			m_data[1][25] -= rhs[1][25];
			m_data[1][26] -= rhs[1][26];
			m_data[1][27] -= rhs[1][27];
			m_data[1][28] -= rhs[1][28];
			m_data[1][29] -= rhs[1][29];
			m_data[1][30] -= rhs[1][30];
			m_data[1][31] -= rhs[1][31];

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
			m_data[2][16] -= rhs[2][16];
			m_data[2][17] -= rhs[2][17];
			m_data[2][18] -= rhs[2][18];
			m_data[2][19] -= rhs[2][19];
			m_data[2][20] -= rhs[2][20];
			m_data[2][21] -= rhs[2][21];
			m_data[2][22] -= rhs[2][22];
			m_data[2][23] -= rhs[2][23];
			m_data[2][24] -= rhs[2][24];
			m_data[2][25] -= rhs[2][25];
			m_data[2][26] -= rhs[2][26];
			m_data[2][27] -= rhs[2][27];
			m_data[2][28] -= rhs[2][28];
			m_data[2][29] -= rhs[2][29];
			m_data[2][30] -= rhs[2][30];
			m_data[2][31] -= rhs[2][31];

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
			m_data[3][16] -= rhs[3][16];
			m_data[3][17] -= rhs[3][17];
			m_data[3][18] -= rhs[3][18];
			m_data[3][19] -= rhs[3][19];
			m_data[3][20] -= rhs[3][20];
			m_data[3][21] -= rhs[3][21];
			m_data[3][22] -= rhs[3][22];
			m_data[3][23] -= rhs[3][23];
			m_data[3][24] -= rhs[3][24];
			m_data[3][25] -= rhs[3][25];
			m_data[3][26] -= rhs[3][26];
			m_data[3][27] -= rhs[3][27];
			m_data[3][28] -= rhs[3][28];
			m_data[3][29] -= rhs[3][29];
			m_data[3][30] -= rhs[3][30];
			m_data[3][31] -= rhs[3][31];

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
			m_data[4][16] -= rhs[4][16];
			m_data[4][17] -= rhs[4][17];
			m_data[4][18] -= rhs[4][18];
			m_data[4][19] -= rhs[4][19];
			m_data[4][20] -= rhs[4][20];
			m_data[4][21] -= rhs[4][21];
			m_data[4][22] -= rhs[4][22];
			m_data[4][23] -= rhs[4][23];
			m_data[4][24] -= rhs[4][24];
			m_data[4][25] -= rhs[4][25];
			m_data[4][26] -= rhs[4][26];
			m_data[4][27] -= rhs[4][27];
			m_data[4][28] -= rhs[4][28];
			m_data[4][29] -= rhs[4][29];
			m_data[4][30] -= rhs[4][30];
			m_data[4][31] -= rhs[4][31];

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
			m_data[5][16] -= rhs[5][16];
			m_data[5][17] -= rhs[5][17];
			m_data[5][18] -= rhs[5][18];
			m_data[5][19] -= rhs[5][19];
			m_data[5][20] -= rhs[5][20];
			m_data[5][21] -= rhs[5][21];
			m_data[5][22] -= rhs[5][22];
			m_data[5][23] -= rhs[5][23];
			m_data[5][24] -= rhs[5][24];
			m_data[5][25] -= rhs[5][25];
			m_data[5][26] -= rhs[5][26];
			m_data[5][27] -= rhs[5][27];
			m_data[5][28] -= rhs[5][28];
			m_data[5][29] -= rhs[5][29];
			m_data[5][30] -= rhs[5][30];
			m_data[5][31] -= rhs[5][31];

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
			m_data[6][16] -= rhs[6][16];
			m_data[6][17] -= rhs[6][17];
			m_data[6][18] -= rhs[6][18];
			m_data[6][19] -= rhs[6][19];
			m_data[6][20] -= rhs[6][20];
			m_data[6][21] -= rhs[6][21];
			m_data[6][22] -= rhs[6][22];
			m_data[6][23] -= rhs[6][23];
			m_data[6][24] -= rhs[6][24];
			m_data[6][25] -= rhs[6][25];
			m_data[6][26] -= rhs[6][26];
			m_data[6][27] -= rhs[6][27];
			m_data[6][28] -= rhs[6][28];
			m_data[6][29] -= rhs[6][29];
			m_data[6][30] -= rhs[6][30];
			m_data[6][31] -= rhs[6][31];

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
			m_data[7][16] -= rhs[7][16];
			m_data[7][17] -= rhs[7][17];
			m_data[7][18] -= rhs[7][18];
			m_data[7][19] -= rhs[7][19];
			m_data[7][20] -= rhs[7][20];
			m_data[7][21] -= rhs[7][21];
			m_data[7][22] -= rhs[7][22];
			m_data[7][23] -= rhs[7][23];
			m_data[7][24] -= rhs[7][24];
			m_data[7][25] -= rhs[7][25];
			m_data[7][26] -= rhs[7][26];
			m_data[7][27] -= rhs[7][27];
			m_data[7][28] -= rhs[7][28];
			m_data[7][29] -= rhs[7][29];
			m_data[7][30] -= rhs[7][30];
			m_data[7][31] -= rhs[7][31];

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
			m_data[8][16] -= rhs[8][16];
			m_data[8][17] -= rhs[8][17];
			m_data[8][18] -= rhs[8][18];
			m_data[8][19] -= rhs[8][19];
			m_data[8][20] -= rhs[8][20];
			m_data[8][21] -= rhs[8][21];
			m_data[8][22] -= rhs[8][22];
			m_data[8][23] -= rhs[8][23];
			m_data[8][24] -= rhs[8][24];
			m_data[8][25] -= rhs[8][25];
			m_data[8][26] -= rhs[8][26];
			m_data[8][27] -= rhs[8][27];
			m_data[8][28] -= rhs[8][28];
			m_data[8][29] -= rhs[8][29];
			m_data[8][30] -= rhs[8][30];
			m_data[8][31] -= rhs[8][31];

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
			m_data[9][16] -= rhs[9][16];
			m_data[9][17] -= rhs[9][17];
			m_data[9][18] -= rhs[9][18];
			m_data[9][19] -= rhs[9][19];
			m_data[9][20] -= rhs[9][20];
			m_data[9][21] -= rhs[9][21];
			m_data[9][22] -= rhs[9][22];
			m_data[9][23] -= rhs[9][23];
			m_data[9][24] -= rhs[9][24];
			m_data[9][25] -= rhs[9][25];
			m_data[9][26] -= rhs[9][26];
			m_data[9][27] -= rhs[9][27];
			m_data[9][28] -= rhs[9][28];
			m_data[9][29] -= rhs[9][29];
			m_data[9][30] -= rhs[9][30];
			m_data[9][31] -= rhs[9][31];

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
			m_data[10][16] -= rhs[10][16];
			m_data[10][17] -= rhs[10][17];
			m_data[10][18] -= rhs[10][18];
			m_data[10][19] -= rhs[10][19];
			m_data[10][20] -= rhs[10][20];
			m_data[10][21] -= rhs[10][21];
			m_data[10][22] -= rhs[10][22];
			m_data[10][23] -= rhs[10][23];
			m_data[10][24] -= rhs[10][24];
			m_data[10][25] -= rhs[10][25];
			m_data[10][26] -= rhs[10][26];
			m_data[10][27] -= rhs[10][27];
			m_data[10][28] -= rhs[10][28];
			m_data[10][29] -= rhs[10][29];
			m_data[10][30] -= rhs[10][30];
			m_data[10][31] -= rhs[10][31];

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
			m_data[11][16] -= rhs[11][16];
			m_data[11][17] -= rhs[11][17];
			m_data[11][18] -= rhs[11][18];
			m_data[11][19] -= rhs[11][19];
			m_data[11][20] -= rhs[11][20];
			m_data[11][21] -= rhs[11][21];
			m_data[11][22] -= rhs[11][22];
			m_data[11][23] -= rhs[11][23];
			m_data[11][24] -= rhs[11][24];
			m_data[11][25] -= rhs[11][25];
			m_data[11][26] -= rhs[11][26];
			m_data[11][27] -= rhs[11][27];
			m_data[11][28] -= rhs[11][28];
			m_data[11][29] -= rhs[11][29];
			m_data[11][30] -= rhs[11][30];
			m_data[11][31] -= rhs[11][31];

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
			m_data[12][16] -= rhs[12][16];
			m_data[12][17] -= rhs[12][17];
			m_data[12][18] -= rhs[12][18];
			m_data[12][19] -= rhs[12][19];
			m_data[12][20] -= rhs[12][20];
			m_data[12][21] -= rhs[12][21];
			m_data[12][22] -= rhs[12][22];
			m_data[12][23] -= rhs[12][23];
			m_data[12][24] -= rhs[12][24];
			m_data[12][25] -= rhs[12][25];
			m_data[12][26] -= rhs[12][26];
			m_data[12][27] -= rhs[12][27];
			m_data[12][28] -= rhs[12][28];
			m_data[12][29] -= rhs[12][29];
			m_data[12][30] -= rhs[12][30];
			m_data[12][31] -= rhs[12][31];

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
			m_data[13][16] -= rhs[13][16];
			m_data[13][17] -= rhs[13][17];
			m_data[13][18] -= rhs[13][18];
			m_data[13][19] -= rhs[13][19];
			m_data[13][20] -= rhs[13][20];
			m_data[13][21] -= rhs[13][21];
			m_data[13][22] -= rhs[13][22];
			m_data[13][23] -= rhs[13][23];
			m_data[13][24] -= rhs[13][24];
			m_data[13][25] -= rhs[13][25];
			m_data[13][26] -= rhs[13][26];
			m_data[13][27] -= rhs[13][27];
			m_data[13][28] -= rhs[13][28];
			m_data[13][29] -= rhs[13][29];
			m_data[13][30] -= rhs[13][30];
			m_data[13][31] -= rhs[13][31];

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
			m_data[14][16] -= rhs[14][16];
			m_data[14][17] -= rhs[14][17];
			m_data[14][18] -= rhs[14][18];
			m_data[14][19] -= rhs[14][19];
			m_data[14][20] -= rhs[14][20];
			m_data[14][21] -= rhs[14][21];
			m_data[14][22] -= rhs[14][22];
			m_data[14][23] -= rhs[14][23];
			m_data[14][24] -= rhs[14][24];
			m_data[14][25] -= rhs[14][25];
			m_data[14][26] -= rhs[14][26];
			m_data[14][27] -= rhs[14][27];
			m_data[14][28] -= rhs[14][28];
			m_data[14][29] -= rhs[14][29];
			m_data[14][30] -= rhs[14][30];
			m_data[14][31] -= rhs[14][31];

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
			m_data[15][16] -= rhs[15][16];
			m_data[15][17] -= rhs[15][17];
			m_data[15][18] -= rhs[15][18];
			m_data[15][19] -= rhs[15][19];
			m_data[15][20] -= rhs[15][20];
			m_data[15][21] -= rhs[15][21];
			m_data[15][22] -= rhs[15][22];
			m_data[15][23] -= rhs[15][23];
			m_data[15][24] -= rhs[15][24];
			m_data[15][25] -= rhs[15][25];
			m_data[15][26] -= rhs[15][26];
			m_data[15][27] -= rhs[15][27];
			m_data[15][28] -= rhs[15][28];
			m_data[15][29] -= rhs[15][29];
			m_data[15][30] -= rhs[15][30];
			m_data[15][31] -= rhs[15][31];

			m_data[16][0] -= rhs[16][0];
			m_data[16][1] -= rhs[16][1];
			m_data[16][2] -= rhs[16][2];
			m_data[16][3] -= rhs[16][3];
			m_data[16][4] -= rhs[16][4];
			m_data[16][5] -= rhs[16][5];
			m_data[16][6] -= rhs[16][6];
			m_data[16][7] -= rhs[16][7];
			m_data[16][8] -= rhs[16][8];
			m_data[16][9] -= rhs[16][9];
			m_data[16][10] -= rhs[16][10];
			m_data[16][11] -= rhs[16][11];
			m_data[16][12] -= rhs[16][12];
			m_data[16][13] -= rhs[16][13];
			m_data[16][14] -= rhs[16][14];
			m_data[16][15] -= rhs[16][15];
			m_data[16][16] -= rhs[16][16];
			m_data[16][17] -= rhs[16][17];
			m_data[16][18] -= rhs[16][18];
			m_data[16][19] -= rhs[16][19];
			m_data[16][20] -= rhs[16][20];
			m_data[16][21] -= rhs[16][21];
			m_data[16][22] -= rhs[16][22];
			m_data[16][23] -= rhs[16][23];
			m_data[16][24] -= rhs[16][24];
			m_data[16][25] -= rhs[16][25];
			m_data[16][26] -= rhs[16][26];
			m_data[16][27] -= rhs[16][27];
			m_data[16][28] -= rhs[16][28];
			m_data[16][29] -= rhs[16][29];
			m_data[16][30] -= rhs[16][30];
			m_data[16][31] -= rhs[16][31];

			m_data[17][0] -= rhs[17][0];
			m_data[17][1] -= rhs[17][1];
			m_data[17][2] -= rhs[17][2];
			m_data[17][3] -= rhs[17][3];
			m_data[17][4] -= rhs[17][4];
			m_data[17][5] -= rhs[17][5];
			m_data[17][6] -= rhs[17][6];
			m_data[17][7] -= rhs[17][7];
			m_data[17][8] -= rhs[17][8];
			m_data[17][9] -= rhs[17][9];
			m_data[17][10] -= rhs[17][10];
			m_data[17][11] -= rhs[17][11];
			m_data[17][12] -= rhs[17][12];
			m_data[17][13] -= rhs[17][13];
			m_data[17][14] -= rhs[17][14];
			m_data[17][15] -= rhs[17][15];
			m_data[17][16] -= rhs[17][16];
			m_data[17][17] -= rhs[17][17];
			m_data[17][18] -= rhs[17][18];
			m_data[17][19] -= rhs[17][19];
			m_data[17][20] -= rhs[17][20];
			m_data[17][21] -= rhs[17][21];
			m_data[17][22] -= rhs[17][22];
			m_data[17][23] -= rhs[17][23];
			m_data[17][24] -= rhs[17][24];
			m_data[17][25] -= rhs[17][25];
			m_data[17][26] -= rhs[17][26];
			m_data[17][27] -= rhs[17][27];
			m_data[17][28] -= rhs[17][28];
			m_data[17][29] -= rhs[17][29];
			m_data[17][30] -= rhs[17][30];
			m_data[17][31] -= rhs[17][31];

			m_data[18][0] -= rhs[18][0];
			m_data[18][1] -= rhs[18][1];
			m_data[18][2] -= rhs[18][2];
			m_data[18][3] -= rhs[18][3];
			m_data[18][4] -= rhs[18][4];
			m_data[18][5] -= rhs[18][5];
			m_data[18][6] -= rhs[18][6];
			m_data[18][7] -= rhs[18][7];
			m_data[18][8] -= rhs[18][8];
			m_data[18][9] -= rhs[18][9];
			m_data[18][10] -= rhs[18][10];
			m_data[18][11] -= rhs[18][11];
			m_data[18][12] -= rhs[18][12];
			m_data[18][13] -= rhs[18][13];
			m_data[18][14] -= rhs[18][14];
			m_data[18][15] -= rhs[18][15];
			m_data[18][16] -= rhs[18][16];
			m_data[18][17] -= rhs[18][17];
			m_data[18][18] -= rhs[18][18];
			m_data[18][19] -= rhs[18][19];
			m_data[18][20] -= rhs[18][20];
			m_data[18][21] -= rhs[18][21];
			m_data[18][22] -= rhs[18][22];
			m_data[18][23] -= rhs[18][23];
			m_data[18][24] -= rhs[18][24];
			m_data[18][25] -= rhs[18][25];
			m_data[18][26] -= rhs[18][26];
			m_data[18][27] -= rhs[18][27];
			m_data[18][28] -= rhs[18][28];
			m_data[18][29] -= rhs[18][29];
			m_data[18][30] -= rhs[18][30];
			m_data[18][31] -= rhs[18][31];

			m_data[19][0] -= rhs[19][0];
			m_data[19][1] -= rhs[19][1];
			m_data[19][2] -= rhs[19][2];
			m_data[19][3] -= rhs[19][3];
			m_data[19][4] -= rhs[19][4];
			m_data[19][5] -= rhs[19][5];
			m_data[19][6] -= rhs[19][6];
			m_data[19][7] -= rhs[19][7];
			m_data[19][8] -= rhs[19][8];
			m_data[19][9] -= rhs[19][9];
			m_data[19][10] -= rhs[19][10];
			m_data[19][11] -= rhs[19][11];
			m_data[19][12] -= rhs[19][12];
			m_data[19][13] -= rhs[19][13];
			m_data[19][14] -= rhs[19][14];
			m_data[19][15] -= rhs[19][15];
			m_data[19][16] -= rhs[19][16];
			m_data[19][17] -= rhs[19][17];
			m_data[19][18] -= rhs[19][18];
			m_data[19][19] -= rhs[19][19];
			m_data[19][20] -= rhs[19][20];
			m_data[19][21] -= rhs[19][21];
			m_data[19][22] -= rhs[19][22];
			m_data[19][23] -= rhs[19][23];
			m_data[19][24] -= rhs[19][24];
			m_data[19][25] -= rhs[19][25];
			m_data[19][26] -= rhs[19][26];
			m_data[19][27] -= rhs[19][27];
			m_data[19][28] -= rhs[19][28];
			m_data[19][29] -= rhs[19][29];
			m_data[19][30] -= rhs[19][30];
			m_data[19][31] -= rhs[19][31];

			m_data[20][0] -= rhs[20][0];
			m_data[20][1] -= rhs[20][1];
			m_data[20][2] -= rhs[20][2];
			m_data[20][3] -= rhs[20][3];
			m_data[20][4] -= rhs[20][4];
			m_data[20][5] -= rhs[20][5];
			m_data[20][6] -= rhs[20][6];
			m_data[20][7] -= rhs[20][7];
			m_data[20][8] -= rhs[20][8];
			m_data[20][9] -= rhs[20][9];
			m_data[20][10] -= rhs[20][10];
			m_data[20][11] -= rhs[20][11];
			m_data[20][12] -= rhs[20][12];
			m_data[20][13] -= rhs[20][13];
			m_data[20][14] -= rhs[20][14];
			m_data[20][15] -= rhs[20][15];
			m_data[20][16] -= rhs[20][16];
			m_data[20][17] -= rhs[20][17];
			m_data[20][18] -= rhs[20][18];
			m_data[20][19] -= rhs[20][19];
			m_data[20][20] -= rhs[20][20];
			m_data[20][21] -= rhs[20][21];
			m_data[20][22] -= rhs[20][22];
			m_data[20][23] -= rhs[20][23];
			m_data[20][24] -= rhs[20][24];
			m_data[20][25] -= rhs[20][25];
			m_data[20][26] -= rhs[20][26];
			m_data[20][27] -= rhs[20][27];
			m_data[20][28] -= rhs[20][28];
			m_data[20][29] -= rhs[20][29];
			m_data[20][30] -= rhs[20][30];
			m_data[20][31] -= rhs[20][31];

			m_data[21][0] -= rhs[21][0];
			m_data[21][1] -= rhs[21][1];
			m_data[21][2] -= rhs[21][2];
			m_data[21][3] -= rhs[21][3];
			m_data[21][4] -= rhs[21][4];
			m_data[21][5] -= rhs[21][5];
			m_data[21][6] -= rhs[21][6];
			m_data[21][7] -= rhs[21][7];
			m_data[21][8] -= rhs[21][8];
			m_data[21][9] -= rhs[21][9];
			m_data[21][10] -= rhs[21][10];
			m_data[21][11] -= rhs[21][11];
			m_data[21][12] -= rhs[21][12];
			m_data[21][13] -= rhs[21][13];
			m_data[21][14] -= rhs[21][14];
			m_data[21][15] -= rhs[21][15];
			m_data[21][16] -= rhs[21][16];
			m_data[21][17] -= rhs[21][17];
			m_data[21][18] -= rhs[21][18];
			m_data[21][19] -= rhs[21][19];
			m_data[21][20] -= rhs[21][20];
			m_data[21][21] -= rhs[21][21];
			m_data[21][22] -= rhs[21][22];
			m_data[21][23] -= rhs[21][23];
			m_data[21][24] -= rhs[21][24];
			m_data[21][25] -= rhs[21][25];
			m_data[21][26] -= rhs[21][26];
			m_data[21][27] -= rhs[21][27];
			m_data[21][28] -= rhs[21][28];
			m_data[21][29] -= rhs[21][29];
			m_data[21][30] -= rhs[21][30];
			m_data[21][31] -= rhs[21][31];

			m_data[22][0] -= rhs[22][0];
			m_data[22][1] -= rhs[22][1];
			m_data[22][2] -= rhs[22][2];
			m_data[22][3] -= rhs[22][3];
			m_data[22][4] -= rhs[22][4];
			m_data[22][5] -= rhs[22][5];
			m_data[22][6] -= rhs[22][6];
			m_data[22][7] -= rhs[22][7];
			m_data[22][8] -= rhs[22][8];
			m_data[22][9] -= rhs[22][9];
			m_data[22][10] -= rhs[22][10];
			m_data[22][11] -= rhs[22][11];
			m_data[22][12] -= rhs[22][12];
			m_data[22][13] -= rhs[22][13];
			m_data[22][14] -= rhs[22][14];
			m_data[22][15] -= rhs[22][15];
			m_data[22][16] -= rhs[22][16];
			m_data[22][17] -= rhs[22][17];
			m_data[22][18] -= rhs[22][18];
			m_data[22][19] -= rhs[22][19];
			m_data[22][20] -= rhs[22][20];
			m_data[22][21] -= rhs[22][21];
			m_data[22][22] -= rhs[22][22];
			m_data[22][23] -= rhs[22][23];
			m_data[22][24] -= rhs[22][24];
			m_data[22][25] -= rhs[22][25];
			m_data[22][26] -= rhs[22][26];
			m_data[22][27] -= rhs[22][27];
			m_data[22][28] -= rhs[22][28];
			m_data[22][29] -= rhs[22][29];
			m_data[22][30] -= rhs[22][30];
			m_data[22][31] -= rhs[22][31];

			m_data[23][0] -= rhs[23][0];
			m_data[23][1] -= rhs[23][1];
			m_data[23][2] -= rhs[23][2];
			m_data[23][3] -= rhs[23][3];
			m_data[23][4] -= rhs[23][4];
			m_data[23][5] -= rhs[23][5];
			m_data[23][6] -= rhs[23][6];
			m_data[23][7] -= rhs[23][7];
			m_data[23][8] -= rhs[23][8];
			m_data[23][9] -= rhs[23][9];
			m_data[23][10] -= rhs[23][10];
			m_data[23][11] -= rhs[23][11];
			m_data[23][12] -= rhs[23][12];
			m_data[23][13] -= rhs[23][13];
			m_data[23][14] -= rhs[23][14];
			m_data[23][15] -= rhs[23][15];
			m_data[23][16] -= rhs[23][16];
			m_data[23][17] -= rhs[23][17];
			m_data[23][18] -= rhs[23][18];
			m_data[23][19] -= rhs[23][19];
			m_data[23][20] -= rhs[23][20];
			m_data[23][21] -= rhs[23][21];
			m_data[23][22] -= rhs[23][22];
			m_data[23][23] -= rhs[23][23];
			m_data[23][24] -= rhs[23][24];
			m_data[23][25] -= rhs[23][25];
			m_data[23][26] -= rhs[23][26];
			m_data[23][27] -= rhs[23][27];
			m_data[23][28] -= rhs[23][28];
			m_data[23][29] -= rhs[23][29];
			m_data[23][30] -= rhs[23][30];
			m_data[23][31] -= rhs[23][31];

			m_data[24][0] -= rhs[24][0];
			m_data[24][1] -= rhs[24][1];
			m_data[24][2] -= rhs[24][2];
			m_data[24][3] -= rhs[24][3];
			m_data[24][4] -= rhs[24][4];
			m_data[24][5] -= rhs[24][5];
			m_data[24][6] -= rhs[24][6];
			m_data[24][7] -= rhs[24][7];
			m_data[24][8] -= rhs[24][8];
			m_data[24][9] -= rhs[24][9];
			m_data[24][10] -= rhs[24][10];
			m_data[24][11] -= rhs[24][11];
			m_data[24][12] -= rhs[24][12];
			m_data[24][13] -= rhs[24][13];
			m_data[24][14] -= rhs[24][14];
			m_data[24][15] -= rhs[24][15];
			m_data[24][16] -= rhs[24][16];
			m_data[24][17] -= rhs[24][17];
			m_data[24][18] -= rhs[24][18];
			m_data[24][19] -= rhs[24][19];
			m_data[24][20] -= rhs[24][20];
			m_data[24][21] -= rhs[24][21];
			m_data[24][22] -= rhs[24][22];
			m_data[24][23] -= rhs[24][23];
			m_data[24][24] -= rhs[24][24];
			m_data[24][25] -= rhs[24][25];
			m_data[24][26] -= rhs[24][26];
			m_data[24][27] -= rhs[24][27];
			m_data[24][28] -= rhs[24][28];
			m_data[24][29] -= rhs[24][29];
			m_data[24][30] -= rhs[24][30];
			m_data[24][31] -= rhs[24][31];

			m_data[25][0] -= rhs[25][0];
			m_data[25][1] -= rhs[25][1];
			m_data[25][2] -= rhs[25][2];
			m_data[25][3] -= rhs[25][3];
			m_data[25][4] -= rhs[25][4];
			m_data[25][5] -= rhs[25][5];
			m_data[25][6] -= rhs[25][6];
			m_data[25][7] -= rhs[25][7];
			m_data[25][8] -= rhs[25][8];
			m_data[25][9] -= rhs[25][9];
			m_data[25][10] -= rhs[25][10];
			m_data[25][11] -= rhs[25][11];
			m_data[25][12] -= rhs[25][12];
			m_data[25][13] -= rhs[25][13];
			m_data[25][14] -= rhs[25][14];
			m_data[25][15] -= rhs[25][15];
			m_data[25][16] -= rhs[25][16];
			m_data[25][17] -= rhs[25][17];
			m_data[25][18] -= rhs[25][18];
			m_data[25][19] -= rhs[25][19];
			m_data[25][20] -= rhs[25][20];
			m_data[25][21] -= rhs[25][21];
			m_data[25][22] -= rhs[25][22];
			m_data[25][23] -= rhs[25][23];
			m_data[25][24] -= rhs[25][24];
			m_data[25][25] -= rhs[25][25];
			m_data[25][26] -= rhs[25][26];
			m_data[25][27] -= rhs[25][27];
			m_data[25][28] -= rhs[25][28];
			m_data[25][29] -= rhs[25][29];
			m_data[25][30] -= rhs[25][30];
			m_data[25][31] -= rhs[25][31];

			m_data[26][0] -= rhs[26][0];
			m_data[26][1] -= rhs[26][1];
			m_data[26][2] -= rhs[26][2];
			m_data[26][3] -= rhs[26][3];
			m_data[26][4] -= rhs[26][4];
			m_data[26][5] -= rhs[26][5];
			m_data[26][6] -= rhs[26][6];
			m_data[26][7] -= rhs[26][7];
			m_data[26][8] -= rhs[26][8];
			m_data[26][9] -= rhs[26][9];
			m_data[26][10] -= rhs[26][10];
			m_data[26][11] -= rhs[26][11];
			m_data[26][12] -= rhs[26][12];
			m_data[26][13] -= rhs[26][13];
			m_data[26][14] -= rhs[26][14];
			m_data[26][15] -= rhs[26][15];
			m_data[26][16] -= rhs[26][16];
			m_data[26][17] -= rhs[26][17];
			m_data[26][18] -= rhs[26][18];
			m_data[26][19] -= rhs[26][19];
			m_data[26][20] -= rhs[26][20];
			m_data[26][21] -= rhs[26][21];
			m_data[26][22] -= rhs[26][22];
			m_data[26][23] -= rhs[26][23];
			m_data[26][24] -= rhs[26][24];
			m_data[26][25] -= rhs[26][25];
			m_data[26][26] -= rhs[26][26];
			m_data[26][27] -= rhs[26][27];
			m_data[26][28] -= rhs[26][28];
			m_data[26][29] -= rhs[26][29];
			m_data[26][30] -= rhs[26][30];
			m_data[26][31] -= rhs[26][31];

			m_data[27][0] -= rhs[27][0];
			m_data[27][1] -= rhs[27][1];
			m_data[27][2] -= rhs[27][2];
			m_data[27][3] -= rhs[27][3];
			m_data[27][4] -= rhs[27][4];
			m_data[27][5] -= rhs[27][5];
			m_data[27][6] -= rhs[27][6];
			m_data[27][7] -= rhs[27][7];
			m_data[27][8] -= rhs[27][8];
			m_data[27][9] -= rhs[27][9];
			m_data[27][10] -= rhs[27][10];
			m_data[27][11] -= rhs[27][11];
			m_data[27][12] -= rhs[27][12];
			m_data[27][13] -= rhs[27][13];
			m_data[27][14] -= rhs[27][14];
			m_data[27][15] -= rhs[27][15];
			m_data[27][16] -= rhs[27][16];
			m_data[27][17] -= rhs[27][17];
			m_data[27][18] -= rhs[27][18];
			m_data[27][19] -= rhs[27][19];
			m_data[27][20] -= rhs[27][20];
			m_data[27][21] -= rhs[27][21];
			m_data[27][22] -= rhs[27][22];
			m_data[27][23] -= rhs[27][23];
			m_data[27][24] -= rhs[27][24];
			m_data[27][25] -= rhs[27][25];
			m_data[27][26] -= rhs[27][26];
			m_data[27][27] -= rhs[27][27];
			m_data[27][28] -= rhs[27][28];
			m_data[27][29] -= rhs[27][29];
			m_data[27][30] -= rhs[27][30];
			m_data[27][31] -= rhs[27][31];

			m_data[28][0] -= rhs[28][0];
			m_data[28][1] -= rhs[28][1];
			m_data[28][2] -= rhs[28][2];
			m_data[28][3] -= rhs[28][3];
			m_data[28][4] -= rhs[28][4];
			m_data[28][5] -= rhs[28][5];
			m_data[28][6] -= rhs[28][6];
			m_data[28][7] -= rhs[28][7];
			m_data[28][8] -= rhs[28][8];
			m_data[28][9] -= rhs[28][9];
			m_data[28][10] -= rhs[28][10];
			m_data[28][11] -= rhs[28][11];
			m_data[28][12] -= rhs[28][12];
			m_data[28][13] -= rhs[28][13];
			m_data[28][14] -= rhs[28][14];
			m_data[28][15] -= rhs[28][15];
			m_data[28][16] -= rhs[28][16];
			m_data[28][17] -= rhs[28][17];
			m_data[28][18] -= rhs[28][18];
			m_data[28][19] -= rhs[28][19];
			m_data[28][20] -= rhs[28][20];
			m_data[28][21] -= rhs[28][21];
			m_data[28][22] -= rhs[28][22];
			m_data[28][23] -= rhs[28][23];
			m_data[28][24] -= rhs[28][24];
			m_data[28][25] -= rhs[28][25];
			m_data[28][26] -= rhs[28][26];
			m_data[28][27] -= rhs[28][27];
			m_data[28][28] -= rhs[28][28];
			m_data[28][29] -= rhs[28][29];
			m_data[28][30] -= rhs[28][30];
			m_data[28][31] -= rhs[28][31];

			m_data[29][0] -= rhs[29][0];
			m_data[29][1] -= rhs[29][1];
			m_data[29][2] -= rhs[29][2];
			m_data[29][3] -= rhs[29][3];
			m_data[29][4] -= rhs[29][4];
			m_data[29][5] -= rhs[29][5];
			m_data[29][6] -= rhs[29][6];
			m_data[29][7] -= rhs[29][7];
			m_data[29][8] -= rhs[29][8];
			m_data[29][9] -= rhs[29][9];
			m_data[29][10] -= rhs[29][10];
			m_data[29][11] -= rhs[29][11];
			m_data[29][12] -= rhs[29][12];
			m_data[29][13] -= rhs[29][13];
			m_data[29][14] -= rhs[29][14];
			m_data[29][15] -= rhs[29][15];
			m_data[29][16] -= rhs[29][16];
			m_data[29][17] -= rhs[29][17];
			m_data[29][18] -= rhs[29][18];
			m_data[29][19] -= rhs[29][19];
			m_data[29][20] -= rhs[29][20];
			m_data[29][21] -= rhs[29][21];
			m_data[29][22] -= rhs[29][22];
			m_data[29][23] -= rhs[29][23];
			m_data[29][24] -= rhs[29][24];
			m_data[29][25] -= rhs[29][25];
			m_data[29][26] -= rhs[29][26];
			m_data[29][27] -= rhs[29][27];
			m_data[29][28] -= rhs[29][28];
			m_data[29][29] -= rhs[29][29];
			m_data[29][30] -= rhs[29][30];
			m_data[29][31] -= rhs[29][31];

			m_data[30][0] -= rhs[30][0];
			m_data[30][1] -= rhs[30][1];
			m_data[30][2] -= rhs[30][2];
			m_data[30][3] -= rhs[30][3];
			m_data[30][4] -= rhs[30][4];
			m_data[30][5] -= rhs[30][5];
			m_data[30][6] -= rhs[30][6];
			m_data[30][7] -= rhs[30][7];
			m_data[30][8] -= rhs[30][8];
			m_data[30][9] -= rhs[30][9];
			m_data[30][10] -= rhs[30][10];
			m_data[30][11] -= rhs[30][11];
			m_data[30][12] -= rhs[30][12];
			m_data[30][13] -= rhs[30][13];
			m_data[30][14] -= rhs[30][14];
			m_data[30][15] -= rhs[30][15];
			m_data[30][16] -= rhs[30][16];
			m_data[30][17] -= rhs[30][17];
			m_data[30][18] -= rhs[30][18];
			m_data[30][19] -= rhs[30][19];
			m_data[30][20] -= rhs[30][20];
			m_data[30][21] -= rhs[30][21];
			m_data[30][22] -= rhs[30][22];
			m_data[30][23] -= rhs[30][23];
			m_data[30][24] -= rhs[30][24];
			m_data[30][25] -= rhs[30][25];
			m_data[30][26] -= rhs[30][26];
			m_data[30][27] -= rhs[30][27];
			m_data[30][28] -= rhs[30][28];
			m_data[30][29] -= rhs[30][29];
			m_data[30][30] -= rhs[30][30];
			m_data[30][31] -= rhs[30][31];

			m_data[31][0] -= rhs[31][0];
			m_data[31][1] -= rhs[31][1];
			m_data[31][2] -= rhs[31][2];
			m_data[31][3] -= rhs[31][3];
			m_data[31][4] -= rhs[31][4];
			m_data[31][5] -= rhs[31][5];
			m_data[31][6] -= rhs[31][6];
			m_data[31][7] -= rhs[31][7];
			m_data[31][8] -= rhs[31][8];
			m_data[31][9] -= rhs[31][9];
			m_data[31][10] -= rhs[31][10];
			m_data[31][11] -= rhs[31][11];
			m_data[31][12] -= rhs[31][12];
			m_data[31][13] -= rhs[31][13];
			m_data[31][14] -= rhs[31][14];
			m_data[31][15] -= rhs[31][15];
			m_data[31][16] -= rhs[31][16];
			m_data[31][17] -= rhs[31][17];
			m_data[31][18] -= rhs[31][18];
			m_data[31][19] -= rhs[31][19];
			m_data[31][20] -= rhs[31][20];
			m_data[31][21] -= rhs[31][21];
			m_data[31][22] -= rhs[31][22];
			m_data[31][23] -= rhs[31][23];
			m_data[31][24] -= rhs[31][24];
			m_data[31][25] -= rhs[31][25];
			m_data[31][26] -= rhs[31][26];
			m_data[31][27] -= rhs[31][27];
			m_data[31][28] -= rhs[31][28];
			m_data[31][29] -= rhs[31][29];
			m_data[31][30] -= rhs[31][30];
			m_data[31][31] -= rhs[31][31];

			return *this;
		}

		template <typename U>
		friend Mat32x32<U> operator*(const Mat32x32<U>& lhs, const Mat32x32<U>& rhs);
		

	private:

		T m_data[32][32] = {};
	};

	/// @brief Representation of a 32x32 integer matrix.
	///
	using Mat32x32i = Mat32x32<int>;

	/// @brief Representation of a 32x32 signed 8-bit integer matrix.
	///
	using Mat32x32i8 = Mat32x32<std::int8_t>;

	/// @brief Representation of a 32x32 float matrix.
	///
	using Mat32x32f = Mat32x32<float>;

	/// @brief Representation of a 32x32 unsigned integer matrix.
	///
	using Mat32x32u = Mat32x32<unsigned int>;


	/// @brief Overload of + binary arithmetic operator.
	/// 
	/// @tparam T is the type of the matrices' values.
	/// @param lhs is the first matrix.
	/// @param rhs is the second matrix.
	/// 
	/// @return The matrix resulted by the addition of the two provided matrices.
	/// 
	template <class T>
	inline Mat32x32<T> operator+(Mat32x32<T> lhs, const Mat32x32<T>& rhs)
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
	inline Mat32x32<T> operator-(Mat32x32<T> lhs, const Mat32x32<T>& rhs)
	{
		lhs -= rhs;
		return lhs;
	}

}
