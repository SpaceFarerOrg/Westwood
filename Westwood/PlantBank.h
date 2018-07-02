#pragma once
#include <vector>
#include <unordered_map>
#include <string>
#include "Plant.h"

class CPlantBank
{
public:
	void LoadAllPlants();
	short GetPlantID(const char* a_plantName) const;

	const CPlant& GetPlant(short a_plant) const;
private:
	std::unordered_map<std::string, short> m_plantNameToIndexLUT;
	std::vector<CPlant> m_plants;
};