#pragma once
#include <vector>
#include "PlantBank.h"
#include <SFML\System\Vector2.hpp>

class CFarm
{
public:
	CFarm();
	void PlantSeed(const char* a_plantName, const sf::Vector2f& a_onPosition);
	void PlantSeed(short a_plantID, const sf::Vector2f& a_onPosition);

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
		sf::Vector2f m_position;
	};

	void TickDay();
private:
	std::vector<SPlantedPlant> m_plants;
	CPlantBank m_plantBank;
};