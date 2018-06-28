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

struct SItemSpawnData
{
	SItemSpawnData()
	{
		m_chance = 0;
		m_itemId = -1;
		m_minSpawnAmount = 0;
		m_maxSpawnAmount = 0;
	}

	SItemSpawnData(short a_chance, short a_itemID, short a_minSpawnAmount, short a_maxSpawnAmount)
	{
		m_chance = a_chance;
		m_itemId = a_itemID;
		m_minSpawnAmount = a_minSpawnAmount;
		m_maxSpawnAmount = a_maxSpawnAmount;
	}

	short m_chance;
	short m_itemId;
	short m_minSpawnAmount;
	short m_maxSpawnAmount;
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

	void AddInteractionItemSpawn(short a_itemID, short a_chance, ETileInteraction a_onInteraction, short a_minSpawnAmount, short a_maxSpawnAmount)
	{
		m_onInteractionSpawnlist[static_cast<size_t>(a_onInteraction)].push_back({ a_chance, a_itemID, a_minSpawnAmount, a_maxSpawnAmount });
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
	std::array<std::vector<SItemSpawnData>, static_cast<size_t>(ETileInteraction::Count)> m_onInteractionSpawnlist;


	short m_tileIndex;
	sf::IntRect m_textureRect;
	bool m_isAdaptive : 1;
};