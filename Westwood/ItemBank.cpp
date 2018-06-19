#include "ItemBank.h"
#include <fstream>

CItemBank & CItemBank::GetInstance()
{
	static CItemBank instance;

	return instance;
}

void CItemBank::LoadAllItems(const char * a_itemsFilePath)
{
	nlohmann::json itemsJson;
	std::fstream itemsFile(a_itemsFilePath);
	itemsFile >> itemsJson;
	itemsFile.close();

	short amountOfItems = itemsJson["items"].size();
	m_items.reserve(amountOfItems);

	for (short i = 0; i < amountOfItems; ++i)
	{
		m_items.push_back(CItem());
		m_items.back().LoadItem(itemsJson["items"][i]);

		m_itemNameToIdLUT[m_items.back().GetName()] = i;
	}
}

short CItemBank::GetItemID(const char * a_itemName) const
{
	short id = -1;

	if (m_itemNameToIdLUT.find(a_itemName) != m_itemNameToIdLUT.end())
	{
		id = m_itemNameToIdLUT.at(a_itemName);
	}

	return id;
}

const CItem & CItemBank::GetItem(short a_itemID) const
{
	const CItem& item = m_items.at(a_itemID);

	return item;
}

#include "TextureBank.h"
#include "Renderer.h"
void CItemBank::RenderItem(short a_itemID, const sf::Vector2f & a_position, bool a_shouldRenderAsUI) const
{
	sf::Sprite sprite;
	sprite.setTexture(CTextureBank::GetTexture(ETextures::Items));
	sprite.setTextureRect(m_items[a_itemID].GetRenderRect());
	sprite.setPosition(a_position);

	if (a_shouldRenderAsUI)
	{
		CRenderer::GetInstance().PushUIRenderCommand(sprite);
	}
	else
	{
		CRenderer::GetInstance().PushRenderCommand(sprite);
	}
}

CItemBank::CItemBank()
{
	m_itemSpriteSize = 32;
}
