#include "WaterCan.h"
#include "ItemBank.h"
#include "Player.h"

void CWaterCan::Init()
{
	m_itemID = CItemBank::GetInstance().GetItemID("WaterCan");
	m_name = "WaterCan";
	m_energyDrainage = 5.f;
}

void CWaterCan::Use(CPlayer& a_user)
{
	ITool::Use(a_user);
	a_user.PerformWorldInteraction(ETileInteraction::Water, a_user.GetInteractPosition());
}