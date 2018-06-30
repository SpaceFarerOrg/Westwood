#pragma once
#include "Tool.h"
#include "ToolBank.h"
#include "Avatar.h"
#include "Inventory.h"
#include "StatusBar.h"

#include <array>

class CPlayer
{
public:

	CPlayer(CAvatar& a_avatar);
	void Init();
	void Update();

	CInventory& GetInventory();
	bool GetShouldSleep();
	void WakeUp();

	const sf::Vector2f& GetPosition() const;
private:
	void Faint();
private:
	CStatusBar m_energyStatus;

	CAvatar & m_avatar;

	CInventory m_inventory;
	CToolBank m_toolBank;

	short m_activeTool;
	bool m_shouldSleep : 1;
};