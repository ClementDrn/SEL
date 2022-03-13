#pragma once


namespace sel {

	template <class T>
	struct Vec3
	{
	public:

		union
		{
			T x;
			T r;
		} = 0;

		union
		{
			T y;
			T g;
		} = 0;

		union
		{
			T z;
			T b;
		} = 0;

		Vec3(T x, T y, T z)
			: x(x), y(y), z(z) {}

		Vec3& operator+=(const Vec3& rhs)
		{
			x += rhs.x;
			y += rhs.y;
			z += rhs.z;
			return *this;
		}

		Vec3& operator-=(const Vec3& rhs)
		{
			x -= rhs.x;
			y -= rhs.y;
			z -= rhs.z;
			return *this;
		}

	};

	using Vec3i = Vec3<int>;
	using Vec3u = Vec3<unsigned int>;
	using Vec3f = Vec3<float>;



	template <class T>
	inline bool operator==(const Vec3<T>& lhs, const Vec3<T>& rhs)
	{
		return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z;
	}

	template <class T>
	inline bool operator!=(const Vec3<T>& lhs, const Vec3<T>& rhs)
	{ 
		return !(lhs == rhs); 
	}


	template <class T>
	inline Vec3<T> operator+(Vec3<T> lhs, const Vec3<T>& rhs)
	{
		lhs += rhs;
		return lhs;
	}

	template <class T>
	inline Vec3<T> operator-(Vec3<T> lhs, const Vec3<T>& rhs)
	{
		lhs -= rhs;
		return lhs;
	}

}
