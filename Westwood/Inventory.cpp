#include "Inventory.h"
#include "ItemBank.h"
#include "GameEventMaster.h"

CInventory::CInventory()
{
	m_freeSlots = static_cast<short>(m_slots.max_size());
	m_activeSlot = 0;
	m_isOpen = false;
	m_isOwnedByPlayer = false;
}

void CInventory::BindToolBank(CToolBank & a_toolBank)
{
	m_boundToolBank = &a_toolBank;
}

void CInventory::SetIsOwnedByPlayer()
{
	m_isOwnedByPlayer = true;
}

void CInventory::OpenInventory()
{
	CGameEventMaster::GetInstance().SendGameEvent(EGameEvent::PauseTime);
	m_isOpen = true;
}

void CInventory::CloseInventory()
{
	CGameEventMaster::GetInstance().SendGameEvent(EGameEvent::ContinueTime);
	m_isOpen = false;
}

bool CInventory::IsFull()
{
	bool full = m_freeSlots == 0;

	return full;
}

void CInventory::AddItemToInventory(short a_itemId, short a_amount)
{
	short slotIndexIfExisting = GetSlotIndex(a_itemId);

	if (slotIndexIfExisting != -1)
	{
		//Adds to current stack
		m_slots[slotIndexIfExisting].m_itemCount += a_amount;
	}
	else if(!IsFull()) //Does not assume I will remember to do full checks each time
	{
		for (short freeSlotIndex = 0; freeSlotIndex < m_slots.max_size(); ++freeSlotIndex)
		{
			if (m_slots[freeSlotIndex] == 0)
			{
				m_slots[freeSlotIndex].m_itemId = a_itemId;
				m_slots[freeSlotIndex].m_itemCount = a_amount;

				m_freeSlots--;
				break;
			}
		}
	}
}

short CInventory::GetSlotIndex(short a_itemId) const
{
	for (short i = 0; i < m_slots.max_size(); ++i)
	{
		if (m_slots[i] == a_itemId)
		{
			return i;
		}
	}

	return -1;
}

bool CInventory::Contains(short a_itemId) const
{
	short slotIndex = GetSlotIndex(a_itemId);

	if (slotIndex == -1)
	{
		return false;
	}

	return true;
}

#include "Renderer.h"
void CInventory::RenderInventory()
{
	if (m_isOpen == false && m_isOwnedByPlayer)
	{
		RenderAsClosed();
	}
	else if(m_isOpen == true)
	{
		RenderAsOpen();
	}

}

void CInventory::ChangeActiveSlot(short a_change)
{
	//This is mostly an edge case as only the player can change inventory slot
	//But when the inventory is opened we do not want to let the player change slots
	if (m_isOpen == true)
	{
		return;
	}

	m_activeSlot += a_change;

	if (m_activeSlot < 0)
	{
		m_activeSlot = m_slots.max_size() - 1;
	}
	else if(m_activeSlot >= m_slots.max_size())
	{
		m_activeSlot = 0;
	}

	m_boundToolBank->SetRelevantToolAsActive(m_slots[m_activeSlot].m_itemId);

	m_isDirty = true;
}

short CInventory::GetActiveSlotItemID() const
{
	short itemID = m_slots[m_activeSlot].m_itemId;

	return itemID;
}

bool CInventory::GetIsDirty()
{
	if (m_isDirty)
	{
		m_isDirty = false;
		return true;
	}

	return false;
}

#include "InputManager.h"
#include "TextureBank.h"
void CInventory::RenderAsOpen()
{
	if (CInputManager::GetInstance().IsKeyPressed(EKeyCode::Escape))
	{
		CloseInventory();
	}

	sf::Vector2f positionToRenderItem;

	float totalWOfInventory = 32.f * static_cast<float>(m_slots.max_size());

	positionToRenderItem.x = (CRenderer::GetInstance().GetWindowDimensions().x / 2.f) - (totalWOfInventory / 2.f);
	positionToRenderItem.y = (CRenderer::GetInstance().GetWindowDimensions().y / 2.f) - 16.f;

	short hoveredItem = -1;

	for (short i = 0; i < m_slots.max_size(); ++i)
	{
		CItemBank::GetInstance().RenderItem(m_slots[i].m_itemId, positionToRenderItem, true);

		sf::FloatRect mouseCollisionRect;
		mouseCollisionRect.left = positionToRenderItem.x;
		mouseCollisionRect.top = positionToRenderItem.y;
		mouseCollisionRect.width = 32.f;
		mouseCollisionRect.height = 32.f;

		if (mouseCollisionRect.contains(CInputManager::GetInstance().GetMousePosFloat()))
		{
			hoveredItem = m_slots[i].m_itemId;
		}

		positionToRenderItem.x += 32;
	}

	if (hoveredItem != -1)
	{
		RenderItemInformation(hoveredItem, CInputManager::GetInstance().GetMousePosFloat());
	}
}

void CInventory::RenderAsClosed()
{
	sf::Vector2f positionToRenderItem;

	float totalWOfInventory = 32.f * static_cast<float>(m_slots.max_size());

	positionToRenderItem.x = (CRenderer::GetInstance().GetWindowDimensions().x / 2.f) - (totalWOfInventory / 2.f);
	positionToRenderItem.y = CRenderer::GetInstance().GetWindowDimensions().y - 64.f;

	for (short i = 0; i < m_slots.max_size(); ++i)
	{
		if (i == m_activeSlot)
		{
			sf::RectangleShape rect;
			rect.setFillColor(sf::Color(255, 255, 255, 50));
			rect.setSize({ 32.f, 32.f });
			rect.setPosition(positionToRenderItem);

			CRenderer::GetInstance().PushUIRenderCommand(rect);
		}

		CItemBank::GetInstance().RenderItem(m_slots[i].m_itemId, positionToRenderItem, true);

		positionToRenderItem.x += 32;
	}
}

void CInventory::RenderItemInformation(short a_itemID, const sf::Vector2f & a_atPosition)
{
	const CItem& hoveredItem = CItemBank::GetInstance().GetItem(a_itemID);

	sf::String itemInfoString;
	itemInfoString = hoveredItem.GetName() + "\n" + hoveredItem.GetDescription();

	sf::Text itemInfo;
	itemInfo.setFont(CTextureBank::GetFont(EFonts::Debug));
	itemInfo.setString(itemInfoString);

	itemInfo.setOrigin(itemInfo.getLocalBounds().width / 2.f, itemInfo.getLocalBounds().height);
	itemInfo.setPosition(a_atPosition);

	CRenderer::GetInstance().PushUIRenderCommand(itemInfo);
}
