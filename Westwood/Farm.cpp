#include "Farm.h"
#include "GameEventMaster.h"

CFarm::CFarm()
{
	m_plantBank.LoadAllPlants();
	CGameEventMaster::GetInstance().SubscribeToEvent(EGameEvent::FadeReachBlack, [this] {this->TickDay(); });
}

void CFarm::PlantSeed(const char * a_plantName, const sf::Vector2f& a_onPosition)
{
	short plantID = m_plantBank.GetPlantID(a_plantName);

	PlantSeed(plantID, a_onPosition);
}

void CFarm::PlantSeed(short a_plantID, const sf::Vector2f& a_onPosition)
{
	m_plants.push_back(SPlantedPlant());

	m_plants.back().m_plantID = a_plantID;
	m_plants.back().m_position = a_onPosition;
}

void CFarm::Render()
{
	for (SPlantedPlant& plantData : m_plants)
	{
		const CPlant& plant = m_plantBank.GetPlant(plantData.m_plantID);

		plant.Render(plantData.m_position, plantData.m_days);
	}
}

void CFarm::TickDay()
{
	for (SPlantedPlant& plant : m_plants)
	{
		plant.m_days++;
	}
}
