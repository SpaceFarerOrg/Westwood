#include "WaterCan.h"
#include "ItemBank.h"
#include "Player.h"

void CWaterCan::Init()
{
	m_itemID = CItemBank::GetInstance().GetItemID("WaterCan");
	m_name = "WaterCan";
}

void CWaterCan::Use(CPlayer& a_user)
{
	ITool::Use(a_user);
}