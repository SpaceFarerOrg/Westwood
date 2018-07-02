#include "Shovel.h"
#include "ItemBank.h"
#include "Player.h"

void CShovel::Init()
{
	m_itemID = CItemBank::GetInstance().GetItemID("Shovel");
	m_energyDrainage = 10.f;
	m_name = "Shovel";
}

void CShovel::Use(CPlayer & a_user, CWorldZone& a_zone)
{
	ITool::Use(a_user, a_zone);
	a_zone.GetTileMap().Dig(a_user.GetInteractPosition());
}

