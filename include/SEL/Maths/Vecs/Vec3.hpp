#pragma once

#include <cmath>


namespace sel {

	/// @brief Data structure that describes a vector with 3 coordinates.
	/// 
	/// @tparam T is the type of the coordinates.
	///  
	template <class T>
	struct Vec3
	{
	public:

		union
		{
			T x = 0;		///< The x (first) coordinate.
			T r;			///< The r (first) coordinate.
		};

		union
		{
			T y = 0;		///< The y (second) coordinate.
			T g;			///< The g (second) coordinate.
		};

		union
		{
			T z = 0;		///< The z (third) coordinate.
			T b;			///< The b (third) coordinate.
		};

		/// @brief Default constructor.
		///
		/// Gives default values to coordinates.
		/// 
		Vec3() = default;

		/// @brief Constructor allowing to specify values for coordinates.
		/// 
		/// @param x is the value for the x (first) coordinate.
		/// @param y is the value for the y (second) coordinate.
		/// @param z is the value for the z (third) coordinate.
		/// 
		Vec3(T x, T y, T z)
			: x(x), y(y), z(z) {}

		/// @brief Overload of += binary arithmetic operator.
		/// 
		/// The other vector's coordinates are added to the instance's coordinates.
		/// 
		/// @param rhs is the vector in which the coordinates must be added to the instance's coordinates.
		/// 
		/// @return The reference to the updated vector.
		/// 
		Vec3& operator+=(const Vec3& rhs)
		{
			x += rhs.x;
			y += rhs.y;
			z += rhs.z;
			return *this;
		}

		/// @brief Overload of -= binary arithmetic operator.
		/// 
		/// The instance's coordinates are substracted by the other vector's coordinates.
		///
		/// @param rhs is the vector in which the coordinates must substract the instance's coordinates.
		/// 
		/// @return The reference to the updated vector.
		///	
		Vec3& operator-=(const Vec3& rhs)
		{
			x -= rhs.x;
			y -= rhs.y;
			z -= rhs.z;
			return *this;
		}

		/// @brief Overload of *= binary arithmetic operator.
		///
		/// The instance's coordinates are multiplied by the provided scalar.
		/// 
		/// @param rhs is the value by which the coordinates must be multiplied.
		/// 
		/// @return The reference to the updated vector.
		///
		Vec3& operator*=(float rhs)
		{
			x *= rhs;
			y *= rhs;
			z *= rhs;
			return *this;
		}

		/// @brief Overload of /= binary arithmetic operator.
		///
		/// The instance's coordinates are divided by the provided scalar.
		/// 
		/// @param rhs is the value by which the coordinates must be divided.
		/// 
		/// @return The reference to the updated vector.
		/// 
		Vec3& operator/=(float rhs)
		{
			x /= rhs;
			y /= rhs;
			z /= rhs;
			return *this;
		}

		/// @brief Overlaod of *= binary arithmetic operator.
		/// 
		/// The instance's coordinates are multiplied by the other vector's coordinates.
		/// 
		/// @param rhs is the vector in which the coordinates must be multiplied by the instance's coordinates.
		/// 
		/// @return The reference to the updated vector.
		/// 
		Vec3& operator*=(const Vec3& rhs)
		{
			x *= rhs.x;
			y *= rhs.y;
			z *= rhs.z;
			return *this;
		}

		/// @brief Overload of /= binary arithmetic operator.
		///
		/// The instance's coordinates are divided by the other vector's coordinates.
		/// 
		/// @param rhs is the vector in which the coordinates must be divided by the instance's coordinates.
		/// 
		/// @return The reference to the updated vector.
		/// 
		Vec3& operator/=(const Vec3& rhs)
		{
			x /= rhs.x;
			y /= rhs.y;
			z /= rhs.z;
			return *this;
		}

	};

	/// @brief Data structure that describes a vector with 3 integer coordinates.
	///
	using Vec3i = Vec3<int>;
	
	/// @brief Data structure that describes a vector with 3 unsigned integer coordinates.
	///
	using Vec3u = Vec3<unsigned int>;
	
	/// @brief Data structure that describes a vector with 3 float coordinates.
	///
	using Vec3f = Vec3<float>;


	/// @brief Overload of the == comparison operator.
	/// 
	/// The comparison returns true if both vectors are equal, which means that their coordinates are the same.
	/// 
	/// @tparam T is the type of the vector's coordinates.
	/// @param lhs is the first vector.
	/// @param rhs is the second vector.
	/// 
	/// @return The test result.
	/// 
	template <class T>
	inline bool operator==(const Vec3<T>& lhs, const Vec3<T>& rhs)
	{
		return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z;
	}

	/// @brief Overload of the != comparison operator.
	/// 
	/// The comparison returns true if both vectors are not equal, which means that their coordinates are not the same.
	/// 
	/// @tparam T is the type of the vector's coordinates.
	/// @param lhs is the first vector.
	/// @param rhs is the second vector.
	/// 
	/// @return The test result.
	/// 
	template <class T>
	inline bool operator!=(const Vec3<T>& lhs, const Vec3<T>& rhs)
	{ 
		return !(lhs == rhs); 
	}

	/// @brief Overload of + binary arithmetic operator.
	/// 
	/// @tparam T is the type of the vectors's coordinates.
	/// @param lhs is the first vector.
	/// @param rhs is the second vector.
	/// 
	/// @return The vector resulted by the addition of the two provided vectors.
	/// 
	template <class T>
	inline Vec3<T> operator+(const Vec3<T>& lhs, const Vec3<T>& rhs)
	{
		return { lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z };
	}

	/// @brief Overload of - binary arithmetic operator.
	/// 
	/// @tparam T is the type of the vectors' coordinates.
	/// @param lhs is the first vector.
	/// @param rhs is the second vector.
	/// 
	/// @return The vector resulted by the difference between the two provided vectors.
	/// 
	template <class T>
	inline Vec3<T> operator-(const Vec3<T>& lhs, const Vec3<T>& rhs)
	{
		return { lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z };
	}

	/// @brief Overload of * binary arithmetic operator.
	///
	/// @tparam T is the type of the vector's coordinates.
	/// @param lhs is the vector.
	/// @param rhs is the scalar.
	/// 
	/// @return The vector resulted by the multiplication of the vector by the scalar.
	/// 
	template <class T>
	inline Vec3<T> operator*(const Vec3<T>& lhs, float rhs)
	{
		return { lhs.x * rhs, lhs.y * rhs, lhs.z * rhs };
	}

	/// @brief Overload of * binary arithmetic operator.
	///
	/// @tparam T is the type of the vector's coordinates.
	/// @param lhs is the scalar.
	/// @param rhs is the vector.
	/// 
	/// @return The vector resulted by the multiplication of the vector by the scalar.
	/// 
	template <class T>
	inline Vec3<T> operator*(float lhs, const Vec3<T>& rhs)
	{
		return { lhs * rhs.x, lhs * rhs.y, lhs * rhs.z };
	}

	/// @brief Overload of * binary arithmetic operator.
	///
	/// @tparam T is the type of the vectors' coordinates.
	/// @param lhs is the first vector.
	/// @param rhs is the second vector.
	/// 
	/// @return The vector resulted by the multiplication of the two provided vectors.
	/// 
	template <class T>
	inline Vec3<T> operator*(const Vec3<T>& lhs, const Vec3<T>& rhs)
	{
		return { lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z };
	}

	/// @brief Overload of / binary arithmetic operator.
	///
	/// @tparam T is the type of the vectors' coordinates.
	/// @param lhs is the first vector.
	/// @param rhs is the second vector.
	/// 
	/// @return The vector resulted by the division of the two provided vectors.
	/// 
	template <class T>
	inline Vec3<T> operator/(const Vec3<T>& lhs, const Vec3<T>& rhs)
	{
		return { lhs.x / rhs.x, lhs.y / rhs.y, lhs.z / rhs.z };
	}
	
	/// @brief Function that returns the dot product of two vectors.
	/// 
	/// @tparam T is the type of the vectors' coordinates.
	/// @param u is the first vector.
	/// @param v is the second vector.
	/// 
	/// @return The dot product of the two provided vectors.
	/// 
	template <class T>
	float dot(const Vec3<T>& u, const Vec3<T>& v)
	{
		return u.x * v.x + u.y * v.y + u.z * v.z;
	}

	/// @brief Calculates the normalized version of a given vector.
	///
	/// @tparam T is the type of the vector's coordinates.
	/// @param vec is the vector to be normalized.
	///
	/// @return The normalized version of the input vector.
	/// 
	template <class T>
	Vec3<T> normalize(const Vec3<T>& vec)
	{
		T length = std::sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
		return { vec.x / length, vec.y / length, vec.z / length };
	}

}
