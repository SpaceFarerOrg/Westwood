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

	sf::Vector2f CheckForAllowedMove(const sf::Vector2f& a_targetPosition, const sf::Vector2f& a_currentPosition) const;

	void PerformWorldInteraction(ETileInteraction a_interaction, const sf::Vector2f& a_interactionPosition);
private:
	sf::String m_zoneName;
	CTileMap m_tileMap;

};