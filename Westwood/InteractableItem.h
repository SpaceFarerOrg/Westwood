#pragma once
#include <SFML\Graphics\Rect.hpp>
#include <SFML\System\Vector2.hpp>

class CPlayer;

class CInteractableItem
{
public:
	void Init(float a_width, float a_height, const sf::IntRect& a_sourceRectInObjectSheet);
	virtual void Interact(CPlayer& a_user) = 0;
	bool IsColliding(const sf::Vector2f& a_point);
	void SetPosition(const sf::Vector2f& a_position);
	void Render();
private:
	sf::Vector2f m_position;
	sf::FloatRect m_collisionRect;
	sf::IntRect m_textureRect;

};