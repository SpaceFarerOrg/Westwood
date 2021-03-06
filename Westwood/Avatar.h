#pragma once
#include <SFML\System\Vector2.hpp>
#include "TileInteraction.h"
#include <array>
#include "AnimationCollection.h"
#include "CharacterCollection.h"

class CAvatar
{
public:
	CAvatar();
	CAvatar(const CAvatar& a_avatar);

	void SetDirection(const sf::Vector2f& a_direction);
	void SetMovementSpeed(float a_movementSpeed);

	void SetDeltaTime(float a_deltaTime);
	float GetDeltaTime();

	const sf::Vector2f& GetPosition() const;
	void SetPosition(const sf::Vector2f& a_position);
	sf::Vector2f GetPositionOfCollisionPoint(short a_collisionPoint) const;
	sf::Vector2f GetFuturePositionOfCollisionPoint(short a_collisionPoint) const;
	
	const short GetCurrentZone() const;
	
	void AllowMove(const sf::Vector2f& a_allowedMove);

	const sf::Vector2f& GetFacingDirection() const;
	void Draw();
protected:
	void UpdateAnimationCollection();

	CCharacterCollection m_characterCollection;

	sf::Vector2f CalculateFuturePositionOfCollisionPoint(short a_collisionPoint) const;

	sf::Vector2f m_position;
	sf::Vector2f m_currentDirection;
	sf::Vector2f m_facingDirection;

	sf::Vector2f m_interactedPosition;

	std::array<sf::Vector2f, 4> m_collisionPoints;

	float m_currentDeltaTime;

	float m_movementSpeed;

	short m_currentZone;

	bool m_wasDirectionChanged : 1;
};