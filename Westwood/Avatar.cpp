#include "Avatar.h"
#include <utility>
#include "Math.h"

CAvatar::CAvatar()
{
	m_currentZone = 0;

	//These are offsets from the sprite position
	m_collisionPoints[0] = { 0.f, 64.f };
	m_collisionPoints[1] = { 32.f, 64.f };
	m_collisionPoints[2] = { 0.f, 32.f };
	m_collisionPoints[3] = { 32.f, 32.f };
}

CAvatar::CAvatar(const CAvatar & a_avatar)
{
	// This just needed to exist
}

void CAvatar::SetDirection(const sf::Vector2f & a_direction)
{
	if (a_direction != m_currentDirection)
	{
		m_wasDirectionChanged = true;
	}

	m_currentDirection = a_direction;

	if (fabs(m_currentDirection.x) > 0.f)
	{
		m_facingDirection = { m_currentDirection.x, 0 };
	}
	else if (fabs(m_currentDirection.y) > 0.f)
	{
		m_facingDirection = { 0, m_currentDirection.y };
	}
}

void CAvatar::SetMovementSpeed(float a_movementSpeed)
{
	m_movementSpeed = a_movementSpeed;
}

void CAvatar::SetDeltaTime(float a_deltaTime)
{
	m_currentDeltaTime = a_deltaTime;

	UpdateAnimationCollection();
}

float CAvatar::GetDeltaTime()
{
	return m_currentDeltaTime;
}

const sf::Vector2f & CAvatar::GetPosition() const
{
	return m_position;
}

void CAvatar::SetPosition(const sf::Vector2f & a_position)
{
	m_position = a_position;
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

#include <SFML\Graphics\Sprite.hpp>
#include "Renderer.h"
#include "TextureBank.h"
const sf::Vector2f & CAvatar::GetFacingDirection() const
{
	return m_facingDirection;
}
void CAvatar::Draw()
{
	//m_animationCollection.Render(m_position);

	m_characterCollection.Render(m_position);
}

void CAvatar::UpdateAnimationCollection()
{
	m_animationCollection.Update(m_currentDeltaTime);
}


sf::Vector2f CAvatar::CalculateFuturePositionOfCollisionPoint(short a_collisionPoint) const
{
	sf::Vector2f futurePos = (m_position + m_collisionPoints[a_collisionPoint]) + m_currentDirection * m_movementSpeed * m_currentDeltaTime;

	return std::move(futurePos);
}
