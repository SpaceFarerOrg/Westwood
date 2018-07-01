#include "Axe.h"
#include "ItemBank.h"
#include "Player.h"

void CAxe::Init()
{
	m_itemID = CItemBank::GetInstance().GetItemID("Axe");
	m_name = "Axe";
}

void CAxe::Use(CPlayer& a_user)
{
	ITool::Use(a_user);
}