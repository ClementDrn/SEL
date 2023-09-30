#pragma once


namespace sel {

	/// @brief Representation of a 2x3 matrix.
	/// 
	/// @tparam T is the type of the matrix's values.
	///  
	template <typename T>
	class Mat2x3
	{
	public:

		/// @brief Default constructor.
		///
		/// This constructor sets matrix's values to default.
		/// 
		Mat2x3() = default;

		/// @brief Constructor.
		/// 
		/// @param scalar is the value to set to the diagonal to.
		/// 
		Mat2x3(T scalar)
			: m_data{ { scalar, 0, 0 }, { 0, scalar, 0 } } {}

		/// @brief Constructor.
		///
		/// This constructor sets matrix's values to the given ones.
		/// 
		/// @param m00 is the value of the first row, first column.
		/// @param m01 is the value of the first row, second column.
		/// @param m02 is the value of the first row, third column.
		/// @param m10 is the value of the second row, first column.
		/// @param m11 is the value of the second row, second column.
		/// @param m12 is the value of the second row, third column.
		/// 
		Mat2x3(T m00, T m01, T m02, T m10, T m11, T m12)
			: m_data{ m00, m01, m02, m10, m11, m12 } {}

		/// @brief Copy constructor.
		///
		/// This constructor copies the input matrix.
		/// 
		/// @param other is the matrix to copy.
		/// 
		Mat2x3(const Mat2x3& other)
			: m_data{ other[0][0], other[0][1], other[0][2], other[1][0], other[1][1], other[1][2] } {}


		/// @return the identity matrix.
		/// 
		static Mat2x3<T> identity()
		{
			return Mat2x3<T>(
				1, 0, 0,
				0, 1, 0
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
		Mat2x3& operator+=(const Mat2x3& rhs)
		{
			m_data[0][0] += rhs[0][0];
			m_data[0][1] += rhs[0][1];
			m_data[0][2] += rhs[0][2];

			m_data[1][0] += rhs[1][0];
			m_data[1][1] += rhs[1][1];
			m_data[1][2] += rhs[1][2];

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
		Mat2x3& operator-=(const Mat2x3& rhs)
		{
			m_data[0][0] -= rhs[0][0];
			m_data[0][1] -= rhs[0][1];
			m_data[0][2] -= rhs[0][2];

			m_data[1][0] -= rhs[1][0];
			m_data[1][1] -= rhs[1][1];
			m_data[1][2] -= rhs[1][2];

			return *this;
		}


	private:

		T m_data[2][3] = {};
	};

	/// @brief Representation of a 2x3 integer matrix.
	///
	using Mat2x3i = Mat2x3<int>;

	/// @brief Representation of a 2x3 float matrix.
	///
	using Mat2x3f = Mat2x3<float>;

	/// @brief Representation of a 2x3 unsigned integer matrix.
	///
	using Mat2x3u = Mat2x3<unsigned int>;


	/// @brief Overload of + binary arithmetic operator.
	/// 
	/// @tparam T is the type of the matrices' values.
	/// @param lhs is the first matrix.
	/// @param rhs is the second matrix.
	/// 
	/// @return The matrix resulted by the addition of the two provided matrices.
	/// 
	template <class T>
	inline Mat2x3<T> operator+(Mat2x3<T> lhs, const Mat2x3<T>& rhs)
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
	inline Mat2x3<T> operator-(Mat2x3<T> lhs, const Mat2x3<T>& rhs)
	{
		lhs -= rhs;
		return lhs;
	}

}
