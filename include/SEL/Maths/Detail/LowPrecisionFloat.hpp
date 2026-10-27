#pragma once

#include <cmath>
#include <limits>
#include <ostream>
#include <type_traits>

namespace sel::utils {

	/// @brief OCP element encodings with saturating, nearest-even conversions.
	/// Arithmetic rounds through FP32; raw construction preserves special encodings.
	/// Numeric conversion uses nearest-even rounding, gradual underflow, and signed
	/// zero. Overflow and infinities saturate; FP8 NaNs become canonical NaNs and
	/// FP4 NaNs become positive zero. Each standalone value occupies one byte.
	/// @tparam ExponentBits Exponent field width: 2, 4, or 5.
	/// @tparam MantissaBits Trailing significand width: 1, 3, or 2 respectively.
	template <unsigned int ExponentBits, unsigned int MantissaBits>
	class LowPrecisionFloat
	{
		static_assert((ExponentBits == 2 && MantissaBits == 1)
			|| (ExponentBits == 4 && MantissaBits == 3)
			|| (ExponentBits == 5 && MantissaBits == 2), "Unsupported OCP element format");
		static constexpr unsigned int signMask = 1u << (ExponentBits + MantissaBits);
		static constexpr unsigned int exponentMask = (1u << ExponentBits) - 1u;
		static constexpr unsigned int mantissaMask = (1u << MantissaBits) - 1u;
		static constexpr bool isFp4 = ExponentBits == 2 && MantissaBits == 1;
		static constexpr bool isE4M3 = ExponentBits == 4 && MantissaBits == 3;
		static constexpr unsigned int maxFinite = isFp4 ? 7u : (isE4M3 ? 126u : 123u);
	public:
		/// @brief Packed element proxy, defined for the FP4 matrix specialization.
		class reference;

		/// @brief Construct positive zero.
		constexpr LowPrecisionFloat() = default;

		/// @brief Quantize directly from the source precision, without FP32 narrowing.
		/// Overflow/infinity saturate; NaN becomes canonical FP8 NaN or FP4 +0.
		/// @tparam Number A built-in arithmetic type.
		/// @param value Numeric value to round to the nearest representable value;
		/// halfway cases select the encoding with an even significand.
		template <class Number, std::enable_if_t<std::is_arithmetic_v<Number>, int> = 0>
		LowPrecisionFloat(Number value) : m_bits(encode(static_cast<long double>(value))) {}

		/// @brief Construct from an encoding, bypassing numeric conversion.
		/// @param bits All eight bits for FP8, or the low four bits for FP4.
		/// @return A value preserving the selected bits, including FP8 NaNs and
		/// E5M2 infinities. FP4's unused high nibble is discarded.
		static constexpr LowPrecisionFloat fromBits(unsigned char bits)
		{
			LowPrecisionFloat result;
			result.m_bits = bits & (2u * signMask - 1u);
			return result;
		}

		/// @brief Return the encoding; the high nibble is zero for FP4.
		constexpr unsigned char bits() const { return m_bits; }

		/// @brief Decode to FP32, preserving finite values and signed zero exactly.
		/// Raw E5M2 infinities decode to infinities and FP8 NaNs to quiet NaNs;
		/// NaN payload preservation is not guaranteed.
		constexpr float value() const
		{
			const unsigned int magnitude = m_bits & (signMask - 1u);
			const unsigned int exponent = magnitude >> MantissaBits;
			const unsigned int mantissa = magnitude & mantissaMask;
			float result = 0;
			if (!isFp4 && exponent == exponentMask
				&& (!isE4M3 || mantissa == mantissaMask))
			{
				result = (!isE4M3 && mantissa == 0)
					? std::numeric_limits<float>::infinity()
					: std::numeric_limits<float>::quiet_NaN();
			}
			else
			{
				const int bias = int((1u << (ExponentBits - 1)) - 1u);
				int power = (exponent ? int(exponent) : 1) - bias - int(MantissaBits);
				result = float(mantissa + (exponent ? (1u << MantissaBits) : 0u));
				while (power > 0) { result *= 2; --power; }
				while (power < 0) { result *= 0.5f; ++power; }
			}
			return m_bits & signMask ? -result : result;
		}

		/// @brief Decode explicitly to FP32, with the same behavior as value().
		constexpr explicit operator float() const { return value(); }
		/// @brief Return a copy with the original encoding.
		constexpr LowPrecisionFloat operator+() const { return *this; }
		/// @brief Flip the raw sign bit, including for zeros, infinities, and NaNs.
		constexpr LowPrecisionFloat operator-() const { return fromBits(m_bits ^ signMask); }

		/// @brief Add in FP32, then round and saturate the stored result.
		LowPrecisionFloat& operator+=(LowPrecisionFloat rhs) { return *this = arithmetic(value() + rhs.value()); }
		/// @brief Subtract in FP32, then round and saturate the stored result.
		LowPrecisionFloat& operator-=(LowPrecisionFloat rhs) { return *this = arithmetic(value() - rhs.value()); }
		/// @brief Multiply in FP32, then round and saturate the stored result.
		LowPrecisionFloat& operator*=(LowPrecisionFloat rhs) { return *this = arithmetic(value() * rhs.value()); }
		/// @brief Divide in FP32, then convert using the infinity/NaN policies.
		LowPrecisionFloat& operator/=(LowPrecisionFloat rhs) { return *this = arithmetic(value() / rhs.value()); }

		/// @brief Return the FP32 sum rounded and saturated to this format.
		friend LowPrecisionFloat operator+(LowPrecisionFloat lhs, LowPrecisionFloat rhs) { return lhs += rhs; }
		/// @brief Return the FP32 difference rounded and saturated to this format.
		friend LowPrecisionFloat operator-(LowPrecisionFloat lhs, LowPrecisionFloat rhs) { return lhs -= rhs; }
		/// @brief Return the FP32 product rounded and saturated to this format.
		friend LowPrecisionFloat operator*(LowPrecisionFloat lhs, LowPrecisionFloat rhs) { return lhs *= rhs; }
		/// @brief Return the FP32 quotient using the infinity/NaN conversion policies.
		friend LowPrecisionFloat operator/(LowPrecisionFloat lhs, LowPrecisionFloat rhs) { return lhs /= rhs; }
		/// @brief Compare decoded values for equality; NaNs compare unequal.
		friend constexpr bool operator==(LowPrecisionFloat lhs, LowPrecisionFloat rhs) { return lhs.value() == rhs.value(); }
		/// @brief Compare decoded values for inequality; NaNs compare unequal.
		friend constexpr bool operator!=(LowPrecisionFloat lhs, LowPrecisionFloat rhs) { return lhs.value() != rhs.value(); }
		/// @brief Compare decoded values for less-than; false for unordered NaNs.
		friend constexpr bool operator<(LowPrecisionFloat lhs, LowPrecisionFloat rhs) { return lhs.value() < rhs.value(); }
		/// @brief Compare decoded values for greater-than; false for unordered NaNs.
		friend constexpr bool operator>(LowPrecisionFloat lhs, LowPrecisionFloat rhs) { return lhs.value() > rhs.value(); }
		/// @brief Compare decoded values for less-or-equal; false for unordered NaNs.
		friend constexpr bool operator<=(LowPrecisionFloat lhs, LowPrecisionFloat rhs) { return lhs.value() <= rhs.value(); }
		/// @brief Compare decoded values for greater-or-equal; false for unordered NaNs.
		friend constexpr bool operator>=(LowPrecisionFloat lhs, LowPrecisionFloat rhs) { return lhs.value() >= rhs.value(); }
		/// @brief Print the decoded FP32 value using the stream's floating-point formatting.
		/// @return The original stream for chaining.
		friend std::ostream& operator<<(std::ostream& stream, LowPrecisionFloat value) { return stream << value.value(); }

	private:
		static LowPrecisionFloat arithmetic(float value)
		{
			// Force the specified FP32 rounding even on excess-precision targets.
			volatile float rounded = value;
			return LowPrecisionFloat(rounded);
		}

		static unsigned char encode(long double value)
		{
			if (std::isnan(value)) return isFp4 ? 0u : (isE4M3 ? 127u : 126u);
			const unsigned int sign = std::signbit(value) ? signMask : 0u;
			const long double magnitude = std::fabs(value);
			if (magnitude >= fromBits(maxFinite).value()) return sign | maxFinite;

			// Positive finite encodings are ordered. Locate adjacent values, then
			// compare exact dyadic midpoints in the original source precision.
			unsigned int lower = 0, upper = maxFinite;
			while (upper - lower > 1)
			{
				const unsigned int middle = (lower + upper) / 2;
				if (fromBits(middle).value() <= magnitude) lower = middle;
				else upper = middle;
			}
			const long double midpoint = (static_cast<long double>(fromBits(lower).value())
				+ fromBits(upper).value()) / 2;
			const unsigned int rounded = magnitude < midpoint ? lower
				: magnitude > midpoint ? upper : (lower % 2 == 0 ? lower : upper);
			return static_cast<unsigned char>(sign | rounded);
		}

		unsigned char m_bits = 0;
	};

	/// @brief Identify the three supported low-precision wrapper types for dispatch.
	template <class T> inline constexpr bool isLowPrecisionFloat = false;
	template <unsigned int E, unsigned int M>
	inline constexpr bool isLowPrecisionFloat<LowPrecisionFloat<E, M>> = true;

	static_assert(std::numeric_limits<float>::is_iec559 && std::numeric_limits<float>::digits == 24
		&& sizeof(float) == 4, "Low-precision arithmetic requires IEEE binary32 float");
}
