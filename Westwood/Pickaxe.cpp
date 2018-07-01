#include "Pickaxe.h"
#include "ItemBank.h"
#include "Player.h"

void CPickaxe::Init()
{
	m_itemID = CItemBank::GetInstance().GetItemID("Pickaxe");
	m_name = "Pickaxe";
}

void CPickaxe::Use(CPlayer& a_user)
{
	ITool::Use(a_user);
}