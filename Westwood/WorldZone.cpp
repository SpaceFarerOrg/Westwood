#include "WorldZone.h"
#include "ItemBank.h"
#include <fstream>
#include "Math.h"
#include "Player.h"
#include "Bed.h"

void CWorldZone::LoadZone(nlohmann::json & a_zoneJson)
{
	m_zoneName = a_zoneJson["name"].get<std::string>();

	std::ifstream tileMapFile("data/" + a_zoneJson["tileMap"].get<std::string>());
	
	nlohmann::json tileMapJson;
	tileMapFile >> tileMapJson;

	tileMapFile.close();

	m_tileMap.Load(tileMapJson, *this);
	LoadObjects(tileMapJson);
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

void CWorldZone::EnterZone()
{

}

void CWorldZone::LeaveZone()
{

}

CTileMap & CWorldZone::GetTileMap()
{
	return m_tileMap;
}

void CWorldZone::CheckPlayerAgainstItems(CPlayer& a_player)
{
	std::vector<size_t> removedItems;

	for (size_t i = 0; i < m_items.size(); ++i)
	{
		SItemInWorldData& item = m_items[i];
		
		if (Math::GetLenght2(item.m_position - a_player.GetPosition()) < 10.f * 10.f)
		{
			CInventory& playerInventory = a_player.GetInventory();

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

CInteractableItem * CWorldZone::GetTargetedObject(const sf::Vector2f & a_targetPosition)
{
	CInteractableItem* item = nullptr;

	for (CInteractableItem*& object : m_objects)
	{
		if (object->IsColliding(a_targetPosition))
		{
			item = object;
		}
	}

	return item;
}

void CWorldZone::SpawnItem(short a_itemID, short a_amount, const sf::Vector2f& a_position)
{
	for (short i = 0; i < a_amount; ++i)
	{
		m_items.push_back({ a_itemID, a_position });
	}
}

void CWorldZone::LoadObjects(nlohmann::json & a_tileMapJson)
{
	int amountOfObjects = a_tileMapJson["layers"][1]["objects"].size();

	for (int i = 0; i < amountOfObjects; ++i)
	{
		nlohmann::json objectData = a_tileMapJson["layers"][1]["objects"][i];

		std::string objectType = objectData["type"];

		if (objectType == "bed")
		{
			m_objects.push_back(new CBed());
			sf::Vector2f position;
			position.x = objectData["x"];
			position.y = objectData["y"];
			// Tiled saves positon with origin at bottom left, this corrects that
			int offset = objectData["height"];
			position.y -= offset;

			m_objects.back()->SetPosition(position);
		}
	}
}
