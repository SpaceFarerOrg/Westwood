#include "Avatar.h"
#include <utility>

CAvatar::CAvatar()
{
	m_lastInteraction = ETileInteraction::Count;
	m_currentZone = 0;

	//These are offsets from the sprite position
	m_collisionPoints[0] = { 0.f, 64.f };
	m_collisionPoints[1] = { 32.f, 64.f };
	m_collisionPoints[2] = { 0.f, 32.f };
	m_collisionPoints[3] = { 32.f, 32.f };
	
}

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

sf::Vector2f CAvatar::GetPositionOfCollisionPoint(short a_collisionPoint) const
{
	return std::move(m_position + m_collisionPoints[a_collisionPoint]);
}

sf::Vector2f CAvatar::GetFuturePositionOfCollisionPoint(short a_collisionPoint) const
{
	return std::move(CalculateFuturePositionOfCollisionPoint(a_collisionPoint));
}

void CAvatar::AllowMove(const sf::Vector2f& a_allowedMove)
{
	m_position += a_allowedMove;
}

const short CAvatar::GetCurrentZone() const
{
	return m_currentZone;
}

void CAvatar::PerformWorldInteraction(ETileInteraction a_interaction, const sf::Vector2f & a_atPosition)
{
	m_lastInteraction = a_interaction;
	m_interactedPosition = a_atPosition;
}

bool CAvatar::HasPerformedWorldInteraction(ETileInteraction & a_outInteraction, sf::Vector2f & a_outAtPosition)
{
	if (m_lastInteraction != ETileInteraction::Count)
	{
		a_outInteraction = m_lastInteraction;
		m_lastInteraction = ETileInteraction::Count;

		a_outAtPosition = m_interactedPosition;

		return true;
	}

	return false;
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


sf::Vector2f CAvatar::CalculateFuturePositionOfCollisionPoint(short a_collisionPoint) const
{
	sf::Vector2f futurePos = (m_position + m_collisionPoints[a_collisionPoint]) + m_currentDirection * m_movementSpeed * m_currentDeltaTime;

	return std::move(futurePos);
}
