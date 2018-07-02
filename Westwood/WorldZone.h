#pragma once
#include <SFML\System\String.hpp>
#include <vector>
#include "TileMap.h"
#include <json.hpp>
#include "InteractableItem.h"

class CPlayer;

class CWorldZone
{
	friend class CWorldEditor;

public:
	void LoadZone(nlohmann::json& a_zoneJson);
	void Render();

	void EnterZone();
	void LeaveZone();

	CTileMap& GetTileMap();

	void CheckPlayerAgainstItems(CPlayer& a_player);

	sf::Vector2f CheckForAllowedMove(const sf::Vector2f& a_targetPosition, const sf::Vector2f& a_currentPosition) const;

	CInteractableItem* GetTargetedObject(const sf::Vector2f& a_targetPosition);

	void SpawnItem(short a_itemID, short a_amount, const sf::Vector2f& a_position);
private:
	struct SItemInWorldData
	{
		short a_itemID;
		sf::Vector2f m_position;
	};
private:

	void LoadObjects(nlohmann::json& a_tileMapJson);

	std::vector<SItemInWorldData> m_items;
	std::vector<CInteractableItem*> m_objects;

	sf::String m_zoneName;
	CTileMap m_tileMap;
};