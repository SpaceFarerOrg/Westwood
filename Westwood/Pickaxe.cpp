#include "Pickaxe.h"
#include "ItemBank.h"

void CPickaxe::Init()
{
	m_itemID = CItemBank::GetInstance().GetItemID("Pickaxe");
}

void CPickaxe::Use(CAvatar& a_user)
{

}