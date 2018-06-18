#pragma once
#include <array>
#include "TileInteraction.h"
#include <SFML\Graphics\Rect.hpp>

enum class EAdaptiveState
{
	LowerRightCorner,
	UpperRightCorner,
	LowerLeftCorner,
	UpperLeftCorner,
	Center,
	LonelyWithRightNeighbour,
	LonelyWithLeftNeighbour,
	LonelyWithLowerNeighbour,
	LonelyWithUpperNeighbour,
	CenterOfVerticalLine,
	CenterOfHorizontalLine,
	Left,
	Right,
	Top,
	Bottom,
	Count,
};

struct STileData
{
	operator short() const { return m_tileIndex; };
	void operator =(short a_index) { m_tileIndex = a_index; };

	ETileInteraction m_allowedInteraction;
	short m_tileIndex;
	sf::IntRect m_textureRect;
	
	std::array<short, static_cast<size_t>(EAdaptiveState::Count)> m_adaptiveIndexLUT;

	short GetAdaptiveIndex(EAdaptiveState a_state)
	{
		return m_adaptiveIndexLUT[static_cast<size_t>(a_state)];
	}

	bool m_isPassable : 1;
	bool m_isAdaptive : 1;

};