#pragma once


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
	inline Vec2<T> operator+(Vec2<T> lhs, const Vec2<T>& rhs)
	{
		lhs += rhs;
		return lhs;
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
	inline Vec2<T> operator-(Vec2<T> lhs, const Vec2<T>& rhs)
	{
		lhs -= rhs;
		return lhs;
	}

}
