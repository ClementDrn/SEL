#pragma once


namespace sel {

	template <typename T>
	class Mat4x3
	{
	public:

		Mat4x3() = default;


		T* operator[](size_t idx) { return m_data[idx]; }
		const T* operator[](size_t idx) const { return m_data[idx]; }


		Mat4x3& operator+=(const Mat4x3& rhs)
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

			m_data[3][0] += rhs[3][0];
			m_data[3][1] += rhs[3][1];
			m_data[3][2] += rhs[3][2];

			return *this;
		}

		Mat4x3& operator-=(const Mat4x3& rhs)
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

			m_data[3][0] -= rhs[3][0];
			m_data[3][1] -= rhs[3][1];
			m_data[3][2] -= rhs[3][2];

			return *this;
		}


	private:

		T m_data[4][3] = {};
	};

	using Mat4x3i = Mat4x3<int>;
	using Mat4x3f = Mat4x3<float>;
	using Mat4x3u = Mat4x3<unsigned int>;


	template <class T>
	inline Mat4x3<T> operator+(Mat4x3<T> lhs, const Mat4x3<T>& rhs)
	{
		lhs += rhs;
		return lhs;
	}

	template <class T>
	inline Mat4x3<T> operator-(Mat4x3<T> lhs, const Mat4x3<T>& rhs)
	{
		lhs -= rhs;
		return lhs;
	}

}
