#pragma once

#include <cstddef>
#include <type_traits>

#include "SEL/Maths/Float4E2M1.hpp"

namespace sel::utils {

	/// @brief Borrowed reference to one FP4 nibble in a matrix storage byte.
	/// Copy construction aliases the element; assignment copies the element value.
	/// The backing matrix storage must outlive the proxy. Arithmetic and comparisons
	/// use Float4E2M1 semantics; writes preserve the neighboring nibble.
	template <>
	class LowPrecisionFloat<2, 1>::reference
	{
	public:
		/// @brief Refer to a nibble in an existing byte.
		/// @param byte Backing storage byte, which must outlive this proxy.
		/// @param shift Nibble offset in bits: 0 for the low nibble, 4 for the high.
		reference(unsigned char& byte, unsigned int shift)
			: m_byte(&byte), m_shift(shift) {}
		/// @brief Copy the reference, retaining its association with the same element.
		reference(const reference&) = default;

		/// @brief Read the current nibble as an independent wrapper value.
		operator Float4E2M1() const { return Float4E2M1::fromBits((*m_byte >> m_shift) & 0x0fu); }
		/// @brief Decode the current nibble to FP32.
		explicit operator float() const { return Float4E2M1(*this).value(); }
		/// @brief Read a value snapshot with the original encoding.
		Float4E2M1 operator+() const { return Float4E2M1(*this); }
		/// @brief Read a value snapshot with its raw sign bit flipped.
		Float4E2M1 operator-() const { return -Float4E2M1(*this); }

		/// @brief Store an encoding without changing the neighboring nibble.
		reference& operator=(Float4E2M1 value)
		{
			// Mask only this nibble so the adjacent element remains intact.
			const unsigned int bits = value.bits();
			*m_byte = static_cast<unsigned char>((*m_byte & ~(0x0fu << m_shift)) | (bits << m_shift));
			return *this;
		}

		/// @brief Copy the other element's value without rebinding this proxy.
		reference& operator=(const reference& other) { return *this = Float4E2M1(other); }
		/// @brief Add in FP32 and store the rounded, saturated FP4 result.
		reference& operator+=(Float4E2M1 rhs) { return *this = Float4E2M1(*this) + rhs; }
		/// @brief Subtract in FP32 and store the rounded, saturated FP4 result.
		reference& operator-=(Float4E2M1 rhs) { return *this = Float4E2M1(*this) - rhs; }
		/// @brief Multiply in FP32 and store the rounded, saturated FP4 result.
		reference& operator*=(Float4E2M1 rhs) { return *this = Float4E2M1(*this) * rhs; }
		/// @brief Divide in FP32 and store FP4; infinities saturate and NaNs become +0.
		reference& operator/=(Float4E2M1 rhs) { return *this = Float4E2M1(*this) / rhs; }
		/// @brief Decode the current element to FP32.
		float value() const { return Float4E2M1(*this).value(); }
		/// @brief Return the current four-bit encoding in the low nibble.
		unsigned char bits() const { return Float4E2M1(*this).bits(); }

	private:
		unsigned char* m_byte;
		unsigned int m_shift;
	};


	/// @brief Shared packed storage and operations for FP4 matrices.
	/// Elements use row-major order, with even indices in the low nibble.
	/// Storage occupies (Rows * Columns + 1) / 2 bytes with no padding between
	/// rows; an unused final high nibble remains zero.
	/// @tparam Rows Number of rows in the derived matrix.
	/// @tparam Columns Number of columns in the derived matrix.
	/// @tparam Matrix Derived matrix type returned by arithmetic and identity().
	template <std::size_t Rows, std::size_t Columns, class Matrix>
	class PackedFloat4Matrix
	{
	public:
		/// @brief Initialize all elements and any unused padding nibble to positive zero.
		PackedFloat4Matrix() = default;

		/// @brief Set the diagonal to scalar and all other elements to positive zero.
		/// @param scalar Value for each existing diagonal element.
		PackedFloat4Matrix(Float4E2M1 scalar)
		{
			for (std::size_t index = 0; index < Rows && index < Columns; ++index)
			{
				(*this)[index][index] = scalar;
			}
		}

		/// @brief Initialize exactly Rows * Columns values in row-major order.
		/// @param values Numeric or wrapper values converted individually to FP4.
		template <class... Values, std::enable_if_t<sizeof...(Values) == Rows * Columns
			&& (std::is_convertible_v<Values, Float4E2M1> && ...), int> = 0>
		PackedFloat4Matrix(Values... values)
		{
			const Float4E2M1 elements[] = { Float4E2M1(values)... };
			for (std::size_t index = 0; index < Rows * Columns; ++index)
			{
				element(index) = elements[index];
			}
		}

		/// @brief Return diagonal ones and zero elsewhere, including rectangular shapes.
		static Matrix identity() { return Matrix(Float4E2M1(1)); }

		/// @brief Mutable row view; indexing returns a borrowed element proxy.
		class Row
		{
		public:
			/// @brief Refer to a row starting at the given linear element offset.
			Row(PackedFloat4Matrix& matrix, std::size_t offset)
				: m_matrix(matrix), m_offset(offset) {}
			/// @brief Return an unchecked proxy to the selected column.
			Float4E2M1::reference operator[](std::size_t column) const
			{
				return m_matrix.element(m_offset + column);
			}
		private:
			PackedFloat4Matrix& m_matrix;
			std::size_t m_offset;
		};

		/// @brief Read-only row view; indexing returns an independent wrapper value.
		class ConstRow
		{
		public:
			/// @brief Refer to a row starting at the given linear element offset.
			ConstRow(const PackedFloat4Matrix& matrix, std::size_t offset)
				: m_matrix(matrix), m_offset(offset) {}
			/// @brief Read an unchecked column as a wrapper value.
			Float4E2M1 operator[](std::size_t column) const
			{
				return m_matrix.element(m_offset + column);
			}
		private:
			const PackedFloat4Matrix& m_matrix;
			std::size_t m_offset;
		};

		/// @brief Return an unchecked mutable row view; elements are proxies, not pointers.
		Row operator[](std::size_t row) { return Row(*this, row * Columns); }
		/// @brief Return an unchecked read-only row view whose elements are values.
		ConstRow operator[](std::size_t row) const { return ConstRow(*this, row * Columns); }

		/// @brief Add element by element, rounding and saturating each FP4 result.
		/// @return The derived matrix for chaining.
		Matrix& operator+=(const Matrix& rhs)
		{
			for (std::size_t row = 0; row < Rows; ++row)
			{
				for (std::size_t column = 0; column < Columns; ++column)
				{
					(*this)[row][column] += rhs[row][column];
				}
			}
			return static_cast<Matrix&>(*this);
		}

		/// @brief Subtract element by element, rounding and saturating each FP4 result.
		/// @return The derived matrix for chaining.
		Matrix& operator-=(const Matrix& rhs)
		{
			for (std::size_t row = 0; row < Rows; ++row)
			{
				for (std::size_t column = 0; column < Columns; ++column)
				{
					(*this)[row][column] -= rhs[row][column];
				}
			}
			return static_cast<Matrix&>(*this);
		}

	private:
		Float4E2M1::reference element(std::size_t index)
		{
			return Float4E2M1::reference(m_data[index / 2], static_cast<unsigned int>(index % 2) * 4);
		}

		Float4E2M1 element(std::size_t index) const
		{
			return Float4E2M1::fromBits((m_data[index / 2] >> ((index % 2) * 4)) & 0x0fu);
		}

		// No padding between rows; an unused final high nibble stays zero.
		unsigned char m_data[(Rows * Columns + 1) / 2] = {};
	};

}
