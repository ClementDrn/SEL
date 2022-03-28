#pragma once


namespace sel {

	constexpr static unsigned int strToUint(const char* str, unsigned int index = 0)
	{
		return !str[index] ? 5381 : (strToUint(str, index + 1) * 33) ^ str[index];
	}

}
