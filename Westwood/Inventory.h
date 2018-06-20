#pragma once
#include <array>
#include "Item.h"
#include "ToolBank.h"

struct SInventoryItem
{
	SInventoryItem()
	{
		m_itemCount = 0;
		m_itemId = 0;
	}

	SInventoryItem(short a_itemId)
	{
		m_itemId = a_itemId;
	}

	bool operator==(SInventoryItem a_other) const
	{
		return m_itemId == a_other.m_itemId;
	}

	short m_itemCount;
	short m_itemId;
};

class CInventory
{
public:
	CInventory();
	void BindToolBank(CToolBank& a_toolBank);

	void RenderInventory() const;

	bool IsFull();
	bool Contains(short a_itemId) const;
	void AddItemToInventory(short a_itemId, short a_amount = 1);
	
	void ChangeActiveSlot(short a_change);

	short GetActiveSlotItemID() const;

	bool GetIsDirty();
private:
	std::array<SInventoryItem, 10> m_slots;
	CToolBank* m_boundToolBank;

	short GetSlotIndex(short a_itemId) const;
	short m_activeSlot;
	short m_freeSlots;

	bool m_isDirty : 1;
};