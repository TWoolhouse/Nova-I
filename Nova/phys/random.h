#pragma once
#include "lib.h"
#include <random>

namespace Nova::mlb {

	class NOVA_API Random {
	public:
		template<typename T>
		inline static T random(T a, T b) = delete;
		template<>
		inline static float random(float a, float b) { return std::uniform_real_distribution<float>(a, b)(m_gen); }
		template<>
		inline static double random(double a, double b) { return std::uniform_real_distribution<double>(a, b)(m_gen); }
		template<>
		inline static int random(int a, int b) { return std::uniform_int_distribution<int>(a, b)(m_gen); }
		template<>
		inline static unsigned int random(unsigned int a, unsigned int b) { return std::uniform_int_distribution<unsigned int>(a, b)(m_gen); }

		template<typename T>
		inline static std::uniform_real_distribution<T> generatorf(T a, T b) { return std::uniform_real_distribution<T>(a, b); }
		template<typename T>
		inline static std::uniform_int_distribution<T> generatori(T a, T b) { return std::uniform_int_distribution<T>(a, b); }

		inline static std::mt19937& generator() { return m_gen; }
	protected:
		static std::mt19937 m_gen;
	};

}