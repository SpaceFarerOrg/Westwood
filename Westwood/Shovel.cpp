#include "Shovel.h"
#include "ItemBank.h"
#include "Player.h"

void CShovel::Init()
{
	m_itemID = CItemBank::GetInstance().GetItemID("Shovel");
	m_energyDrainage = 10.f;
}

void CShovel::Use(CPlayer & a_user)
{
	a_user.DrainEnergy(m_energyDrainage);
	a_user.PerformWorldInteraction(ETileInteraction::Dig, a_user.GetPosition() + (a_user.GetFacingDirection() * 64.f));
}
