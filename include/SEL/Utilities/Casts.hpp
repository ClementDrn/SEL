#pragma once


namespace sel {

	/// @brief Transforms a C-style string to an unsigned int.
	/// 
	/// This is useful when using a switch with strings since switches only support case statements with numbers.
	/// 
	/// @param str is the string input
	/// @param index is the index of the string to start from.
	/// 
	/// @return The number representing the string.
	///  
	constexpr static unsigned int strToUint(const char* str, unsigned int index = 0)
	{
		return !str[index] ? 5381 : (strToUint(str, index + 1) * 33) ^ str[index];
	}

}
