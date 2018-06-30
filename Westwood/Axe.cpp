#include "Axe.h"
#include "ItemBank.h"
#include "Player.h"

void CAxe::Init()
{
	m_itemID = CItemBank::GetInstance().GetItemID("Axe");
}

void CAxe::Use(CPlayer& a_user)
{

}