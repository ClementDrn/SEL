#pragma once

namespace sel {

	template <typename T>
	class Mat3x4
	{
	public:

		Mat3x4() = default;


		T* operator[](size_t idx) { return m_data[idx]; }
		const T* operator[](size_t idx) const { return m_data[idx]; }


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

	using Mat3x4i = Mat3x4<int>;
	using Mat3x4f = Mat3x4<float>;
	using Mat3x4u = Mat3x4<unsigned int>;


	template <class T>
	inline Mat3x4<T> operator+(Mat3x4<T> lhs, const Mat3x4<T>& rhs)
	{
		lhs += rhs;
		return lhs;
	}

	template <class T>
	inline Mat3x4<T> operator-(Mat3x4<T> lhs, const Mat3x4<T>& rhs)
	{
		lhs -= rhs;
		return lhs;
	}

}
