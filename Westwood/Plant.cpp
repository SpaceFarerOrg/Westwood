#include "Plant.h"
#include "Math.h"
#include <SFML\Graphics\Sprite.hpp>
#include "Renderer.h"
#include "TextureBank.h"
#include "ItemBank.h"

void CPlant::Load(nlohmann::json & a_thisPlantJson)
{
	m_name = a_thisPlantJson["name"].get<std::string>();
	m_rowInSheet = a_thisPlantJson["row"].get<short>();
	m_daysToMature = a_thisPlantJson["days"].get<short>() - 1;

	m_spawnItemID = CItemBank::GetInstance().GetItemID(m_name.toAnsiString().c_str());
}

const sf::String & CPlant::GetName() const
{
	return m_name;
}

bool CPlant::IsMatured(short a_daysGrown) const
{
	return m_daysToMature <= a_daysGrown;
}

void CPlant::Render(const sf::Vector2f & a_position, short a_daysGrown) const
{
	sf::Sprite sprite;
	sprite.setTexture(CTextureBank::GetTexture(ETextures::Plants));
	sf::IntRect sourceRect;
	sourceRect.width = 64;
	sourceRect.height = 64;
	sourceRect.top = m_rowInSheet * 64;
	sourceRect.left = GetGrowthStage(a_daysGrown) * 64;

	sprite.setTextureRect(sourceRect);
	sprite.setPosition(a_position);

	CRenderer::GetInstance().PushRenderCommand(sprite, LAYER_OBJECT);
}

short CPlant::GetPlantAsItemID() const
{
	return m_spawnItemID;
}

short CPlant::GetGrowthStage(short a_daysGrown) const
{
	short stage = Math::Clamp<short>(a_daysGrown, 0, 5);

	return stage;
}

