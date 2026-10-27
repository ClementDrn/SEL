#pragma once

#include "Detail/LowPrecisionFloat.hpp"

namespace sel {

	/// @brief OCP E5M2 value with one sign bit, five exponent bits, and two fraction bits.
	/// One-byte storage supports signed zero, subnormals, infinities, and NaNs,
	/// with maximum finite magnitude 57344. Numeric conversion rounds to nearest-even,
	/// saturates overflow/infinities to signed 57344, and maps NaNs to canonical
	/// encoding 0x7e. Raw-bit construction preserves infinity and NaN encodings.
	/// @see utils::LowPrecisionFloat for arithmetic and raw-bit access.
	using Float8E5M2 = utils::LowPrecisionFloat<5, 2>;

}
