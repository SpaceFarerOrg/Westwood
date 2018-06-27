#include "UIButton.h"
#include "InputManager.h"
#include "Renderer.h"
#include "TextureBank.h"
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
	shape.setPosition(left, top);

	CRenderer::GetInstance().PushUIRenderCommand(shape);

	sf::Text subText;
	subText.setFillColor(shape.getFillColor());
	subText.setFont(CTextureBank::GetFont(EFonts::Debug));
	subText.setCharacterSize(static_cast<size_t>(height * 0.25f));
	subText.setString(m_subText);
	subText.setOrigin(subText.getGlobalBounds().width / 2.f, subText.getGlobalBounds().height / 2.f);
	subText.setPosition(left + width / 2.f, top + height * 1.25f);

	CRenderer::GetInstance().PushUIRenderCommand(subText);
}

void CUIButton::SetPosition(float a_x, float a_y)
{
	left = a_x - width / 2.f;
	top = a_y - height / 2.f;
}

void CUIButton::SetPosition(const sf::Vector2f & a_position)
{
	SetPosition(a_position.x, a_position.y);
}

void CUIButton::AddSubText(const sf::String & a_text)
{
	m_subText = a_text;
}

void CUIButton::SetAssociatedObject(void * a_object)
{
	m_associatedObject = a_object;
}
