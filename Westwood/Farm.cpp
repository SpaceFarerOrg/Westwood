#include "Farm.h"
#include "GameEventMaster.h"
#include "TileMap.h"
#include "WorldZone.h"

CFarm::CFarm()
{
	CGameEventMaster::GetInstance().SubscribeToEvent(EGameEvent::FadeReachBlack, [this] {this->TickDay(); });
}

void CFarm::Init()
{
	m_plantBank.LoadAllPlants();
}

void CFarm::PlantSeed(const char * a_plantName, short a_tileIndex)
{
	short plantID = m_plantBank.GetPlantID(a_plantName);

	PlantSeed(plantID, a_tileIndex);
}

void CFarm::PlantSeed(short a_plantID, short a_tileIndex)
{
	m_plants[a_tileIndex].m_plantID = a_plantID;
	m_plants[a_tileIndex].m_days = 0;
}

void CFarm::BindFarmTileMap(CTileMap & a_tileMap)
{
	m_tileMap = &a_tileMap;
}

bool CFarm::TileContainsSeed(short a_tileIndex)
{
	bool foundSeed = false;

	if(m_plants.find(a_tileIndex) != m_plants.end())
	{
		foundSeed = true;
	}

	return foundSeed;
}

bool CFarm::TryHarvest(short a_tileIndex, CWorldZone* a_zone)
{
	if (m_plants.find(a_tileIndex) == m_plants.end())
	{
		return false;
	}

	const CPlant& relevantPlant = m_plantBank.GetPlant(m_plants[a_tileIndex].m_plantID);

	if (relevantPlant.IsMatured(m_plants[a_tileIndex].m_days))
	{
		a_zone->SpawnItem(relevantPlant.GetPlantAsItemID(), 1, a_zone->GetTileMap().GetTilePosition(a_tileIndex));

		m_plants.erase(a_tileIndex);

		return true;
	}


	return false;

}

void CFarm::Render()
{
	for (auto& plantData : m_plants)
	{
		const CPlant& plant = m_plantBank.GetPlant(plantData.second.m_plantID);

		plant.Render(m_tileMap->GetTilePosition(plantData.first), plantData.second.m_days);
	}
}

void CFarm::TickDay()
{
	for (auto& plant : m_plants)
	{
		if (m_tileMap->IsTileWatered(plant.first))
		{
			plant.second.m_days += 1;
		}
	}
}
