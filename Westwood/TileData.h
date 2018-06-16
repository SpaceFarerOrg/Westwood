#pragma once
#include "TileInteraction.h"
#include <SFML\Graphics\Rect.hpp>

struct STileData
{
	operator short() const { return m_tileIndex; };
	void operator =(short a_index) { m_tileIndex = a_index; };

	ETileInteraction m_allowedInteraction;
	short m_tileIndex;
	sf::IntRect m_textureRect;
	bool m_isPassable : 1;
};