#pragma once
#include "Useable.h"
#include <string>

class CWorldZone;

enum class EToolType
{
	Axe,
	Pickaxe,
	Shovel,
	WaterCan,
	Count
};

/*This one is just to ensure we can store tools separately but that they are useable*/
class ITool : public IUseable
{
public:
	virtual void Use(CPlayer& a_user, CWorldZone& a_zone) override;
	const std::string& GetItemName();
protected:
	float m_energyDrainage;
	std::string m_name;
};