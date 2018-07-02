#include "WaterCan.h"
#include "ItemBank.h"
#include "Player.h"

void CWaterCan::Init()
{
	m_itemID = CItemBank::GetInstance().GetItemID("WaterCan");
	m_name = "WaterCan";
	m_energyDrainage = 5.f;
}

void CWaterCan::Use(CPlayer& a_user, CWorldZone& a_zone)
{
	ITool::Use(a_user, a_zone);
	a_zone.GetTileMap().Water(a_user.GetInteractPosition());
}