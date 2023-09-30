#pragma once

#include <random>
#include <limits>


namespace sel {

	/// @brief Generates pseudo-random numbers.
	/// 
	class Random
	{
	public:

		/// @brief Initializes the pseudo-random number generator.
		///
		/// This static method should be called once before generating numbers.
		/// 
		static void init(uint32_t seed = std::random_device{}())
		{
			s_engine.seed(seed);
		}

		/// @brief Generates a pseudo-random float number between 0.0f and 1.0f.
		/// 
		/// @return The random decimal number.
		///  
		static float decimal()
		{
			// First, a uint32_t number is generated, then it is divided by the maximum value it could have be.
			return static_cast<float>(s_distribution(s_engine)) / static_cast<float>(std::numeric_limits<uint32_t>::max());
		}

		/// @brief Generates a pseudo-random integer.
		/// 
		/// @return The pseudo-random integer.
		///  
		static int integer()
		{
			return static_cast<int>(s_distribution(s_engine));
		}

		/// @brief Generates a pseudo-random unsigned integer.
		/// 
		/// @return The pseudo-random unsigned integer.
		///  
		static uint32_t uinteger()
		{
			return s_distribution(s_engine);
		}

		/// @brief Generates a pseudo-random boolean.
		/// 
		/// @return The pseudo-random unsigned boolean.
		///  
		static bool boolean()
		{
			return static_cast<bool>(s_distribution(s_engine) % 2);
		}

		/// @return The pseudo-random number generator used by the class.
		/// 
		static std::mt19937& getEngine() { return s_engine; }

	private:

		inline static std::mt19937 s_engine;
		inline static std::uniform_int_distribution<std::mt19937::result_type> s_distribution;
	};

}
