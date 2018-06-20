#include "Shovel.h"
#include "ItemBank.h"

void CShovel::Init()
{
	m_itemID = CItemBank::GetInstance().GetItemID("Shovel");
}

void CShovel::Use(CAvatar & a_user)
{
	a_user.PerformWorldInteraction(ETileInteraction::Dig, a_user.GetPosition());
}
