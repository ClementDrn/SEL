#pragma once


namespace sel {

	/// @brief Subclasses of this class won't be able to be copied by default.
	class NonCopyable
	{
	public:

		NonCopyable(const NonCopyable&) = delete;
		NonCopyable& operator=(const NonCopyable&) = delete;

	protected:

		NonCopyable() = default;
	};

}
