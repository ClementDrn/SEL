#pragma once

#include "Detail/LowPrecisionFloat.hpp"

namespace sel {

	/// @brief OCP E4M3 value with one sign bit, four exponent bits, and three fraction bits.
	/// One-byte storage supports signed zero, subnormals, and NaNs, with maximum
	/// finite magnitude 448 and no infinity encoding. Numeric conversion rounds
	/// to nearest-even, saturates overflow/infinities to signed 448, and maps NaNs
	/// to canonical encoding 0x7f without preserving payloads.
	/// @see utils::LowPrecisionFloat for arithmetic and raw-bit access.
	using Float8E4M3 = utils::LowPrecisionFloat<4, 3>;

}
