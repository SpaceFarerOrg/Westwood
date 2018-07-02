#include "Item.h"
#include <json.hpp>
#include <fstream>
#include "TextureBank.h"
#include "ItemBank.h"

CItem::CItem()
{
	m_name = "";
	m_description = "";
	m_isSeed = false;
	m_seedIndex = -1;
}

void CItem::LoadItem(nlohmann::json& a_itemJson)
{
	m_name = a_itemJson["name"].get<std::string>();
	m_description = a_itemJson["description"].get<std::string>();
	
	short itemsSpriteSize = static_cast<short>(CItemBank::GetInstance().GetItemsSpriteSize());

	short indexInTexture = a_itemJson["indexInSheet"].get<short>();
	short numberOfItemsInTextureRow = CTextureBank::GetTexture(ETextures::Items).getSize().x / itemsSpriteSize;

	m_renderRect.left = indexInTexture % numberOfItemsInTextureRow * itemsSpriteSize;
	m_renderRect.top = indexInTexture / numberOfItemsInTextureRow * itemsSpriteSize;
	m_renderRect.width = itemsSpriteSize;
	m_renderRect.height = itemsSpriteSize;

	if (a_itemJson.find("seedData") != a_itemJson.end())
	{
		m_isSeed = true;
		m_seedIndex = a_itemJson["seedData"].get<short>();
	}

	//Todo: Load all item parameters here
}

const sf::IntRect & CItem::GetRenderRect() const
{
	return m_renderRect;
}

const bool CItem::IsSeed() const
{
	return m_isSeed;
}

const short CItem::GetSeedID() const
{
	return m_seedIndex;
}
