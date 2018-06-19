#pragma once
#include <SFML\System\Vector2.hpp>
#include "TileInteraction.h"

class CAvatar
{
public:
	CAvatar();

	void SetDirection(const sf::Vector2f& a_direction);
	void SetMovementSpeed(float a_movementSpeed);

	void SetDeltaTime(float a_deltaTime);

	const sf::Vector2f& GetPosition() const;

	sf::Vector2f GetFuturePosition() const;
	void AllowMoveTo(const sf::Vector2f& a_allowedNewPosition);

	const short GetCurrentZone() const;

	void PerformWorldInteraction(ETileInteraction a_interaction, const sf::Vector2f& a_atPosition);
	bool HasPerformedWorldInteraction(ETileInteraction& a_outInteraction, sf::Vector2f& a_outAtPosition);

	void Draw();
private:
	sf::Vector2f CalculateFuturePosition() const;

	sf::Vector2f m_position;
	sf::Vector2f m_currentDirection;

	ETileInteraction m_lastInteraction;
	sf::Vector2f m_interactedPosition;
	
	float m_currentDeltaTime;

	float m_movementSpeed;

	short m_currentZone;

	bool m_wasDirectionChanged : 1;
};