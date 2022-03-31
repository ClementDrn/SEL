#pragma once


namespace sel {

	/// @brief Data structure that describes a vector with 4 coordinates.
	/// 
	/// @tparam T is the type of the coordinates.
	///  
	template <class T>
	struct Vec4
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

		union
		{
			T w = 0;		///< The w (fourth) coordinate.
			T a;			///< The a (fourth) coordinate.
		};

		/// @brief Default constructor.
		///
		/// Gives default values to coordinates.
		/// 
		Vec4() = default;

		/// @brief Constructor allowing to specify values for coordinates.
		/// 
		/// @param x is the value for the x (first) coordinate.
		/// @param y is the value for the y (second) coordinate.
		/// @param z is the value for the z (third) coordinate.
		/// @param w is the value for the w (fourth) coordinate.
		/// 
		Vec4(T x, T y, T z, T w)
			: x(x), y(y), z(z), w(w) {}

		/// @brief Overload of += binary arithmetic operator.
		/// 
		/// The other vector's coordinates are added to the instance's coordinates.
		/// 
		/// @param rhs is the vector in which the coordinates must be added to the instance's coordinates.
		/// 
		/// @return The reference to the updated vector.
		/// 
		Vec4& operator+=(const Vec4& rhs)
		{
			x += rhs.x;
			y += rhs.y;
			z += rhs.z;
			w += rhs.w;
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
		Vec4& operator-=(const Vec4& rhs)
		{
			x -= rhs.x;
			y -= rhs.y;
			z -= rhs.z;
			w -= rhs.w;
			return *this;
		}

	};

	/// @brief Data structure that describes a vector with 4 integer coordinates.
	///
	using Vec4i = Vec4<int>;

	/// @brief Data structure that describes a vector with 4 unsigned integer coordinates.
	///
	using Vec4u = Vec4<unsigned int>;

	/// @brief Data structure that describes a vector with 4 float coordinates.
	///
	using Vec4f = Vec4<float>;


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
	inline bool operator==(const Vec4<T>& lhs, const Vec4<T>& rhs)
	{
		return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z && lhs.w == rhs.w;
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
	inline bool operator!=(const Vec4<T>& lhs, const Vec4<T>& rhs)
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
	inline Vec4<T> operator+(Vec4<T> lhs, const Vec4<T>& rhs)
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
	inline Vec4<T> operator-(Vec4<T> lhs, const Vec4<T>& rhs)
	{
		lhs -= rhs;
		return lhs;
	}

}
