#pragma once
#include <SFML\System\String.hpp>
#include "TileMap.h"
#include <json.hpp>

class CWorldZone
{
	friend class CWorldEditor;

public:
	void LoadZone(nlohmann::json& a_zoneJson);
	void Render();

	bool IsMoveToPositionAllowed(const sf::Vector2f& a_positionToCheck) const;
private:
	sf::String m_zoneName;
	CTileMap m_tileMap;

};