#pragma once
#include <SFML\System\Vector2.hpp>
#include <random>
#include <assert.h>

namespace Math
{

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

	static float Lerp(float a_Start, float a_Target, float a_Percentage)
	{
		return (1 - a_Percentage) * a_Start + a_Percentage * a_Target;
	}

	static sf::Vector2f Lerp(const sf::Vector2f& a_Start, const sf::Vector2f& a_End, float a_Percentage)
	{
		sf::Vector2f returnVector;

		returnVector.x = Lerp(a_Start.x, a_End.x, a_Percentage);
		returnVector.y = Lerp(a_Start.y, a_End.y, a_Percentage);

		return std::move(returnVector);
	}


	static float GetLenght2(const sf::Vector2f& a_vector)
	{
		return a_vector.x * a_vector.x + a_vector.y * a_vector.y;
	}

	static float GetLength(const sf::Vector2f& a_Vector)
	{
		return sqrtf(GetLenght2(a_Vector));
	}

	static void Normalize(sf::Vector2f& a_Vec)
	{
		float l = GetLength(a_Vec);
		a_Vec /= l;
	}
}