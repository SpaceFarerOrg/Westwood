#pragma once
#include "Avatar.h"
#include "Inventory.h"

class CPlayer
{
public:
	CPlayer(CAvatar& a_avatar);
	void Update();

	CInventory& GetInventory();

private:
	CAvatar & m_avatar;
	CInventory m_inventory;
	short m_activeTool;
};