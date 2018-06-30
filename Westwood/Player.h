#pragma once
#include "Tool.h"
#include "ToolBank.h"
#include "Avatar.h"
#include "Inventory.h"
#include "StatusBar.h"

#include <array>

class CPlayer : public CAvatar
{
public:

	CPlayer();
	void Init();
	void Update();

	CInventory& GetInventory();
	bool GetShouldSleep();
	void WakeUp();

	void DrainEnergy(float a_drainage);
private:
	void Faint();
	void DoInteraction();
private:
	CStatusBar m_energyStatus;

	CInventory m_inventory;
	CToolBank m_toolBank;

	short m_activeTool;
	bool m_shouldSleep : 1;
};