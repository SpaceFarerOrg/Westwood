#pragma once
#include <SFML\System\Vector2.hpp>

namespace Math
{
	static float GetLenght2(const sf::Vector2f& a_vector)
	{
		return a_vector.x * a_vector.x + a_vector.y * a_vector.y;
	}
}