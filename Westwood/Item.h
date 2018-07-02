#pragma once
#include <SFML\System\String.hpp>
#include <json.hpp>
#include <SFML\Graphics\Rect.hpp>
#include "Avatar.h"

class CItem
{
public:
	CItem();
	void LoadItem(nlohmann::json& a_itemJson);
	short GetItemID() const;
	const sf::String& GetName() const { return m_name; };
	const sf::String& GetDescription() const { return m_description; };
	const sf::IntRect& GetRenderRect() const;
	const bool IsSeed() const;
	const short GetSeedID() const;

	virtual void Use(CAvatar& a_user) {};
private:
	short m_itemId;
	sf::IntRect m_renderRect;
	sf::String m_name;
	sf::String m_description;

	bool m_isSeed;
	short m_seedIndex;
};