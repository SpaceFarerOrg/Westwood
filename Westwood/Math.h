#pragma once
#include <SFML\System\Vector2.hpp>
#include <random>
#include <assert.h>

namespace Math
{
	static float GetLenght2(const sf::Vector2f& a_vector)
	{
		return a_vector.x * a_vector.x + a_vector.y * a_vector.y;
	}

	static short RandomInRange(short a_min, short a_max)
	{
		static std::random_device randomDevice;
		static std::mt19937 seedGenerator(randomDevice());

		std::uniform_int_distribution<short> distributor(a_min, a_max);
		short randomNumber = distributor(seedGenerator);

		return randomNumber;
	}

	static bool Chance(short a_percentageChance)
	{
		short percentage = RandomInRange(0, 100);

		if (a_percentageChance >= percentage)
		{
			return true;
		}

		return false;
	}

	template <typename T>
	T Clamp(const T& a_t, const T& a_min, const T& a_max)
	{
		T clampedVal = a_t;

		if (clampedVal < a_min)
		{
			clampedVal = a_min;
		}
		else if (a_max < clampedVal)
		{
			clampedVal = a_max;
		}

		return clampedVal;
	}
}