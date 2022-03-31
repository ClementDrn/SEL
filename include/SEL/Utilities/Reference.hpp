#pragma once

#include <memory>


namespace sel {
	
	/// @brief Allocates memory for the specified class or type 
	/// and releases it when it is out of scope.
	/// 
	/// In fact, Scope is implemented as a std::unique_ptr.
	/// 
	/// @tparam T is the class/type of object/variable Scope has to allocate.
	/// 
	template <typename T>
	using Scope = std::unique_ptr<T>;

	/// @brief Effectively creates a Scope instance.
	/// 
	/// @tparam T is the class/type of object/variable Scope has to allocate.
	/// @tparam ...Args are the types of the arguments for the class constructor.
	/// @param ...args are the arguments for the class constructor.
	/// 
	/// @return The created Scope instance.
	/// 
	template <typename T, typename ...Args>
	constexpr Scope<T> createScope(Args&& ...args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}


	/// @brief Allows to share a same reference to an object/variable through copies.
	/// 
	/// When every Ref instance of a same object/variable is deleted or out of scope,
	/// the object/variable's memory is released.
	/// In fact, Ref is implemented as a std::shared_ptr.
	/// 
	/// @tparam T is the class/type of object/variable Ref has to allocate.
	/// 
	template <typename T>
	using Ref = std::shared_ptr<T>;

	/// @brief Effectively creates a Ref instance.
	/// 
	/// @tparam T is the class/type of object/variable Ref has to allocate.
	/// @tparam ...Args are the types of the arguments for the class constructor.
	/// @param ...args are the arguments for the class constructor.
	/// 
	/// @return The created Ref instance.
	/// 
	template <typename T, typename ...Args>
	constexpr Ref<T> createRef(Args&& ...args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}

}
