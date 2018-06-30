#pragma once
#include <SFML\System\String.hpp>
#include <vector>
#include "TileMap.h"
#include <json.hpp>
#include "Player.h"
#include "InteractableItem.h"

class CWorldZone
{
	friend class CWorldEditor;

public:
	void LoadZone(nlohmann::json& a_zoneJson);
	void Render();

	void EnterZone(CPlayer& a_player);
	void LeaveZone();

	void CheckPlayerAgainstItems();

	sf::Vector2f CheckForAllowedMove(const sf::Vector2f& a_targetPosition, const sf::Vector2f& a_currentPosition) const;

	void PerformWorldInteraction(ETileInteraction a_interaction, const sf::Vector2f& a_interactionPosition);

	void SpawnItem(short a_itemID, short a_amount, const sf::Vector2f& a_position);
private:
	struct SItemInWorldData
	{
		short a_itemID;
		sf::Vector2f m_position;
	};
private:
	std::vector<SItemInWorldData> m_items;
	std::vector<CInteractableItem*> m_objects;

	sf::String m_zoneName;
	CTileMap m_tileMap;

	CPlayer* m_player;
};