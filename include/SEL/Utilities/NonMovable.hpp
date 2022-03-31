#pragma once


namespace sel {

	/// @brief Subclasses of this class won't be able to be moved by default.
	///
	class NonMovable
	{
	public:

		NonMovable(NonMovable&&) = delete;
		NonMovable& operator=(NonMovable&&) = delete;

	protected:

		NonMovable() = default;
	};

}
