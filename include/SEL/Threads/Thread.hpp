#pragma once

#include "SEL/Utilities/NonCopyable.hpp"

#include <thread>


namespace sel {

	/// @brief Represents a thread of execution and can assign tasks to it.
	///
	class Thread : public NonCopyable
	{
	public:

		/// @brief Specifies the possible states of the thread.
		///
		enum class State
		{
			None	= 0b0000,		///< The instance has been created but no task is assigned to a thread. In fact no thread is used by the instance.
			Running = 0b0001,		///< The thread is running the assigned task.
			Joined	= 0b1000,		///< The thread has finished its execution and joined another thread.
		};


		/// @brief Default constructor. No task will be assigned to a thread.
		/// 
		Thread()
			: m_state(State::None) {}

		/// @brief Move constructor.
		/// 
		/// @param other is the Thread object being moved.
		/// 
		/// @return The newly constructed Thread object.
		/// 
		Thread(Thread&& other) noexcept
			: m_thread(std::move(other.m_thread)), m_state(other.m_state)
		{
			other.m_state = State::None;
		}
		
		/// @brief Constructor that assigns a task to the thread represented by the constructed instance.
		/// 
		/// @tparam Fn is a callable type.
		/// @tparam ...Args are the argument types.
		/// @param function is the callable object.
		/// @param ...args The arguments that are needed to call the object.
		/// 
		template <class Fn, class ...Args>
		Thread(Fn&& function, Args&&... args)
			: m_thread(function, args...), m_state(State::Running) {}

		/// @brief Destructor that will call join() before deleting the instance.
		///
		~Thread()
		{
			join();
		}


		/// @brief Assigns a task to a thread and makes the instance represent this thread. 
		/// 
		/// The method returns true if the task could be assigned. 
		/// If false is returned, make sure you have joined the thread to its parent one beforehand.
		/// 
		/// @tparam Fn is a callable type
		/// @tparam ...Args are the argument types.
		/// @param function is the callable object.
		/// @param ...args The arguments that are needed to call the object.
		/// 
		/// @return The value indicating if the task could be assigned to the thread.
		/// 
		template <class Fn, class ...Args>
		bool run(Fn&& function, Args&&... args)
		{
			if (!(m_state == State::None || m_state == State::Joined))
				return false;

			m_thread = std::thread(function, args...);
			m_state = State::Running;
			return true;
		}

		/// @brief Waits for the thread to finish its execution.
		/// 
		/// If the thread is not joinable or if it is trying to join itself, false will be returned.
		/// 
		/// @return The value indicating if the method could wait for the thread to finish its execution.
		/// 
		bool join()
		{
			if (m_thread.joinable() && std::this_thread::get_id() != m_thread.get_id())
			{
				m_thread.join();
				m_state = State::Joined;

				return true;
			}

			return false;
		}


		/// @return The thread's state.
		///
		State getState() const { return m_state; }


		/// @brief Swaps two Thread objects.
		/// 
		/// @param other is the other Thread object being swapped.
		/// 
		void swap(Thread& other)
		{
			if (this != &other)
			{
				m_thread.swap(other.m_thread);

				State temp = m_state;
				m_state = other.m_state;
				other.m_state = temp;
			}
		}

		/// @brief Move assignment operator.
		/// 
		/// @param other is the Thread object being moved.
		/// 
		/// @return The newly constructed Thread object.
		/// 
		Thread& operator=(Thread&& other) noexcept
		{
			if (this != &other)
			{
				m_thread = std::move(other.m_thread);
				m_state = other.m_state;
				other.m_state = State::None;
			}

			return *this;
		}


	private:

		std::thread m_thread;
		State m_state;
	};

}
