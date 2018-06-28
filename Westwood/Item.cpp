#include "Item.h"
#include <json.hpp>
#include <fstream>
#include "TextureBank.h"
#include "ItemBank.h"

CItem::CItem()
{
	m_name = "";
	m_description = "";
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

	//Todo: Load all item parameters here
}

const sf::IntRect & CItem::GetRenderRect() const
{
	return m_renderRect;
}
