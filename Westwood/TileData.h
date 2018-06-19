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

	short m_tileIndex;
	sf::IntRect m_textureRect;
	

	void SetInteractionAllowance(ETileInteraction a_interaction, bool a_shouldBeAllowed)
	{
		m_allowedInteractions[static_cast<size_t>(a_interaction)] = a_shouldBeAllowed;
	}

	bool IsInteractionAllowed(ETileInteraction a_interaction) const
	{
		return m_allowedInteractions[static_cast<size_t>(a_interaction)];
	}

	short GetAdaptiveIndex(EAdaptiveState a_state)
	{
		return m_adaptiveIndexLUT[static_cast<size_t>(a_state)];
	}
	
	std::array<short, static_cast<size_t>(EAdaptiveState::Count)> m_adaptiveIndexLUT;
	std::array<bool, static_cast<size_t>(ETileInteraction::Count)> m_allowedInteractions;

	bool m_isAdaptive : 1;
};