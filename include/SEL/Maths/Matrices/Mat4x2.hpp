#pragma once


namespace sel {

	template <typename T>
	class Mat4x2
	{
	public:

		Mat4x2() = default;


		T* operator[](size_t idx) { return m_data[idx]; }
		const T* operator[](size_t idx) const { return m_data[idx]; }


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

	using Mat4x2i = Mat4x2<int>;
	using Mat4x2f = Mat4x2<float>;
	using Mat4x2u = Mat4x2<unsigned int>;


	template <class T>
	inline Mat4x2<T> operator+(Mat4x2<T> lhs, const Mat4x2<T>& rhs)
	{
		lhs += rhs;
		return lhs;
	}

	template <class T>
	inline Mat4x2<T> operator-(Mat4x2<T> lhs, const Mat4x2<T>& rhs)
	{
		lhs -= rhs;
		return lhs;
	}

}
