#include "Item.h"
#include <json.hpp>
#include <fstream>
#include "TextureBank.h"

CItem::CItem()
{
	m_name = "";
	m_description = "";
}

void CItem::LoadItem(nlohmann::json& a_itemJson)
{
	m_name = a_itemJson["name"].get<std::string>();
	m_description = a_itemJson["description"].get<std::string>();
	
	short indexInTexture = a_itemJson["indexInSheet"].get<short>();
	short numberOfItemsInTextureRow = CTextureBank::GetTexture(ETextures::Items).getSize().x / 32;

	m_renderRect.left = indexInTexture % numberOfItemsInTextureRow * 32;
	m_renderRect.top = indexInTexture / numberOfItemsInTextureRow * 32;
	m_renderRect.width = 32;
	m_renderRect.height = 32;

	//Todo: Load all item parameters here
}

const sf::IntRect & CItem::GetRenderRect() const
{
	return m_renderRect;
}
