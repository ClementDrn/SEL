#pragma once

namespace sel {

	/// @brief Representation of a 3x4 matrix.
	/// 
	/// @tparam T is the type of the matrix's values.
	///  
	template <typename T>
	class Mat3x4
	{
	public:

		/// @brief Default constructor.
		///
		/// This constructor sets matrix's values to default.
		/// 
		Mat3x4() = default;

		/// @brief Constructor.
		/// 
		/// @param scalar is the value to set to the diagonal to.
		/// 
		Mat3x4(T scalar)
			: m_data{ { scalar, 0, 0, 0 }, { 0, scalar, 0, 0 }, { 0, 0, scalar, 0 } } {}

		/// @brief Constructor.
		///
		/// This constructor sets matrix's values to the given ones.
		/// 
		/// @param m00 is the value of the first row, first column.
		/// @param m01 is the value of the first row, second column.
		/// @param m10 is the value of the second row, first column.
		/// @param m11 is the value of the second row, second column.
		/// @param m20 is the value of the third row, first column.
		/// @param m21 is the value of the third row, second column.
		/// @param m30 is the value of the fourth row, first column.
		/// @param m31 is the value of the fourth row, second column.
		/// @param m32 is the value of the fourth row, third column.
		/// @param m33 is the value of the fourth row, fourth column.
		/// 
		Mat3x4(T m00, T m01, T m02, T m03, T m10, T m11, T m12, T m13, T m20, T m21, T m22, T m23, T m30, T m31, T m32, T m33)
			: m_data{ m00, m01, m02, m03, m10, m11, m12, m13, m20, m21, m22, m23, m30, m31, m32, m33 } {}

		/// @brief Copy constructor.
		///
		/// This constructor copies the input matrix.
		/// 
		/// @param other is the matrix to copy.
		/// 
		Mat3x4(const Mat3x4& other)
			: m_data{ other[0][0], other[0][1], other[0][2], other[0][3], other[1][0], other[1][1], other[1][2], other[1][3], other[2][0], other[2][1], other[2][2], other[2][3] } {}


		/// @return the identity matrix.
		/// 
		static Mat3x4<T> identity()
		{
			return Mat3x4<T>(
				1, 0, 0, 0,
				0, 1, 0, 0,
				0, 0, 1, 0
			);
		}


		/// @brief Access specified matrix column.
		/// 
		/// Returns the column at specified location index (idx). No bounds checking is performed.
		/// To access a specific value of the matrix, first retrieve a column, then access to one of its values 
		/// by providing another index, you will end up with a two coordinate access.
		/// 
		/// @param idx is the index of the matrix column to retrieve.
		/// 
		/// @return The specified matrix column.
		/// 
		constexpr T* operator[](size_t idx) { return m_data[idx]; }
		constexpr const T* operator[](size_t idx) const { return m_data[idx]; }


		/// @brief Overload of += binary arithmetic operator.
		/// 
		/// The other matrix is added to the instance.
		/// 
		/// @param rhs is the matrix which must be added to the instance.
		/// 
		/// @return The reference to the updated matrix.
		/// 
		Mat3x4& operator+=(const Mat3x4& rhs)
		{
			m_data[0][0] += rhs[0][0];
			m_data[0][1] += rhs[0][1];
			m_data[0][2] += rhs[0][2];
			m_data[0][3] += rhs[0][3];

			m_data[1][0] += rhs[1][0];
			m_data[1][1] += rhs[1][1];
			m_data[1][2] += rhs[1][2];
			m_data[1][3] += rhs[1][3];

			m_data[2][0] += rhs[2][0];
			m_data[2][1] += rhs[2][1];
			m_data[2][2] += rhs[2][2];
			m_data[2][3] += rhs[2][3];

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
		Mat3x4& operator-=(const Mat3x4& rhs)
		{
			m_data[0][0] -= rhs[0][0];
			m_data[0][1] -= rhs[0][1];
			m_data[0][2] -= rhs[0][2];
			m_data[0][3] -= rhs[0][3];

			m_data[1][0] -= rhs[1][0];
			m_data[1][1] -= rhs[1][1];
			m_data[1][2] -= rhs[1][2];
			m_data[1][3] -= rhs[1][3];

			m_data[2][0] -= rhs[2][0];
			m_data[2][1] -= rhs[2][1];
			m_data[2][2] -= rhs[2][2];
			m_data[2][3] -= rhs[2][3];

			return *this;
		}


	private:

		T m_data[3][4] = {};
	};

	/// @brief Representation of a 3x4 integer matrix.
	///
	using Mat3x4i = Mat3x4<int>;

	/// @brief Representation of a 3x4 float matrix.
	///
	using Mat3x4f = Mat3x4<float>;

	/// @brief Representation of a 3x4 unsigned integer matrix.
	///
	using Mat3x4u = Mat3x4<unsigned int>;


	/// @brief Overload of + binary arithmetic operator.
	/// 
	/// @tparam T is the type of the matrices' values.
	/// @param lhs is the first matrix.
	/// @param rhs is the second matrix.
	/// 
	/// @return The matrix resulted by the addition of the two provided matrices.
	/// 
	template <class T>
	inline Mat3x4<T> operator+(Mat3x4<T> lhs, const Mat3x4<T>& rhs)
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
	inline Mat3x4<T> operator-(Mat3x4<T> lhs, const Mat3x4<T>& rhs)
	{
		lhs -= rhs;
		return lhs;
	}

}
