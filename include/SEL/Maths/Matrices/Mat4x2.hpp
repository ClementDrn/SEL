#pragma once


namespace sel {

	/// @brief Representation of a 4x2 matrix.
	/// 
	/// @tparam T is the type of the matrix's values.
	///  
	template <typename T>
	class Mat4x2
	{
	public:

		/// @brief Default constructor.
		///
		/// This constructor sets matrix's values to default.
		/// 
		Mat4x2() = default;

		/// @brief Constructor.
		/// 
		/// @param scalar is the value to set to the diagonal to.
		/// 
		Mat4x2(T scalar)
			: m_data{ { scalar, 0 }, { 0, scalar }, { 0, 0 }, { 0, 0 } } {}

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
		/// 
		Mat4x2(T m00, T m01, T m10, T m11, T m20, T m21, T m30, T m31)
			: m_data{ m00, m01, m10, m11, m20, m21, m30, m31 } {}

		/// @brief Copy constructor.
		///
		/// This constructor copies the input matrix.
		/// 
		/// @param other is the matrix to copy.
		/// 
		Mat4x2(const Mat4x2& other)
			: m_data{ other[0][0], other[0][1], other[1][0], other[1][1], other[2][0], other[2][1], other[3][0], other[3][1] } {}


		/// @return the identity matrix.
		/// 
		static Mat4x2<T> identity()
		{
			return Mat4x2<T>(
				1, 0,
				0, 1,
				0, 0,
				0, 0
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
		Mat4x2& operator+=(const Mat4x2& rhs)
		{
			m_data[0][0] += rhs[0][0];
			m_data[0][1] += rhs[0][1];

			m_data[1][0] += rhs[1][0];
			m_data[1][1] += rhs[1][1];

			m_data[2][0] += rhs[2][0];
			m_data[2][1] += rhs[2][1];

			m_data[3][0] += rhs[3][0];
			m_data[3][1] += rhs[3][1];

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
		Mat4x2& operator-=(const Mat4x2& rhs)
		{
			m_data[0][0] -= rhs[0][0];
			m_data[0][1] -= rhs[0][1];

			m_data[1][0] -= rhs[1][0];
			m_data[1][1] -= rhs[1][1];

			m_data[2][0] -= rhs[2][0];
			m_data[2][1] -= rhs[2][1];

			m_data[3][0] -= rhs[3][0];
			m_data[3][1] -= rhs[3][1];

			return *this;
		}
		

	private:

		T m_data[4][2] = {};
	};

	/// @brief Representation of a 4x2 integer matrix.
	///
	using Mat4x2i = Mat4x2<int>;

	/// @brief Representation of a 4x2 float matrix.
	///
	using Mat4x2f = Mat4x2<float>;

	/// @brief Representation of a 4x2 unsigned integer matrix.
	///
	using Mat4x2u = Mat4x2<unsigned int>;


	/// @brief Overload of + binary arithmetic operator.
	/// 
	/// @tparam T is the type of the matrices' values.
	/// @param lhs is the first matrix.
	/// @param rhs is the second matrix.
	/// 
	/// @return The matrix resulted by the addition of the two provided matrices.
	/// 
	template <class T>
	inline Mat4x2<T> operator+(Mat4x2<T> lhs, const Mat4x2<T>& rhs)
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
	inline Mat4x2<T> operator-(Mat4x2<T> lhs, const Mat4x2<T>& rhs)
	{
		lhs -= rhs;
		return lhs;
	}

}
