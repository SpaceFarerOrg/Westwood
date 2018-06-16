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

void CAvatar::SetDeltaTime(float a_deltaTime)
{
	m_currentDeltaTime = a_deltaTime;
}

sf::Vector2f CAvatar::GetFuturePosition() const
{
	return std::move(CalculateFuturePosition());
}

void CAvatar::AllowMove(bool a_moveWasAllowed)
{
	//Only update the position to the one desired if the move was allowed from the world
	if (a_moveWasAllowed)
	{
		m_position = CalculateFuturePosition();
	}
}

const short CAvatar::GetCurrentZone() const
{
	return m_currentZone;
}

sf::Vector2f CAvatar::CalculateFuturePosition() const
{
	sf::Vector2f futurePos = m_position + m_currentDirection * m_movementSpeed * m_currentDeltaTime;

	return std::move(futurePos);
}
