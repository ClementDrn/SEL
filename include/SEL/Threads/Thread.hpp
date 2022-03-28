#pragma once

#include "SEL/Utilities/NonCopyable.hpp"

#include <thread>


namespace sel {

	/// <summary>
	/// Represents a thread of execution and can assign tasks to it.
	/// </summary>
	class Thread : public NonCopyable
	{
	public:

		/// <summary>
		/// Specifies the possible states of the thread.
		/// </summary>
		enum class State
		{
			None	= 0b0000,		// The instance has been created but no task is assigned to a thread. In fact no thread is used by the instance.
			Running = 0b0001,		// The thread is running the assigned task.
			Joined	= 0b1000,		// The thread has finished its execution and joined another thread.
		};


		/// <summary>
		/// Default constructor. No task will be assigned to a thread.
		/// </summary>
		Thread()
			: m_state(State::None) {}

		/// <summary>
		/// Move constructor.
		/// </summary>
		/// <param name="other">The Thread object being moved.</param>
		/// <returns>The newly constructed Thread object.</returns>
		Thread(Thread&& other) noexcept
			: m_thread(std::move(other.m_thread)), m_state(other.m_state)
		{
			other.m_state = State::None;
		}

		/// <summary>
		/// Constructor that assigns a task to the thread represented by the constructed instance.
		/// </summary>
		/// <typeparam name="Fn">A callable type.</typeparam>
		/// <typeparam name="...Args">The argument types.</typeparam>
		/// <param name="function">The callable object.</param>
		/// <param name="...args">The arguments that are needed to call the object.</param>
		template <class Fn, class ...Args>
		Thread(Fn&& function, Args&&... args)
			: m_thread(function, args...), m_state(State::Running) {}

		/// <summary>
		/// Destructor that will call join() before deleting the instance.
		/// </summary>
		~Thread()
		{
			join();
		}


		/// <summary>
		/// Assigns a task to a thread and makes the instance represent this thread. 
		/// The method returns true if the task could be assigned. 
		/// If false is returned, make sure you have joined the thread to its parent one beforehand.
		/// </summary>
		/// <typeparam name="Fn">A callable type.</typeparam>
		/// <typeparam name="...Args">The argument types.</typeparam>
		/// <param name="function">The callable object.</param>
		/// <param name="...args">The arguments that are needed to call the object.</param>
		/// <returns>The value indicating if the task could be assigned to the thread.</returns>
		template <class Fn, class ...Args>
		bool run(Fn&& function, Args&&... args)
		{
			if (!(m_state == State::None || m_state == State::Joined))
				return false;

			m_thread = std::thread(function, args...);
			m_state = State::Running;
			return true;
		}

		/// <summary>
		/// Waits for the thread to finish its execution.
		/// If the thread is not joinable or if it is trying to join itself, false will be returned.
		/// </summary>
		/// <returns>The value indicating if the method could wait for the thread to finish its execution.</returns>
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


		/// <returns>The thread's state.</returns>
		State getState() const { return m_state; }


		/// <summary>
		/// Swaps two Thread objects.
		/// </summary>
		/// <param name="other">The other Thread object being swapped.</param>
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

		/// <summary>
		/// Move assignment operator.
		/// </summary>
		/// <param name="other">The Thread object being moved.</param>
		/// <returns>The newly constructed Thread object.</returns>
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
