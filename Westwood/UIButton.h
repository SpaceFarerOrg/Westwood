#pragma once
#include "SFML/Graphics/Rect.hpp"
#include <functional>

class CUIButton : public sf::FloatRect
{
public:
	CUIButton();
	~CUIButton();
	
	void Update();
	void Render();

private:
};

