#include "WorldZone.h"
#include "ItemBank.h"
#include <fstream>
#include "Math.h"

#include "Bed.h"
void CWorldZone::LoadZone(nlohmann::json & a_zoneJson)
{
	m_zoneName = a_zoneJson["name"].get<std::string>();

	std::ifstream tileMapFile("data/" + a_zoneJson["tileMap"].get<std::string>());
	
	nlohmann::json tileMapJson;
	tileMapFile >> tileMapJson;

	tileMapFile.close();

	m_tileMap.Load(tileMapJson, *this);

	/*
	DEBUG ADD BED
	*/
	m_objects.push_back(new CBed());
	m_objects.back()->SetPosition({ 0.f,0.f });
}

void CWorldZone::Render()
{
	m_tileMap.Render();

	for (SItemInWorldData& itemInWorld : m_items)
	{
		CItemBank::GetInstance().RenderItem(itemInWorld.a_itemID, itemInWorld.m_position);
	}

	for (CInteractableItem*& object : m_objects)
	{
		object->Render();
	}
	
}

void CWorldZone::EnterZone(CPlayer & a_player)
{
	m_player = &a_player;
}

void CWorldZone::LeaveZone()
{

}

void CWorldZone::CheckPlayerAgainstItems()
{
	std::vector<size_t> removedItems;

	for (size_t i = 0; i < m_items.size(); ++i)
	{
		SItemInWorldData& item = m_items[i];
		
		if (Math::GetLenght2(item.m_position - m_player->GetPosition()) < 10.f * 10.f)
		{
			CInventory& playerInventory = m_player->GetInventory();

			if (playerInventory.IsFull())
			{
				continue;
			}

			removedItems.push_back(i);

			playerInventory.AddItemToInventory(m_items[i].a_itemID);
		}
	}

	for (int i = static_cast<int>(removedItems.size()) - 1; i > -1; --i)
	{
		m_items.erase(m_items.begin() + removedItems[i]);
	}
}

sf::Vector2f CWorldZone::CheckForAllowedMove(const sf::Vector2f & a_targetPosition, const sf::Vector2f& a_currentPosition) const
{
	sf::Vector2f allowedPosition = m_tileMap.CheckForAllowedMove(a_targetPosition, a_currentPosition);

	return std::move(allowedPosition);
}

void CWorldZone::PerformWorldInteraction(ETileInteraction a_interaction, const sf::Vector2f & a_interactionPosition)
{
	for (CInteractableItem*& object : m_objects)
	{
		if (object->IsColliding(a_interactionPosition))
		{
			object->Interact(*m_player);
		}
	}

	m_tileMap.PerformInteraction(a_interactionPosition, a_interaction);
}

void CWorldZone::SpawnItem(short a_itemID, short a_amount, const sf::Vector2f& a_position)
{
	for (short i = 0; i < a_amount; ++i)
	{
		m_items.push_back({ a_itemID, a_position });
	}
}
