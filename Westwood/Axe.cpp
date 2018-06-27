#include "Axe.h"
#include "ItemBank.h"

void CAxe::Init()
{
	m_itemID = CItemBank::GetInstance().GetItemID("Axe");
}

void CAxe::Use(CAvatar& a_user)
{

}