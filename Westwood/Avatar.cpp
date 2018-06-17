#include "Avatar.h"
#include <utility>

void CAvatar::SetDirection(const sf::Vector2f & a_direction)
{
	if (a_direction != m_currentDirection)
	{
		m_wasDirectionChanged = true;
	}

	m_currentDirection = a_direction;
}

void CAvatar::SetMovementSpeed(float a_movementSpeed)
{
	m_movementSpeed = a_movementSpeed;
}

void CAvatar::SetDeltaTime(float a_deltaTime)
{
	m_currentDeltaTime = a_deltaTime;
}

const sf::Vector2f & CAvatar::GetPosition() const
{
	return m_position;
}

sf::Vector2f CAvatar::GetFuturePosition() const
{
	return std::move(CalculateFuturePosition());
}

void CAvatar::AllowMoveTo(const sf::Vector2f& a_allowedNewPosition)
{
	m_position = a_allowedNewPosition;
}

const short CAvatar::GetCurrentZone() const
{
	return m_currentZone;
}

#include <SFML\Graphics\Sprite.hpp>
#include "Renderer.h"
#include "TextureBank.h"
void CAvatar::Draw()
{
	sf::Sprite sprite;
	sprite.setTexture(CTextureBank::GetTexture(ETextures::PlayerCharacter));

	sprite.setPosition(m_position);

	CRenderer::GetInstance().PushRenderCommand(sprite);
}


sf::Vector2f CAvatar::CalculateFuturePosition() const
{
	sf::Vector2f futurePos = m_position + m_currentDirection * m_movementSpeed * m_currentDeltaTime;

	return std::move(futurePos);
}
