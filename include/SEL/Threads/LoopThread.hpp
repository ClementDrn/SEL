#pragma once

#include "SEL/Utilities/NonCopyable.hpp"

#include "SEL/Threads/ThreadCore.hpp"
#include "SEL/Threads/Thread.hpp"

#include <functional>


namespace sel {

	/// @brief Represents and controls a thread of execution that will repeat a task.
	/// 
	class LoopThread : public NonCopyable
	{
	public:

		/// @brief Specifies the possible states of the thread.
		///
		enum class State
		{
			None	= 0b0000,		///< The instance has been created but no task is assigned to a thread. In fact no thread is used by the instance.
			Running = 0b0001,		///< The thread is running the assigned task.
			Paused	= 0b0010,		///< The thread is still being used but no longer runs the task.
			Stopped = 0b0100,		///< The thread has finished to loop but has not joined any other thread yet.
			Joined	= 0b1000,		///< The thread has finished its execution and joined another thread.
		};


		/// @brief Default constructor. No task will be assigned to a thread.
		/// 
		LoopThread()
		{
			init();
		}
		
		/// @brief Move constructor.
		/// 
		/// @param other is the LoopThread object being moved.
		/// 
		/// @return The newly constructed LoopThread object.
		/// 
		LoopThread(LoopThread&& other) noexcept
		{
			move(other);
		}

		/// @brief Constructor that assigns a function as the task for its future thread.
		/// 
		/// @param function is the task that will be repeated by the thread.
		/// 
		LoopThread(std::function<void()> function)
			: m_onLoop(function)
		{
			init();
		}
		
		/// @brief Constructor that assigns a method as the task for its future thread.
		/// 
		/// @tparam C is the class that owns the method.
		/// @param method is the task that will be repeated by the thread.
		/// @param object is the object needed to call the method.
		/// 
		template <class C>
		LoopThread(void(C::* method)(), C* object)
			: m_onLoop(std::bind(method, object))
		{
			init();
		}

		/// @brief Destructor that will call stop() and join() before deleting the instance.
		///
		~LoopThread()
		{
			join();
		}

		
		/// @brief Assigns a function as the task for its future thread.
		/// 
		/// The method returns true if the task could be assigned. 
		/// If false is returned, make sure the thread was not running.
		/// 
		/// @param function is the task that will be repeated by the thread.
		/// 
		/// @return The value indicating if the task could be assigned to the thread.
		/// 
		bool setOnLoopFunc(std::function<void()> function)
		{
			if (getState() == State::Running)
				return false;

			WriteLock write(m_mutex);

			m_onLoop = function;
			return true;
		}
		
		/// @brief Assigns a method as the task for its future thread.
		/// 
		/// The method returns true if the task could be assigned. 
		/// If false is returned, make sure the thread was not running.	
		/// 
		/// @tparam C is the class that owns the method.
		/// @param method is the task that will be repeated by the thread.
		/// @param object is the object needed to call the method.
		/// 
		/// @return The value indicating if the task could be assigned to the thread.
		/// 
		template <class C>
		bool setOnLoopFunc(void(C::* method)(), C* object)
		{
			return setOnLoopFunc(std::bind(method, object));
		}


		/// @brief Creates a thread of execution and asks it to start repeating the task. 
		/// 
		void start()
		{
			WriteLock write(m_mutex);

			stopScript();
			join(false);
			m_isStopAsked = false;
			startThread();
		}

		/// @brief Asks and waits for the thread to stop repeating the task but does not terminate.
		/// 
		/// Once this method has been called, the thread will be in a pause state.
		/// 
		void pause()
		{
			ReadLock read(m_mutex);

			if (m_state == State::Running)
			{
				read.unlock();
				WriteLock write(m_mutex);

				m_isPauseAsked = true;

				write.unlock();

				WAIT_FOR(getState() != State::Running);
			}
		}

		/// @brief Asks the thread to start repeating the task again if it was in a pause state.
		/// 
		void resume()
		{
			WriteLock write(m_mutex);
			resumeScript();
		}

		/// @brief Asks the thread to stop repeating the task. 
		/// 
		void stop()
		{
			WriteLock write(m_mutex);
			stopScript();
		}

		/// @brief Waits for the thread to finish its execution.
		/// 
		/// If the thread is not joinable or if it is trying to join itself, false will be returned.
		/// If the withStop parameter is set to false, the method will not call stop() before trying to join the threads.
		/// 
		/// @param withStop is the value indicating if the method should stop the loop before trying to join.
		/// 
		/// @return The value indicating if the method could wait for the thread to finish its execution.
		/// 
		bool join(bool withStop = true)
		{
			if (withStop)
				stop();

			bool success = m_thread.join();

			if (success)
				m_state = State::Joined;

			return success;
		}


		/// @return The thread's state.
		///
		State getState() const
		{
			ReadLock read(m_mutex);

			return m_state;
		}


		/// @brief Swaps two LoopThread objects.
		/// 
		/// @param is the other LoopThread object being swapped.
		/// 
		void swap(LoopThread& other)
		{
			if (this != &other)
			{
				ReadLock thisRead(m_mutex);
				ReadLock otherRead(other.m_mutex);

				State thisState = m_state;
				bool thisPause = m_isPauseAsked;
				bool thisStop = m_isStopAsked;

				State otherState = other.m_state;
				bool otherPause = other.m_isPauseAsked;
				bool otherStop = other.m_isStopAsked;

				thisRead.unlock();
				otherRead.unlock();

				stop();
				other.stop();

				m_onLoop.swap(other.m_onLoop);
				auto temp = m_onLoop;
				m_onLoop = other.m_onLoop;
				other.m_onLoop = temp;

				// If the thread was busy while not supposed to stop.
				if (((int)otherState & ((int)State::Running | (int)State::Paused)) && !otherStop)
					startThread();

				if (((int)thisState & ((int)State::Running | (int)State::Paused)) && !thisStop)
					other.startThread();
			}
		}

		/// @brief Move assignment operator.
		/// 
		/// @param other is the LoopThread object being moved.
		/// 
		/// @return The newly constructed LoopThread object.
		/// 
		LoopThread& operator=(LoopThread&& other) noexcept
		{
			if (this != &other)
				move(other);

			return *this;
		}


	private:

		void init()
		{
			m_state = State::None;
			m_isPauseAsked = false;
			m_isStopAsked = true;
		}

		void move(LoopThread& other)
		{
			ReadLock read(other.m_mutex);

			State state = other.m_state;
			bool pause = other.m_isPauseAsked;
			bool stop = other.m_isStopAsked;

			read.unlock();

			other.stop();
			other.m_state = State::None;

			m_onLoop = std::move(other.m_onLoop);

			m_isPauseAsked = pause;
			m_isStopAsked = stop;

			// If the thread was busy while not supposed to stop.
			if (((int)state & ((int)State::Running | (int)State::Paused)) && !stop)
				startThread();
		}

		void threadLoop()
		{
			while (true)
			{
				{
					ReadLock read(m_mutex);

					if (m_isStopAsked)
					{
						read.unlock();

						WriteLock write(m_mutex);
						m_state = State::Stopped;
						break;
					}

					if (m_isPauseAsked)
					{
						read.unlock();

						WriteLock write(m_mutex);
						m_state = State::Paused;
						write.unlock();

						WAIT_FOR(getState() != State::Paused);
					}
				}

				// Loop script
				m_onLoop();
			}
		}

		void startThread()
		{
			m_state = State::Running;
			m_thread.run(&LoopThread::threadLoop, this);
		}

		void resumeScript()
		{
			if (m_state == State::Paused)
			{
				m_isPauseAsked = false;
				m_state = State::Running;
			}
		}

		void stopScript()
		{
			m_isStopAsked = true;
			resumeScript();
		}


		Thread m_thread;
		State m_state;
		std::function<void()> m_onLoop;
		mutable Mutex m_mutex;
		bool m_isPauseAsked;
		bool m_isStopAsked;
	};

}
