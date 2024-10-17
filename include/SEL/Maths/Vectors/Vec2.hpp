#pragma once

#include <cmath>


namespace sel {

	/// @brief Data structure that describes a vector with 2 coordinates.
	/// 
	/// @tparam T is the type of the coordinates.
	///  
	template <class T>
	struct Vec2
	{
	public:

		T x = 0;		///< The x coordinate.
		T y = 0;		///< The y coordinate.

		/// @brief Default constructor.
		///
		/// Gives default values to coordinates.
		/// 
		Vec2() = default;

		/// @brief Constructor allowing to specify values for coordinates.
		/// 
		/// @param x is the value for the x coordinate.
		/// @param y is the value for the y coordinate.
		/// 
		Vec2(T x, T y)
			: x(x), y(y) {}

		/// @brief Overload of += binary arithmetic operator.
		/// 
		/// The other vector's coordinates are added to the instance's coordinates.
		/// 
		/// @param rhs is the vector in which the coordinates must be added to the instance's coordinates.
		/// 
		/// @return The reference to the updated vector.
		/// 
		Vec2& operator+=(const Vec2& rhs)
		{
			x += rhs.x;
			y += rhs.y;
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
		Vec2& operator-=(const Vec2& rhs)
		{
			x -= rhs.x;
			y -= rhs.y;
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
		Vec2& operator*=(float rhs)
		{
			x *= rhs;
			y *= rhs;
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
		Vec2& operator/=(float rhs)
		{
			x /= rhs;
			y /= rhs;
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
		Vec2& operator*=(const Vec2& rhs)
		{
			x *= rhs.x;
			y *= rhs.y;
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
		Vec2& operator/=(const Vec2& rhs)
		{
			x /= rhs.x;
			y /= rhs.y;
			return *this;
		}

		/// @brief Calculates the length of the vector.
		/// 
		/// @return The length of the vector.
		/// 
		T length() const
		{
			return std::sqrt(x * x + y * y);
		}

		/// @brief Calculates the squared length of the vector.
		/// 
		/// This function is faster that the length() function as it does not perform a square root operation.
		/// 
		/// @return The squared length of the vector.
		/// 
		T lengthSquared() const
		{
			return x * x + y * y;
		}

		/// @brief Normalizes the vector.
		/// 
		/// The vector is scaled to have a length of 1.
		/// 
		void normalize()
		{
			T len = length();
			if (len != 0)
			{
				x /= len;
				y /= len;
			}
		}

	};

	/// @brief Data structure that describes a vector with 2 integer coordinates.
	///
	using Vec2i = Vec2<int>;
	
	/// @brief Data structure that describes a vector with 2 unsigned integer coordinates.
	///
	using Vec2u = Vec2<unsigned int>;
	
	/// @brief Data structure that describes a vector with 2 float coordinates.
	///
	using Vec2f = Vec2<float>;


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
	inline bool operator==(const Vec2<T>& lhs, const Vec2<T>& rhs)
	{
		return lhs.x == rhs.x && lhs.y == rhs.y;
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
	inline bool operator!=(const Vec2<T>& lhs, const Vec2<T>& rhs) 
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
	inline Vec2<T> operator+(const Vec2<T>& lhs, const Vec2<T>& rhs)
	{
		return { lhs.x + rhs.x, lhs.y + rhs.y };
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
	inline Vec2<T> operator-(const Vec2<T>& lhs, const Vec2<T>& rhs)
	{
		return { lhs.x - rhs.x, lhs.y - rhs.y };
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
	inline Vec2<T> operator*(const Vec2<T>& lhs, float rhs)
	{
		return { lhs.x * rhs, lhs.y * rhs };
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
	inline Vec2<T> operator*(float lhs, const Vec2<T>& rhs)
	{
		return { lhs * rhs.x, lhs * rhs.y };
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
	inline Vec2<T> operator*(const Vec2<T>& lhs, const Vec2<T>& rhs)
	{
		return { lhs.x * rhs.x, lhs.y * rhs.y };
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
	inline Vec2<T> operator/(const Vec2<T>& lhs, const Vec2<T>& rhs)
	{
		return { lhs.x / rhs.x, lhs.y / rhs.y };
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
	float dot(const Vec2<T>& u, const Vec2<T>& v)
	{
		return u.x * v.x + u.y * v.y;
	}

	/// @brief Calculates the cross product of 2D vectors
	/// 
	/// @tparam T is the type of the vectors' coordinates. 
	/// @param u is the first 2D vector.
	/// @param v is the second 2D vector.
	/// 
	/// @return The cross product of the two provided vectors.
	/// 
	template <class T>
	float cross(const Vec2<T>& u, const Vec2<T>& v)
	{
		return u.x * v.y - u.y * v.x;
	}

	/// @brief Calculates the normalized version of a given vector.
	///
	/// @tparam T is the type of the vector's coordinates.
	/// @param vec is the vector to be normalized.
	///
	/// @return The normalized version of the input vector.
	/// 
	template <class T>
	Vec2<T> normalize(const Vec2<T>& vec)
	{
		Vec2<T> copy = vec;
		copy.normalize();
		return copy;
	}

}
