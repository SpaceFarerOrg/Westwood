#pragma once
#include <SFML\System\Vector2.hpp>
#include "TileInteraction.h"
#include <array>

class CAvatar
{
public:
	CAvatar();

	void SetDirection(const sf::Vector2f& a_direction);
	void SetMovementSpeed(float a_movementSpeed);

	void SetDeltaTime(float a_deltaTime);

	const sf::Vector2f& GetPosition() const;

	sf::Vector2f GetPositionOfCollisionPoint(short a_collisionPoint) const;

	sf::Vector2f GetFuturePositionOfCollisionPoint(short a_collisionPoint) const;
	void AllowMove(const sf::Vector2f& a_allowedMove);

	const short GetCurrentZone() const;

	void PerformWorldInteraction(ETileInteraction a_interaction, const sf::Vector2f& a_atPosition);
	bool HasPerformedWorldInteraction(ETileInteraction& a_outInteraction, sf::Vector2f& a_outAtPosition);

	void Draw();
private:
	sf::Vector2f CalculateFuturePositionOfCollisionPoint(short a_collisionPoint) const;

	sf::Vector2f m_position;
	sf::Vector2f m_currentDirection;

	ETileInteraction m_lastInteraction;
	sf::Vector2f m_interactedPosition;

	std::array<sf::Vector2f, 4> m_collisionPoints;

	float m_currentDeltaTime;

	float m_movementSpeed;

	short m_currentZone;

	bool m_wasDirectionChanged : 1;
};