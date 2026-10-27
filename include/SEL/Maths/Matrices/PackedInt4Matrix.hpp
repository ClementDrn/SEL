#pragma once

#include <cstddef>
#include <type_traits>

#include "SEL/Maths/Int4.hpp"

namespace sel {

	/// @brief Reference to one nibble. Copies of the proxy refer to the same element.
	class int4::reference
	{
	public:
		constexpr reference(unsigned char& byte, unsigned int shift)
			: m_byte(&byte), m_shift(shift) {}
		constexpr reference(const reference&) = default;

		constexpr operator int4() const { return int4((*m_byte >> m_shift) & 0x0fu); }
		constexpr explicit operator int() const { return int(int4(*this)); }
		constexpr int4 operator+() const { return int4(*this); }
		constexpr int4 operator-() const { return -int4(*this); }

		constexpr reference& operator=(int4 value)
		{
			// Mask only this nibble so the adjacent element remains intact.
			const unsigned int bits = static_cast<unsigned int>(int(value)) & 0x0fu;
			*m_byte = static_cast<unsigned char>((*m_byte & ~(0x0fu << m_shift)) | (bits << m_shift));
			return *this;
		}

		// Assignment copies the value, rather than rebinding the proxy's pointer.
		constexpr reference& operator=(const reference& other) { return *this = int4(other); }
		constexpr reference& operator+=(int4 rhs) { return *this = int4(*this) + rhs; }
		constexpr reference& operator-=(int4 rhs) { return *this = int4(*this) - rhs; }
		constexpr reference& operator*=(int4 rhs) { return *this = int4(*this) * rhs; }

	private:
		unsigned char* m_byte;
		unsigned int m_shift;
	};

}

namespace sel::utils {

	struct PackedInt4Access;

	/// @brief Shared storage and operations for the fixed-shape int4 specializations.
	/// Elements use row-major order, with even indices in the low nibble.
	template <std::size_t Rows, std::size_t Columns, class Matrix>
	class PackedInt4Matrix
	{
	public:
		constexpr PackedInt4Matrix() = default;

		constexpr PackedInt4Matrix(int4 scalar)
		{
			for (std::size_t index = 0; index < Rows && index < Columns; ++index)
			{
				(*this)[index][index] = scalar;
			}
		}

		template <class... Values, std::enable_if_t<sizeof...(Values) == Rows * Columns
			&& (std::is_convertible_v<Values, int4> && ...), int> = 0>
		constexpr PackedInt4Matrix(Values... values)
		{
			const int4 elements[] = { int4(values)... };
			for (std::size_t index = 0; index < Rows * Columns; ++index)
			{
				element(index) = elements[index];
			}
		}

		static constexpr Matrix identity() { return Matrix(int4(1)); }

		class Row
		{
		public:
			constexpr Row(PackedInt4Matrix& matrix, std::size_t offset)
				: m_matrix(matrix), m_offset(offset) {}
			constexpr int4::reference operator[](std::size_t column) const
			{
				return m_matrix.element(m_offset + column);
			}
		private:
			PackedInt4Matrix& m_matrix;
			std::size_t m_offset;
		};

		class ConstRow
		{
		public:
			constexpr ConstRow(const PackedInt4Matrix& matrix, std::size_t offset)
				: m_matrix(matrix), m_offset(offset) {}
			constexpr int4 operator[](std::size_t column) const
			{
				return m_matrix.element(m_offset + column);
			}
		private:
			const PackedInt4Matrix& m_matrix;
			std::size_t m_offset;
		};

		/// @brief Unchecked row access. Packed rows and elements are proxies, not pointers.
		constexpr Row operator[](std::size_t row) { return Row(*this, row * Columns); }
		constexpr ConstRow operator[](std::size_t row) const { return ConstRow(*this, row * Columns); }

		constexpr Matrix& operator+=(const Matrix& rhs)
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

		constexpr Matrix& operator-=(const Matrix& rhs)
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
		friend struct PackedInt4Access;

		constexpr int4::reference element(std::size_t index)
		{
			return int4::reference(m_data[index / 2], static_cast<unsigned int>(index % 2) * 4);
		}

		constexpr int4 element(std::size_t index) const
		{
			return int4((m_data[index / 2] >> ((index % 2) * 4)) & 0x0fu);
		}

		// No padding between rows; an unused final high nibble stays zero.
		unsigned char m_data[(Rows * Columns + 1) / 2] = {};
	};

	/// @brief Internal byte access for packed kernels; no public matrix data API.
	struct PackedInt4Access
	{
		template <std::size_t Rows, std::size_t Columns, class Matrix>
		static const unsigned char* data(const PackedInt4Matrix<Rows, Columns, Matrix>& matrix)
		{
			return matrix.m_data;
		}

		template <std::size_t Rows, std::size_t Columns, class Matrix>
		static unsigned char* data(PackedInt4Matrix<Rows, Columns, Matrix>& matrix)
		{
			return matrix.m_data;
		}
	};

}
