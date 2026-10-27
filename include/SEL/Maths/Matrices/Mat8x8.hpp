#pragma once

#include <cstdint>

#include "PackedInt4Matrix.hpp"

#include <cstddef>


namespace sel {

	/// @brief Representation of a 8x8 matrix.
	/// 
	/// @tparam T is the type of the matrix's values.
	///  
	template <typename T>
	class Mat8x8
	{
	public:

		/// @brief Default constructor.
		///
		/// This constructor sets matrix's values to default.
		/// 
		Mat8x8() = default;

		/// @brief Constructor.
		/// 
		/// @param scalar is the value to set to the diagonal to.
		/// 
		Mat8x8(T scalar)
			: m_data{
				{ scalar, 0, 0, 0, 0, 0, 0, 0 },
				{ 0, scalar, 0, 0, 0, 0, 0, 0 },
				{ 0, 0, scalar, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, scalar, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, scalar, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, scalar, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, scalar, 0 },
				{ 0, 0, 0, 0, 0, 0, 0, scalar }
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
		/// @param m1_0 is the value of row 1, column 0.
		/// @param m1_1 is the value of row 1, column 1.
		/// @param m1_2 is the value of row 1, column 2.
		/// @param m1_3 is the value of row 1, column 3.
		/// @param m1_4 is the value of row 1, column 4.
		/// @param m1_5 is the value of row 1, column 5.
		/// @param m1_6 is the value of row 1, column 6.
		/// @param m1_7 is the value of row 1, column 7.
		/// @param m2_0 is the value of row 2, column 0.
		/// @param m2_1 is the value of row 2, column 1.
		/// @param m2_2 is the value of row 2, column 2.
		/// @param m2_3 is the value of row 2, column 3.
		/// @param m2_4 is the value of row 2, column 4.
		/// @param m2_5 is the value of row 2, column 5.
		/// @param m2_6 is the value of row 2, column 6.
		/// @param m2_7 is the value of row 2, column 7.
		/// @param m3_0 is the value of row 3, column 0.
		/// @param m3_1 is the value of row 3, column 1.
		/// @param m3_2 is the value of row 3, column 2.
		/// @param m3_3 is the value of row 3, column 3.
		/// @param m3_4 is the value of row 3, column 4.
		/// @param m3_5 is the value of row 3, column 5.
		/// @param m3_6 is the value of row 3, column 6.
		/// @param m3_7 is the value of row 3, column 7.
		/// @param m4_0 is the value of row 4, column 0.
		/// @param m4_1 is the value of row 4, column 1.
		/// @param m4_2 is the value of row 4, column 2.
		/// @param m4_3 is the value of row 4, column 3.
		/// @param m4_4 is the value of row 4, column 4.
		/// @param m4_5 is the value of row 4, column 5.
		/// @param m4_6 is the value of row 4, column 6.
		/// @param m4_7 is the value of row 4, column 7.
		/// @param m5_0 is the value of row 5, column 0.
		/// @param m5_1 is the value of row 5, column 1.
		/// @param m5_2 is the value of row 5, column 2.
		/// @param m5_3 is the value of row 5, column 3.
		/// @param m5_4 is the value of row 5, column 4.
		/// @param m5_5 is the value of row 5, column 5.
		/// @param m5_6 is the value of row 5, column 6.
		/// @param m5_7 is the value of row 5, column 7.
		/// @param m6_0 is the value of row 6, column 0.
		/// @param m6_1 is the value of row 6, column 1.
		/// @param m6_2 is the value of row 6, column 2.
		/// @param m6_3 is the value of row 6, column 3.
		/// @param m6_4 is the value of row 6, column 4.
		/// @param m6_5 is the value of row 6, column 5.
		/// @param m6_6 is the value of row 6, column 6.
		/// @param m6_7 is the value of row 6, column 7.
		/// @param m7_0 is the value of row 7, column 0.
		/// @param m7_1 is the value of row 7, column 1.
		/// @param m7_2 is the value of row 7, column 2.
		/// @param m7_3 is the value of row 7, column 3.
		/// @param m7_4 is the value of row 7, column 4.
		/// @param m7_5 is the value of row 7, column 5.
		/// @param m7_6 is the value of row 7, column 6.
		/// @param m7_7 is the value of row 7, column 7.
		/// 
		Mat8x8(
			T m0_0, T m0_1, T m0_2, T m0_3, T m0_4, T m0_5, T m0_6, T m0_7,
			T m1_0, T m1_1, T m1_2, T m1_3, T m1_4, T m1_5, T m1_6, T m1_7,
			T m2_0, T m2_1, T m2_2, T m2_3, T m2_4, T m2_5, T m2_6, T m2_7,
			T m3_0, T m3_1, T m3_2, T m3_3, T m3_4, T m3_5, T m3_6, T m3_7,
			T m4_0, T m4_1, T m4_2, T m4_3, T m4_4, T m4_5, T m4_6, T m4_7,
			T m5_0, T m5_1, T m5_2, T m5_3, T m5_4, T m5_5, T m5_6, T m5_7,
			T m6_0, T m6_1, T m6_2, T m6_3, T m6_4, T m6_5, T m6_6, T m6_7,
			T m7_0, T m7_1, T m7_2, T m7_3, T m7_4, T m7_5, T m7_6, T m7_7)
			: m_data{
				{ m0_0, m0_1, m0_2, m0_3, m0_4, m0_5, m0_6, m0_7 },
				{ m1_0, m1_1, m1_2, m1_3, m1_4, m1_5, m1_6, m1_7 },
				{ m2_0, m2_1, m2_2, m2_3, m2_4, m2_5, m2_6, m2_7 },
				{ m3_0, m3_1, m3_2, m3_3, m3_4, m3_5, m3_6, m3_7 },
				{ m4_0, m4_1, m4_2, m4_3, m4_4, m4_5, m4_6, m4_7 },
				{ m5_0, m5_1, m5_2, m5_3, m5_4, m5_5, m5_6, m5_7 },
				{ m6_0, m6_1, m6_2, m6_3, m6_4, m6_5, m6_6, m6_7 },
				{ m7_0, m7_1, m7_2, m7_3, m7_4, m7_5, m7_6, m7_7 }
			} {}

		/// @brief Copy constructor.
		///
		/// This constructor copies the input matrix.
		/// 
		/// @param other is the matrix to copy.
		/// 
		Mat8x8(const Mat8x8& other)
			: m_data{
				{ other[0][0], other[0][1], other[0][2], other[0][3], other[0][4], other[0][5], other[0][6], other[0][7] },
				{ other[1][0], other[1][1], other[1][2], other[1][3], other[1][4], other[1][5], other[1][6], other[1][7] },
				{ other[2][0], other[2][1], other[2][2], other[2][3], other[2][4], other[2][5], other[2][6], other[2][7] },
				{ other[3][0], other[3][1], other[3][2], other[3][3], other[3][4], other[3][5], other[3][6], other[3][7] },
				{ other[4][0], other[4][1], other[4][2], other[4][3], other[4][4], other[4][5], other[4][6], other[4][7] },
				{ other[5][0], other[5][1], other[5][2], other[5][3], other[5][4], other[5][5], other[5][6], other[5][7] },
				{ other[6][0], other[6][1], other[6][2], other[6][3], other[6][4], other[6][5], other[6][6], other[6][7] },
				{ other[7][0], other[7][1], other[7][2], other[7][3], other[7][4], other[7][5], other[7][6], other[7][7] }
			} {}


		/// @return the identity matrix.
		/// 
		static Mat8x8<T> identity()
		{
			return Mat8x8<T>(1);
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
		Mat8x8& operator+=(const Mat8x8& rhs)
		{
			m_data[0][0] += rhs[0][0];
			m_data[0][1] += rhs[0][1];
			m_data[0][2] += rhs[0][2];
			m_data[0][3] += rhs[0][3];
			m_data[0][4] += rhs[0][4];
			m_data[0][5] += rhs[0][5];
			m_data[0][6] += rhs[0][6];
			m_data[0][7] += rhs[0][7];

			m_data[1][0] += rhs[1][0];
			m_data[1][1] += rhs[1][1];
			m_data[1][2] += rhs[1][2];
			m_data[1][3] += rhs[1][3];
			m_data[1][4] += rhs[1][4];
			m_data[1][5] += rhs[1][5];
			m_data[1][6] += rhs[1][6];
			m_data[1][7] += rhs[1][7];

			m_data[2][0] += rhs[2][0];
			m_data[2][1] += rhs[2][1];
			m_data[2][2] += rhs[2][2];
			m_data[2][3] += rhs[2][3];
			m_data[2][4] += rhs[2][4];
			m_data[2][5] += rhs[2][5];
			m_data[2][6] += rhs[2][6];
			m_data[2][7] += rhs[2][7];

			m_data[3][0] += rhs[3][0];
			m_data[3][1] += rhs[3][1];
			m_data[3][2] += rhs[3][2];
			m_data[3][3] += rhs[3][3];
			m_data[3][4] += rhs[3][4];
			m_data[3][5] += rhs[3][5];
			m_data[3][6] += rhs[3][6];
			m_data[3][7] += rhs[3][7];

			m_data[4][0] += rhs[4][0];
			m_data[4][1] += rhs[4][1];
			m_data[4][2] += rhs[4][2];
			m_data[4][3] += rhs[4][3];
			m_data[4][4] += rhs[4][4];
			m_data[4][5] += rhs[4][5];
			m_data[4][6] += rhs[4][6];
			m_data[4][7] += rhs[4][7];

			m_data[5][0] += rhs[5][0];
			m_data[5][1] += rhs[5][1];
			m_data[5][2] += rhs[5][2];
			m_data[5][3] += rhs[5][3];
			m_data[5][4] += rhs[5][4];
			m_data[5][5] += rhs[5][5];
			m_data[5][6] += rhs[5][6];
			m_data[5][7] += rhs[5][7];

			m_data[6][0] += rhs[6][0];
			m_data[6][1] += rhs[6][1];
			m_data[6][2] += rhs[6][2];
			m_data[6][3] += rhs[6][3];
			m_data[6][4] += rhs[6][4];
			m_data[6][5] += rhs[6][5];
			m_data[6][6] += rhs[6][6];
			m_data[6][7] += rhs[6][7];

			m_data[7][0] += rhs[7][0];
			m_data[7][1] += rhs[7][1];
			m_data[7][2] += rhs[7][2];
			m_data[7][3] += rhs[7][3];
			m_data[7][4] += rhs[7][4];
			m_data[7][5] += rhs[7][5];
			m_data[7][6] += rhs[7][6];
			m_data[7][7] += rhs[7][7];

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
		Mat8x8& operator-=(const Mat8x8& rhs)
		{
			m_data[0][0] -= rhs[0][0];
			m_data[0][1] -= rhs[0][1];
			m_data[0][2] -= rhs[0][2];
			m_data[0][3] -= rhs[0][3];
			m_data[0][4] -= rhs[0][4];
			m_data[0][5] -= rhs[0][5];
			m_data[0][6] -= rhs[0][6];
			m_data[0][7] -= rhs[0][7];

			m_data[1][0] -= rhs[1][0];
			m_data[1][1] -= rhs[1][1];
			m_data[1][2] -= rhs[1][2];
			m_data[1][3] -= rhs[1][3];
			m_data[1][4] -= rhs[1][4];
			m_data[1][5] -= rhs[1][5];
			m_data[1][6] -= rhs[1][6];
			m_data[1][7] -= rhs[1][7];

			m_data[2][0] -= rhs[2][0];
			m_data[2][1] -= rhs[2][1];
			m_data[2][2] -= rhs[2][2];
			m_data[2][3] -= rhs[2][3];
			m_data[2][4] -= rhs[2][4];
			m_data[2][5] -= rhs[2][5];
			m_data[2][6] -= rhs[2][6];
			m_data[2][7] -= rhs[2][7];

			m_data[3][0] -= rhs[3][0];
			m_data[3][1] -= rhs[3][1];
			m_data[3][2] -= rhs[3][2];
			m_data[3][3] -= rhs[3][3];
			m_data[3][4] -= rhs[3][4];
			m_data[3][5] -= rhs[3][5];
			m_data[3][6] -= rhs[3][6];
			m_data[3][7] -= rhs[3][7];

			m_data[4][0] -= rhs[4][0];
			m_data[4][1] -= rhs[4][1];
			m_data[4][2] -= rhs[4][2];
			m_data[4][3] -= rhs[4][3];
			m_data[4][4] -= rhs[4][4];
			m_data[4][5] -= rhs[4][5];
			m_data[4][6] -= rhs[4][6];
			m_data[4][7] -= rhs[4][7];

			m_data[5][0] -= rhs[5][0];
			m_data[5][1] -= rhs[5][1];
			m_data[5][2] -= rhs[5][2];
			m_data[5][3] -= rhs[5][3];
			m_data[5][4] -= rhs[5][4];
			m_data[5][5] -= rhs[5][5];
			m_data[5][6] -= rhs[5][6];
			m_data[5][7] -= rhs[5][7];

			m_data[6][0] -= rhs[6][0];
			m_data[6][1] -= rhs[6][1];
			m_data[6][2] -= rhs[6][2];
			m_data[6][3] -= rhs[6][3];
			m_data[6][4] -= rhs[6][4];
			m_data[6][5] -= rhs[6][5];
			m_data[6][6] -= rhs[6][6];
			m_data[6][7] -= rhs[6][7];

			m_data[7][0] -= rhs[7][0];
			m_data[7][1] -= rhs[7][1];
			m_data[7][2] -= rhs[7][2];
			m_data[7][3] -= rhs[7][3];
			m_data[7][4] -= rhs[7][4];
			m_data[7][5] -= rhs[7][5];
			m_data[7][6] -= rhs[7][6];
			m_data[7][7] -= rhs[7][7];

			return *this;
		}

		template <typename U>
		friend Mat8x8<U> operator*(const Mat8x8<U>& lhs, const Mat8x8<U>& rhs);
		

	private:

		T m_data[8][8] = {};
	};

	template <>
	class Mat8x8<int4> : public utils::PackedInt4Matrix<8, 8, Mat8x8<int4>>
	{
		using Base = utils::PackedInt4Matrix<8, 8, Mat8x8<int4>>;
	public:
		using Base::Base;
		constexpr Mat8x8() = default;
	};

	/// @brief Representation of a packed 8x8 signed four-bit matrix.
	using Mat8x8i4 = Mat8x8<int4>;

	/// @brief Representation of a 8x8 integer matrix.
	///
	using Mat8x8i = Mat8x8<int>;

	/// @brief Representation of a 8x8 signed 8-bit integer matrix.
	///
	using Mat8x8i8 = Mat8x8<std::int8_t>;

	/// @brief Representation of a 8x8 float matrix.
	///
	using Mat8x8f = Mat8x8<float>;

	/// @brief Representation of a 8x8 unsigned integer matrix.
	///
	using Mat8x8u = Mat8x8<unsigned int>;


	/// @brief Overload of + binary arithmetic operator.
	/// 
	/// @tparam T is the type of the matrices' values.
	/// @param lhs is the first matrix.
	/// @param rhs is the second matrix.
	/// 
	/// @return The matrix resulted by the addition of the two provided matrices.
	/// 
	template <class T>
	inline Mat8x8<T> operator+(Mat8x8<T> lhs, const Mat8x8<T>& rhs)
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
	inline Mat8x8<T> operator-(Mat8x8<T> lhs, const Mat8x8<T>& rhs)
	{
		lhs -= rhs;
		return lhs;
	}

}
