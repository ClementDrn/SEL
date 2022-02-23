#pragma once


namespace sel {

	template <class T>
	struct Vec2
	{
	public:

		T x = 0;
		T y = 0;

		Vec2(T x, T y)
			: x(x), y(y) {}

		Vec2& operator+=(const Vec2& rhs)
		{
			x += rhs.x;
			y += rhs.y;
			return *this;
		}

		Vec2& operator-=(const Vec2& rhs)
		{
			x -= rhs.x;
			y -= rhs.y;
			return *this;
		}

	};

	using Vec2i = Vec2<int>;
	using Vec2u = Vec2<unsigned int>;
	using Vec2f = Vec2<float>;



	template <class T>
	inline bool operator==(const Vec2<T>& lhs, const Vec2<T>& rhs)
	{
		return lhs.x == rhs.x && lhs.y == rhs.y;
	}

	template <class T>
	inline bool operator!=(const Vec2<T>& lhs, const Vec2<T>& rhs) { return !(lhs == rhs); }


	template <class T>
	inline Vec2<T> operator+(Vec2<T> lhs, const Vec2<T>& rhs)
	{
		lhs += rhs;
		return lhs;
	}

	template <class T>
	inline Vec2<T> operator-(Vec2<T> lhs, const Vec2<T>& rhs)
	{
		lhs -= rhs;
		return lhs;
	}

}
