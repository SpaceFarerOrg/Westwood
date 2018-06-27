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
public:
	STileData()
	{
		m_tileIndex = -1;
		m_isAdaptive = false;

		for (size_t i = 0; i < static_cast<size_t>(ETileInteraction::Count); ++i)
		{
			m_allowedInteractions[i] = false;
			m_onInteractionAddTile[i] = -1;
		}
	}

	operator short() const { return m_tileIndex; };
	void operator =(short a_index) { m_tileIndex = a_index; };

	
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

	void SetTileToAddOnInteraction(ETileInteraction a_interaction, short a_tileToAddToInteractionLayer)
	{
		m_onInteractionAddTile[static_cast<size_t>(a_interaction)] = a_tileToAddToInteractionLayer;
	}

	short GetTileToAddOnInteraction(ETileInteraction a_interaction) const
	{
		return m_onInteractionAddTile[static_cast<size_t>(a_interaction)];
	}

public:
	std::array<short, static_cast<size_t>(EAdaptiveState::Count)> m_adaptiveIndexLUT;
	std::array<bool, static_cast<size_t>(ETileInteraction::Count)> m_allowedInteractions;
	std::array<short, static_cast<size_t>(ETileInteraction::Count)> m_onInteractionAddTile;


	short m_tileIndex;
	sf::IntRect m_textureRect;
	bool m_isAdaptive : 1;
};