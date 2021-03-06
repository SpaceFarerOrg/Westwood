#pragma once
#include <vector>
#include "PlantBank.h"
#include <SFML\System\Vector2.hpp>
#include <unordered_map>

class CTileMap;
class CWorldZone;

class CFarm
{
public:
	CFarm();
	void Init();
	void PlantSeed(const char* a_plantName, short a_onTileIndex);
	void PlantSeed(short a_plantID, short a_onTileIndex);

	void BindFarmTileMap(CTileMap& a_tileMap);

	bool TileContainsSeed(short a_tileIndex);

	bool TryHarvest(short a_tileIndex, CWorldZone* a_zone);

	void Render();
private:
	struct SPlantedPlant
	{
		SPlantedPlant()
		{
			m_days = 0;
			m_plantID = -1;
		}

		short m_days;
		short m_plantID;
	};

	void TickDay();
private:
	std::unordered_map<short, SPlantedPlant> m_plants;
	CPlantBank m_plantBank;

	CTileMap* m_tileMap;
};