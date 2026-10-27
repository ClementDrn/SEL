#pragma once

#include <type_traits>

namespace sel {

	/// @brief Signed four-bit value with modulo-16 wrapping arithmetic.
	/// Standalone values occupy one byte; int4 matrices pack two values per byte.
	class int4
	{
	public:
		class reference;

		constexpr int4() = default;

		/// @brief Retain the low four bits of an integer, without saturation.
		template <class Integer, std::enable_if_t<std::is_integral_v<Integer>, int> = 0>
		constexpr int4(Integer value)
			: m_bits(static_cast<unsigned char>(value) & 0x0fu) {}

		constexpr int value() const
		{
			return m_bits < 8 ? int(m_bits) : int(m_bits) - 16;
		}

		constexpr explicit operator int() const { return value(); }

		constexpr int4& operator+=(int4 rhs) { return *this = int4(value() + rhs.value()); }
		constexpr int4& operator-=(int4 rhs) { return *this = int4(value() - rhs.value()); }
		constexpr int4& operator*=(int4 rhs) { return *this = int4(value() * rhs.value()); }

		constexpr int4 operator+() const { return *this; }
		constexpr int4 operator-() const { return int4(-value()); }

		friend constexpr int4 operator+(int4 lhs, int4 rhs) { return lhs += rhs; }
		friend constexpr int4 operator-(int4 lhs, int4 rhs) { return lhs -= rhs; }
		friend constexpr int4 operator*(int4 lhs, int4 rhs) { return lhs *= rhs; }

		friend constexpr bool operator==(int4 lhs, int4 rhs) { return lhs.value() == rhs.value(); }
		friend constexpr bool operator!=(int4 lhs, int4 rhs) { return !(lhs == rhs); }
		friend constexpr bool operator<(int4 lhs, int4 rhs) { return lhs.value() < rhs.value(); }
		friend constexpr bool operator>(int4 lhs, int4 rhs) { return rhs < lhs; }
		friend constexpr bool operator<=(int4 lhs, int4 rhs) { return !(rhs < lhs); }
		friend constexpr bool operator>=(int4 lhs, int4 rhs) { return !(lhs < rhs); }

	private:
		unsigned char m_bits = 0;
	};

}
