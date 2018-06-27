#include "WorldZone.h"
#include <fstream>

void CWorldZone::LoadZone(nlohmann::json & a_zoneJson)
{
	m_zoneName = a_zoneJson["name"].get<std::string>();

	std::ifstream tileMapFile("data/" + a_zoneJson["tileMap"].get<std::string>());
	
	nlohmann::json tileMapJson;
	tileMapFile >> tileMapJson;

	tileMapFile.close();

	m_tileMap.Load(tileMapJson, *this);
}

void CWorldZone::Render()
{
	m_tileMap.Render();
}

sf::Vector2f CWorldZone::CheckForAllowedMove(const sf::Vector2f & a_targetPosition, const sf::Vector2f& a_currentPosition) const
{
	sf::Vector2f allowedPosition = m_tileMap.CheckForAllowedMove(a_targetPosition, a_currentPosition);

	return std::move(allowedPosition);
}

void CWorldZone::PerformWorldInteraction(ETileInteraction a_interaction, const sf::Vector2f & a_interactionPosition)
{
	m_tileMap.PerformInteraction(a_interactionPosition, a_interaction);
}
