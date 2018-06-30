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
protected:
	float m_energyDrainage;
};