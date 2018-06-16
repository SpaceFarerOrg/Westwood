#include "WorldZone.h"
#include <fstream>

void CWorldZone::LoadZone(nlohmann::json & a_zoneJson)
{
	m_zoneName = a_zoneJson["name"].get<std::string>();

	std::ifstream tileMapFile("data/" + a_zoneJson["tileMap"].get<std::string>());
	
	nlohmann::json tileMapJson;
	tileMapFile >> tileMapJson;

	tileMapFile.close();

	m_tileMap.Load(tileMapJson);
}

void CWorldZone::Render()
{
	m_tileMap.Render();
}

bool CWorldZone::IsMoveToPositionAllowed(const sf::Vector2f & a_positionToCheck) const
{
	bool allowed = m_tileMap.IsPositionWalkable(a_positionToCheck);
}
