#include "InteractableItem.h"
#include <SFML\Graphics\Sprite.hpp>
#include "TextureBank.h"
#include "Renderer.h"

void CInteractableItem::Init(float a_width, float a_height, const sf::IntRect& a_sourceRectInObjectSheet)
{
	m_collisionRect.width = a_width;
	m_collisionRect.height = a_height;
	m_textureRect = a_sourceRectInObjectSheet;
}

bool CInteractableItem::IsColliding(const sf::Vector2f & a_point)
{
	if (m_collisionRect.contains(a_point))
	{
		return true;
	}

	return false;
}

void CInteractableItem::SetPosition(const sf::Vector2f & a_position)
{
	m_position = a_position;
	m_collisionRect.left = m_position.x;
	m_collisionRect.top = m_position.y;
}

void CInteractableItem::Render()
{
	sf::Sprite sprite;
	sprite.setTexture(CTextureBank::GetTexture(ETextures::Objects));
	sprite.setTextureRect(m_textureRect);
	sprite.setPosition(m_position);

	CRenderer::GetInstance().PushRenderCommand(sprite, LAYER_OBJECT);
}
