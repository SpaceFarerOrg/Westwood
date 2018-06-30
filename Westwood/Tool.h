#pragma once
#include "Useable.h"

enum class EToolType
{
	Axe,
	Pickaxe,
	Shovel,
	Count
};

/*This one is just to ensure we can store tools separately but that they are useable*/
class ITool : public IUseable
{
public:
	virtual void Use(CPlayer& a_user) override;
protected:
	float m_energyDrainage;
};