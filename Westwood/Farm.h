#pragma once
#include <vector>
#include "PlantBank.h"
#include <SFML\System\Vector2.hpp>

class CTileMap;

class CFarm
{
public:
	CFarm();
	void PlantSeed(const char* a_plantName, short a_onTileIndex);
	void PlantSeed(short a_plantID, short a_onTileIndex);

	void BindFarmTileMap(CTileMap& a_tileMap);

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
		short m_tileIndex;
	};

	void TickDay();
private:
	std::vector<SPlantedPlant> m_plants;
	CPlantBank m_plantBank;

	CTileMap* m_tileMap;
};