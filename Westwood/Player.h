#pragma once
#include "Tool.h"
#include "ToolBank.h"
#include "Avatar.h"
#include "Inventory.h"

#include <array>

class CPlayer
{
public:
	CPlayer(CAvatar& a_avatar);
	void Init();
	void Update();

	CInventory& GetInventory();

private:
	CAvatar & m_avatar;

	CInventory m_inventory;
	CToolBank m_toolBank;

	short m_activeTool;
};