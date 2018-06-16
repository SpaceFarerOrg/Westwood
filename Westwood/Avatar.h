#pragma once
#include <SFML\System\Vector2.hpp>

class CAvatar
{
public:
	void SetDirection(const sf::Vector2f& a_direction);
	void SetMovementSpeed(float a_movementSpeed);

	void SetDeltaTime(float a_deltaTime);

	const sf::Vector2f& GetPosition() const;

	sf::Vector2f GetFuturePosition() const;
	void AllowMoveTo(const sf::Vector2f& a_allowedNewPosition);

	const short GetCurrentZone() const;

	void Draw();
private:
	sf::Vector2f CalculateFuturePosition() const;

	sf::Vector2f m_position;
	sf::Vector2f m_currentDirection;
	
	float m_currentDeltaTime;

	float m_movementSpeed;

	short m_currentZone;

	bool m_wasDirectionChanged : 1;
};