#pragma once


namespace sel {

	/// @brief Representation of a 2x2 matrix.
	/// 
	/// @tparam T is the type of the matrix's values.
	///  
	template <typename T>
	class Mat2x2
	{
	public:

		/// @brief Default constructor.
		///
		/// This constructor sets matrix's values to default.
		/// 
		Mat2x2() = default;

		/// @brief Constructor.
		/// 
		/// @param scalar is the value to set to the diagonal to.
		/// 
		Mat2x2(T scalar)
			: m_data{ { scalar, 0 }, { 0, scalar } } {}

		/// @brief Constructor.
		///
		/// This constructor sets matrix's values to the given ones.
		/// 
		/// @param m00 is the value of the first row, first column.
		/// @param m01 is the value of the first row, second column.
		/// @param m10 is the value of the second row, first column.
		/// @param m11 is the value of the second row, second column.
		/// 
		Mat2x2(T m00, T m01, T m10, T m11)
			: m_data{ m00, m01, m10, m11 } {}

		/// @brief Copy constructor.
		///
		/// This constructor copies the input matrix.
		/// 
		/// @param other is the matrix to copy.
		/// 
		Mat2x2(const Mat2x2& other)
			: m_data{ other[0][0], other[0][1], other[1][0], other[1][1] } {}
		
			
		/// @return the identity matrix.
		/// 
		static Mat2x2<T> identity()
		{
			return Mat2x2<T>(
				1, 0,
				0, 1
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
		Mat2x2& operator+=(const Mat2x2& rhs)
		{
			m_data[0][0] += rhs[0][0];
			m_data[0][1] += rhs[0][1];

			m_data[1][0] += rhs[1][0];
			m_data[1][1] += rhs[1][1];

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
		Mat2x2& operator-=(const Mat2x2& rhs)
		{
			m_data[0][0] -= rhs[0][0];
			m_data[0][1] -= rhs[0][1];

			m_data[1][0] -= rhs[1][0];
			m_data[1][1] -= rhs[1][1];

			return *this;
		}


	private:

		T m_data[2][2] = {};
	};

	/// @brief Representation of a 2x2 integer matrix.
	///
	using Mat2x2i = Mat2x2<int>;

	/// @brief Representation of a 2x2 float matrix.
	///
	using Mat2x2f = Mat2x2<float>;

	/// @brief Representation of a 2x2 unsigned integer matrix.
	///
	using Mat2x2u = Mat2x2<unsigned int>;

	
	/// @brief Overload of + binary arithmetic operator.
	/// 
	/// @tparam T is the type of the matrices' values.
	/// @param lhs is the first matrix.
	/// @param rhs is the second matrix.
	/// 
	/// @return The matrix resulted by the addition of the two provided matrices.
	/// 
	template <class T>
	inline Mat2x2<T> operator+(Mat2x2<T> lhs, const Mat2x2<T>& rhs)
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
	inline Mat2x2<T> operator-(Mat2x2<T> lhs, const Mat2x2<T>& rhs)
	{
		lhs -= rhs;
		return lhs;
	}

}
