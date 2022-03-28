#pragma once

namespace sel {

	template <typename T>
	class Mat3x2
	{
	public:

		Mat3x2() = default;


		T* operator[](size_t idx) { return m_data[idx]; }
		const T* operator[](size_t idx) const { return m_data[idx]; }


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

	using Mat3x2i = Mat3x2<int>;
	using Mat3x2f = Mat3x2<float>;
	using Mat3x2u = Mat3x2<unsigned int>;


	template <class T>
	inline Mat3x2<T> operator+(Mat3x2<T> lhs, const Mat3x2<T>& rhs)
	{
		lhs += rhs;
		return lhs;
	}

	template <class T>
	inline Mat3x2<T> operator-(Mat3x2<T> lhs, const Mat3x2<T>& rhs)
	{
		lhs -= rhs;
		return lhs;
	}

}
