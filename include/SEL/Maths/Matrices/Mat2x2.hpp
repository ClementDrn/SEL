#pragma once


namespace sel {

	template <typename T>
	class Mat2x2
	{
	public:

		Mat2x2() = default;


		T* operator[](size_t idx) { return m_data[idx]; }
		const T* operator[](size_t idx) const { return m_data[idx]; }


		Mat2x2& operator+=(const Mat2x2& rhs)
		{
			m_data[0][0] += rhs[0][0];
			m_data[0][1] += rhs[0][1];

			m_data[1][0] += rhs[1][0];
			m_data[1][1] += rhs[1][1];

			return *this;
		}

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

	using Mat2x2i = Mat2x2<int>;
	using Mat2x2f = Mat2x2<float>;
	using Mat2x2u = Mat2x2<unsigned int>;


	template <class T>
	inline Mat2x2<T> operator+(Mat2x2<T> lhs, const Mat2x2<T>& rhs)
	{
		lhs += rhs;
		return lhs;
	}

	template <class T>
	inline Mat2x2<T> operator-(Mat2x2<T> lhs, const Mat2x2<T>& rhs)
	{
		lhs -= rhs;
		return lhs;
	}

}
