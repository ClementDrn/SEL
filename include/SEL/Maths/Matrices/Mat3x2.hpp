#pragma once

namespace sel {

	/// @brief Representation of a 3x2 matrix.
	/// 
	/// @tparam T is the type of the matrix's values.
	///  
	template <typename T>
	class Mat3x2
	{
	public:

		/// @brief Default constructor.
		///
		/// This constructor sets matrix's values to default.
		/// 
		Mat3x2() = default;


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
		Mat3x2& operator+=(const Mat3x2& rhs)
		{
			m_data[0][0] += rhs[0][0];
			m_data[0][1] += rhs[0][1];

			m_data[1][0] += rhs[1][0];
			m_data[1][1] += rhs[1][1];

			m_data[2][0] += rhs[2][0];
			m_data[2][1] += rhs[2][1];

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
		Mat3x2& operator-=(const Mat3x2& rhs)
		{
			m_data[0][0] -= rhs[0][0];
			m_data[0][1] -= rhs[0][1];

			m_data[1][0] -= rhs[1][0];
			m_data[1][1] -= rhs[1][1];

			m_data[2][0] -= rhs[2][0];
			m_data[2][1] -= rhs[2][1];

			return *this;
		}


	private:

		T m_data[3][2] = {};
	};

	/// @brief Representation of a 3x2 integer matrix.
	///
	using Mat3x2i = Mat3x2<int>;

	/// @brief Representation of a 3x2 float matrix.
	///
	using Mat3x2f = Mat3x2<float>;

	/// @brief Representation of a 3x2 unsigned integer matrix.
	///
	using Mat3x2u = Mat3x2<unsigned int>;


	/// @brief Overload of + binary arithmetic operator.
	/// 
	/// @tparam T is the type of the matrices' values.
	/// @param lhs is the first matrix.
	/// @param rhs is the second matrix.
	/// 
	/// @return The matrix resulted by the addition of the two provided matrices.
	/// 
	template <class T>
	inline Mat3x2<T> operator+(Mat3x2<T> lhs, const Mat3x2<T>& rhs)
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
	inline Mat3x2<T> operator-(Mat3x2<T> lhs, const Mat3x2<T>& rhs)
	{
		lhs -= rhs;
		return lhs;
	}

}
