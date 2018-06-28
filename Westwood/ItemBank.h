#pragma once
#include "Item.h"
#include <vector>
#include <unordered_map>
#include <string>
#include <SFML\System\Vector2.hpp>

class CItemBank
{
public:
	static CItemBank & GetInstance();

	void LoadAllItems(const char* a_itemsFilePath);
	short GetItemID(const char* a_itemName) const;

	const CItem& GetItem(short a_itemID) const;

	size_t GetItemCount() const;

	void RenderItem(short a_itemID, const sf::Vector2f& a_position, bool a_shouldRenderAsUI = false) const;

	float GetItemsSpriteSize() const;
private:
	CItemBank();
	std::vector<CItem> m_items;
	std::unordered_map<std::string, short> m_itemNameToIdLUT;

	float m_itemSpriteSize;
};