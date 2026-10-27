#pragma once

#include <cstddef>
#include <cstdint>
#include <type_traits>
#include "PackedInt4Matrix.hpp"

namespace sel::utils {
	struct UninitializedMatrixTag {};
}

namespace sel {

	/// @brief Fixed-size row-major matrix with natural scalar alignment.
	/// @tparam T Element type; Int4 uses tightly packed nibble storage.
	/// @tparam Rows Positive number of rows, known at compile time.
	/// @tparam Columns Positive number of columns, known at compile time.
	template <class T, std::size_t Rows, std::size_t Columns>
	class Matrix
	{
		static_assert(Rows > 0 && Columns > 0, "Matrix dimensions must be positive");
	public:
		using value_type = T;
		static constexpr std::size_t row_count = Rows;
		static constexpr std::size_t column_count = Columns;

		/// @brief Construct a zero matrix.
		constexpr Matrix() : m_data{} {}

		/// @brief Set the diagonal to scalar and all other elements to zero.
		constexpr Matrix(T scalar) : m_data{}
		{
			for (std::size_t index = 0; index < Rows && index < Columns; ++index)
				m_data[index][index] = scalar;
		}

		/// @brief Initialize exactly Rows * Columns elements in row-major order.
		/// The single-element case is already covered by the diagonal constructor.
		template <class... Values, std::enable_if_t<(Rows * Columns > 1)
			&& sizeof...(Values) == Rows * Columns
			&& (std::is_convertible_v<Values, T> && ...), int> = 0>
		constexpr Matrix(Values... values) : m_data{}
		{
			const T elements[] = { static_cast<T>(values)... };
			for (std::size_t row = 0; row < Rows; ++row)
				for (std::size_t column = 0; column < Columns; ++column)
					m_data[row][column] = elements[row * Columns + column];
		}

		/// @brief Return a diagonal-ones matrix, including for rectangular shapes.
		static constexpr Matrix identity() { return Matrix(T(1)); }

		/// @brief Unchecked row access; the returned pointer has Columns elements.
		constexpr T* operator[](std::size_t row) { return m_data[row]; }
		constexpr const T* operator[](std::size_t row) const { return m_data[row]; }

		/// @brief Add a matrix element by element.
		constexpr Matrix& operator+=(const Matrix& rhs)
		{
			for (std::size_t row = 0; row < Rows; ++row)
				for (std::size_t column = 0; column < Columns; ++column)
					m_data[row][column] += rhs[row][column];
			return *this;
		}

		/// @brief Subtract a matrix element by element.
		constexpr Matrix& operator-=(const Matrix& rhs)
		{
			for (std::size_t row = 0; row < Rows; ++row)
				for (std::size_t column = 0; column < Columns; ++column)
					m_data[row][column] -= rhs[row][column];
			return *this;
		}

	private:
		template <class U, std::size_t R, std::size_t K, std::size_t C>
		friend Matrix<U, R, C> operator*(const Matrix<U, R, K>&, const Matrix<U, K, C>&);
		// Multiplication writes every ordinary element before it can be read.
		// Keep this constructor private so public default construction stays zeroed.
		explicit Matrix(utils::UninitializedMatrixTag) {}
		T m_data[Rows][Columns];
	};

	/// @brief Packed signed four-bit matrix, with no padding between rows.
	/// Mutable indexing returns Int4::reference; const indexing returns a value.
	template <std::size_t Rows, std::size_t Columns>
	class Matrix<Int4, Rows, Columns>
		: public utils::PackedInt4Matrix<Rows, Columns, Matrix<Int4, Rows, Columns>>
	{
		static_assert(Rows > 0 && Columns > 0, "Matrix dimensions must be positive");
		using Base = utils::PackedInt4Matrix<Rows, Columns, Matrix<Int4, Rows, Columns>>;
	public:
		using value_type = Int4;
		static constexpr std::size_t row_count = Rows;
		static constexpr std::size_t column_count = Columns;
		using Base::Base;
		constexpr Matrix() = default;

	private:
		template <class U, std::size_t R, std::size_t K, std::size_t C>
		friend Matrix<U, R, C> operator*(const Matrix<U, R, K>&, const Matrix<U, K, C>&);
		// Packed element writes read the adjacent nibble; initialize all bytes,
		// including any final padding nibble, before multiplication fills them.
		explicit Matrix(utils::UninitializedMatrixTag) : Base() {}
	};

	/// @brief Return the element-wise sum of equal-shape matrices.
	template <class T, std::size_t Rows, std::size_t Columns>
	constexpr Matrix<T, Rows, Columns> operator+(Matrix<T, Rows, Columns> lhs,
		const Matrix<T, Rows, Columns>& rhs) { return lhs += rhs; }

	/// @brief Return the element-wise difference of equal-shape matrices.
	template <class T, std::size_t Rows, std::size_t Columns>
	constexpr Matrix<T, Rows, Columns> operator-(Matrix<T, Rows, Columns> lhs,
		const Matrix<T, Rows, Columns>& rhs) { return lhs -= rhs; }
}

#include "MatrixMultiplications.hpp"
