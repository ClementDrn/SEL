#pragma once


namespace sel {

	template <typename T>
	class Mat4x4
	{
	public:

		Mat4x4() = default;


		T* operator[](size_t idx) { return m_data[idx]; }
		const T* operator[](size_t idx) const { return m_data[idx]; }


		Mat4x4& operator+=(const Mat4x4& rhs)
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

			m_data[3][0] += rhs[3][0];
			m_data[3][1] += rhs[3][1];
			m_data[3][2] += rhs[3][2];
			m_data[3][3] += rhs[3][3];

			return *this;
		}

		Mat4x4& operator-=(const Mat4x4& rhs)
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

			m_data[3][0] -= rhs[3][0];
			m_data[3][1] -= rhs[3][1];
			m_data[3][2] -= rhs[3][2];
			m_data[3][3] -= rhs[3][3];

			return *this;
		}


	private:

		T m_data[4][4] = {};
	};

	using Mat4x4i = Mat4x4<int>;
	using Mat4x4f = Mat4x4<float>;
	using Mat4x4u = Mat4x4<unsigned int>;


	template <class T>
	inline Mat4x4<T> operator+(Mat4x4<T> lhs, const Mat4x4<T>& rhs)
	{
		lhs += rhs;
		return lhs;
	}

	template <class T>
	inline Mat4x4<T> operator-(Mat4x4<T> lhs, const Mat4x4<T>& rhs)
	{
		lhs -= rhs;
		return lhs;
	}

}
