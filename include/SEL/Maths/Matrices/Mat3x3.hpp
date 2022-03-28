#pragma once


namespace sel {

	template <typename T>
	class Mat3x3
	{
	public:

		Mat3x3() = default;


		T* operator[](size_t idx) { return m_data[idx]; }
		const T* operator[](size_t idx) const { return m_data[idx]; }


		Mat3x3& operator+=(const Mat3x3& rhs)
		{
			m_data[0][0] += rhs[0][0];
			m_data[0][1] += rhs[0][1];
			m_data[0][2] += rhs[0][2];

			m_data[1][0] += rhs[1][0];
			m_data[1][1] += rhs[1][1];
			m_data[1][2] += rhs[1][2];

			m_data[2][0] += rhs[2][0];
			m_data[2][1] += rhs[2][1];
			m_data[2][2] += rhs[2][2];

			return *this;
		}

		Mat3x3& operator-=(const Mat3x3& rhs)
		{
			m_data[0][0] -= rhs[0][0];
			m_data[0][1] -= rhs[0][1];
			m_data[0][2] -= rhs[0][2];

			m_data[1][0] -= rhs[1][0];
			m_data[1][1] -= rhs[1][1];
			m_data[1][2] -= rhs[1][2];

			m_data[2][0] -= rhs[2][0];
			m_data[2][1] -= rhs[2][1];
			m_data[2][2] -= rhs[2][2];

			return *this;
		}


	private:

		T m_data[3][3] = {};
	};

	using Mat3x3i = Mat3x3<int>;
	using Mat3x3f = Mat3x3<float>;
	using Mat3x3u = Mat3x3<unsigned int>;


	template <class T>
	inline Mat3x3<T> operator+(Mat3x3<T> lhs, const Mat3x3<T>& rhs)
	{
		lhs += rhs;
		return lhs;
	}

	template <class T>
	inline Mat3x3<T> operator-(Mat3x3<T> lhs, const Mat3x3<T>& rhs)
	{
		lhs -= rhs;
		return lhs;
	}

}
