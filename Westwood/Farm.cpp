#include "Farm.h"
#include "GameEventMaster.h"
#include "TileMap.h"

CFarm::CFarm()
{
	m_plantBank.LoadAllPlants();
	CGameEventMaster::GetInstance().SubscribeToEvent(EGameEvent::FadeReachBlack, [this] {this->TickDay(); });
}

void CFarm::PlantSeed(const char * a_plantName, short a_tileIndex)
{
	short plantID = m_plantBank.GetPlantID(a_plantName);

	PlantSeed(plantID, a_tileIndex);
}

void CFarm::PlantSeed(short a_plantID, short a_tileIndex)
{
	m_plants.push_back(SPlantedPlant());

	m_plants.back().m_plantID = a_plantID;
	m_plants.back().m_tileIndex = a_tileIndex;
}

void CFarm::BindFarmTileMap(CTileMap & a_tileMap)
{
	m_tileMap = &a_tileMap;
}

void CFarm::Render()
{
	for (SPlantedPlant& plantData : m_plants)
	{
		const CPlant& plant = m_plantBank.GetPlant(plantData.m_plantID);

		plant.Render(m_tileMap->GetTilePosition(plantData.m_tileIndex), plantData.m_days);
	}
}

void CFarm::TickDay()
{
	for (SPlantedPlant& plant : m_plants)
	{
		if (m_tileMap->IsTileWatered(plant.m_tileIndex))
		{
			plant.m_days++;
		}
	}
}
