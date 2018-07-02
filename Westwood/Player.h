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

class CPlayer : public CAvatar
{
public:
	CPlayer();
	void Init();
	void Update();
	void BindFarm(CFarm& a_farm);

	CInventory& GetInventory();
	bool GetShouldSleep();
	void WakeUp();
	void SetShouldSleep();

	sf::Vector2f GetInteractPosition() const;
	std::function<void()> GetOnInteractAllowedCallback() const;

	void DrainEnergy(float a_drainage);

private:
	void Faint();
	void DoInteraction();

	void SelectInventorySlot();
private:
	std::function<void()> m_onInteractAllowedCallback;

	CFarm* m_farm;

	CStatusBar m_energyStatus;

	CInventory m_inventory;
	CToolBank m_toolBank;

	short m_activeTool;
	bool m_shouldSleep : 1;
};