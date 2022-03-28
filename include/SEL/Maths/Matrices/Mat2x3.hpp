#pragma once


namespace sel {

	template <typename T>
	class Mat2x3
	{
	public:

		Mat2x3() = default;


		T* operator[](size_t idx) { return m_data[idx]; }
		const T* operator[](size_t idx) const { return m_data[idx]; }


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

	using Mat2x3i = Mat2x3<int>;
	using Mat2x3f = Mat2x3<float>;
	using Mat2x3u = Mat2x3<unsigned int>;


	template <class T>
	inline Mat2x3<T> operator+(Mat2x3<T> lhs, const Mat2x3<T>& rhs)
	{
		lhs += rhs;
		return lhs;
	}

	template <class T>
	inline Mat2x3<T> operator-(Mat2x3<T> lhs, const Mat2x3<T>& rhs)
	{
		lhs -= rhs;
		return lhs;
	}

}
