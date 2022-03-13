#pragma once

#include <random>
#include <limits>


namespace sel {

	class Random
	{
	public:

		static void init()
		{
			m_engine.seed(std::random_device()());
		}

		static float decimal()
		{
			return static_cast<float>(m_distribution(m_engine)) / static_cast<float>(std::numeric_limits<uint32_t>::max());
		}

		static int integer()
		{
			return static_cast<int>(m_distribution(m_engine));
		}

		static bool boolean()
		{
			return static_cast<bool>(m_distribution(m_engine) % 2);
		}

	private:

		inline static std::mt19937 m_engine;
		inline static std::uniform_int_distribution<std::mt19937::result_type> m_distribution;
	};

}
