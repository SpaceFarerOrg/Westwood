#pragma once
#include "SFML/Graphics/Rect.hpp"
#include <functional>

class CUIButton : public sf::FloatRect
{
public:
	CUIButton();
	~CUIButton();
	
	void SetFunction(std::function<void(void* a_object)> a_onPressed);
	void Update();
	void Render();

	void SetAssociatedObject(void* a_object);

private:
	std::function<void(void* a_object)> m_onPressed;
	void* m_associatedObject;
};

