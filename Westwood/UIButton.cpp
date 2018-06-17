#include "UIButton.h"
#include "InputManager.h"
#include "Renderer.h"

#include <iostream>

CUIButton::CUIButton()
{
}


CUIButton::~CUIButton()
{
}

void CUIButton::Update()
{
	CInputManager& inputManager = CInputManager::GetInstance();

	if (inputManager.IsKeyPressed(EKeyCode::MouseLeft))
	{
		if (contains(inputManager.GetMousePosFloat()))
		{
			std::cout << "Click!" << std::endl;
		}
	}
}

void CUIButton::Render()
{
	sf::RectangleShape shape;
	
	shape.setFillColor(sf::Color::White);
	shape.setSize({ width, height });
	shape.setPosition(top, left);

	CRenderer::GetInstance().PushUIRenderCommand(shape);
}
