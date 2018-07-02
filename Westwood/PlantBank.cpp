#include "PlantBank.h"
#include <json.hpp>
#include <fstream>

void CPlantBank::LoadAllPlants()
{
	nlohmann::json plantsJson;
	std::ifstream plantsFile("data/plants.json");
	plantsFile >> plantsJson;
	plantsFile.close();

	m_plants.reserve(plantsJson["plants"].size());

	for (size_t i = 0; i < plantsJson["plants"].size(); ++i)
	{
		m_plants.push_back(CPlant());
		m_plants.back().Load(plantsJson["plants"][i]);
		m_plantNameToIndexLUT[m_plants.back().GetName().toAnsiString()] = static_cast<short>(i);
	}
}

short CPlantBank::GetPlantID(const char * a_plantName) const
{
	return m_plantNameToIndexLUT.at(a_plantName);
}

const CPlant & CPlantBank::GetPlant(short a_plant) const
{
	return m_plants[a_plant];
}
