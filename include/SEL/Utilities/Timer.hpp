#pragma once

#include <chrono>


namespace sel {
	
	class Timer
	{
	public:
		
		Timer()
		{
			reset();
		}

		void reset()
		{
			m_start = std::chrono::steady_clock::now();
		}

		size_t getNanoseconds()
		{
			auto end = std::chrono::steady_clock::now();

			std::chrono::duration<double, std::nano> highResStart = { m_start.time_since_epoch() };
			auto elapsedTime =
				std::chrono::time_point_cast<std::chrono::nanoseconds>(end).time_since_epoch()
				- std::chrono::time_point_cast<std::chrono::nanoseconds>(m_start).time_since_epoch();
			
			return elapsedTime.count();
		}

		float getMicroseconds()
		{
			return getNanoseconds() * 0.001f;
		}

		float getMilliseconds()
		{
			return getNanoseconds() * 0.001f * 0.001f;
		}

		float getSeconds()
		{
			return getNanoseconds() * 0.001f * 0.001f * 0.001f;
		}

	private:
		
		std::chrono::time_point<std::chrono::steady_clock> m_start;
	};
	
}
