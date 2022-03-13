#pragma once

#include <random>
#include <limits>


namespace sel {

	class Random
	{
	public:

		Random()
		{
			m_engine.seed(std::random_device()());
		}

		float decimal()
		{
			return static_cast<float>(m_distribution(m_engine)) / static_cast<float>(std::numeric_limits<uint32_t>::max());
		}

		int integer()
		{
			return static_cast<int>(m_distribution(m_engine));
		}

		bool boolean()
		{
			return static_cast<bool>(m_distribution(m_engine) % 2);
		}

	private:

		std::mt19937 m_engine;
		std::uniform_int_distribution<std::mt19937::result_type> m_distribution;
	};

}
