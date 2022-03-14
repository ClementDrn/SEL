#pragma once

#include <random>
#include <limits>


namespace sel {

	class Random
	{
	public:

		static void init()
		{
			s_engine.seed(std::random_device()());
		}

		static float decimal()
		{
			return static_cast<float>(s_distribution(s_engine)) / static_cast<float>(std::numeric_limits<uint32_t>::max());
		}

		static int integer()
		{
			return static_cast<int>(s_distribution(s_engine));
		}

		static uint32_t uinteger()
		{
			return s_distribution(s_engine);
		}

		static bool boolean()
		{
			return static_cast<bool>(s_distribution(s_engine) % 2);
		}

		static std::mt19937& getEngine() { return s_engine; }

	private:

		inline static std::mt19937 s_engine;
		inline static std::uniform_int_distribution<std::mt19937::result_type> s_distribution;
	};

}
