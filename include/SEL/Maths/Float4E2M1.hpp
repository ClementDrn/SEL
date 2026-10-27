#pragma once

#include "Detail/LowPrecisionFloat.hpp"

namespace sel {

	/// @brief OCP E2M1 value with one sign bit, two exponent bits, and one fraction bit.
	/// Finite magnitudes are 0, 0.5, 1, 1.5, 2, 3, 4, and 6; both zeros exist.
	/// Numeric conversion rounds to nearest-even and saturates overflow/infinities
	/// to signed 6. NaN maps to +0 because no NaN encoding exists. Standalone
	/// values occupy one byte; matrices pack two values per byte.
	/// @see utils::LowPrecisionFloat for arithmetic and raw-bit access.
	using Float4E2M1 = utils::LowPrecisionFloat<2, 1>;

}
