#pragma once
#include "Tool.h"
#include "ToolBank.h"
#include "Avatar.h"
#include "Inventory.h"
#include "StatusBar.h"
#include <SFML/Audio/Sound.hpp>
#include <functional>
#include <array>
#include "Farm.h"
#include "WorldZone.h"

class CPlayer : public CAvatar
{
public:
	CPlayer();
	void Init();
	void Update();
	void BindFarm(CFarm& a_farm);
	void SetCurrentZone(CWorldZone& a_zone);

	CInventory& GetInventory();
	bool GetShouldSleep();
	void WakeUp();
	void SetShouldSleep();

	sf::Vector2f GetInteractPosition() const;

	void DrainEnergy(float a_drainage);

private:
	void Faint();
	void DoInteraction();

	void SelectInventorySlot();
private:
	CFarm* m_farm;

	CWorldZone* m_currentZone;
	
	CStatusBar m_energyStatus;

	CInventory m_inventory;
	CToolBank m_toolBank;

	short m_activeTool;
	bool m_shouldSleep : 1;
};