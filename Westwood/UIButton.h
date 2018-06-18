#pragma once
#include "SFML/Graphics/Rect.hpp"
#include <functional>
#include "SFML/Graphics/Text.hpp"

class CUIButton : public sf::FloatRect
{
public:
	CUIButton();
	~CUIButton();
	
	void SetFunction(std::function<void(void* a_object)> a_onPressed);
	void Update();
	void Render();

	void SetPosition(float a_x, float a_y);
	void SetPosition(const sf::Vector2f& a_position);
	void AddSubText(const sf::String& a_text);

	void SetAssociatedObject(void* a_object);

private:
	std::function<void(void* a_object)> m_onPressed;
	void* m_associatedObject;
	sf::String m_subText;
};

