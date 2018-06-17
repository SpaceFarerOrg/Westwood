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

void CUIButton::SetFunction(std::function<void(void* a_object)> a_onPressed)
{
	m_onPressed = a_onPressed;
}

void CUIButton::Update()
{
	CInputManager& inputManager = CInputManager::GetInstance();

	if (inputManager.IsKeyPressed(EKeyCode::MouseLeft))
	{
		if (contains(inputManager.GetMousePosFloat()))
		{
			std::cout << "Click!" << std::endl;
			m_onPressed(m_associatedObject);
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

void CUIButton::SetAssociatedObject(void * a_object)
{
	m_associatedObject = a_object;
}
