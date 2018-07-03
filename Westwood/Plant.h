#pragma once
#include <json.hpp>
#include <SFML\System\String.hpp>
#include <SFML\System\Vector2.hpp>

class CPlant
{
public:
	void Load(nlohmann::json& a_thisPlantJson);

	const sf::String& GetName() const;
	bool IsMatured(short a_daysGrown) const;
	void Render(const sf::Vector2f& a_position, short a_daysGrown) const;
	short GetPlantAsItemID() const;
private:
	short GetGrowthStage(short a_daysGrown) const;
	sf::String m_name;
	short m_rowInSheet;
	short m_daysToMature;
	short m_spawnItemID;

};