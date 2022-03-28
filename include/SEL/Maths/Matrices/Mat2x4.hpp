#pragma once


namespace sel {

	template <typename T>
	class Mat2x4
	{
	public:

		Mat2x4() = default;


		T* operator[](size_t idx) { return m_data[idx]; }
		const T* operator[](size_t idx) const { return m_data[idx]; }


		Mat2x4& operator+=(const Mat2x4& rhs)
		{
			m_data[0][0] += rhs[0][0];
			m_data[0][1] += rhs[0][1];
			m_data[0][2] += rhs[0][2];
			m_data[0][3] += rhs[0][3];

			m_data[1][0] += rhs[1][0];
			m_data[1][1] += rhs[1][1];
			m_data[1][2] += rhs[1][2];
			m_data[1][3] += rhs[1][3];

			return *this;
		}

		Mat2x4& operator-=(const Mat2x4& rhs)
		{
			m_data[0][0] -= rhs[0][0];
			m_data[0][1] -= rhs[0][1];
			m_data[0][2] -= rhs[0][2];
			m_data[0][3] -= rhs[0][3];

			m_data[1][0] -= rhs[1][0];
			m_data[1][1] -= rhs[1][1];
			m_data[1][2] -= rhs[1][2];
			m_data[1][3] -= rhs[1][3];

			return *this;
		}


	private:

		T m_data[2][4] = {};
	};

	using Mat2x4i = Mat2x4<int>;
	using Mat2x4f = Mat2x4<float>;
	using Mat2x4u = Mat2x4<unsigned int>;


	template <class T>
	inline Mat2x4<T> operator+(Mat2x4<T> lhs, const Mat2x4<T>& rhs)
	{
		lhs += rhs;
		return lhs;
	}

	template <class T>
	inline Mat2x4<T> operator-(Mat2x4<T> lhs, const Mat2x4<T>& rhs)
	{
		lhs -= rhs;
		return lhs;
	}

}
