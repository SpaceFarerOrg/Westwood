#include "StatusBar.h"
#include "Math.h"
#include "Renderer.h"

CStatusBar::CStatusBar()
{
	m_width = 0.f;
	m_height = 0.f;
	m_maxValue = 0.f;
	m_value = 0.f;
	m_hasCallback = false;
}

void CStatusBar::Init(float a_maxValue, float a_width, float a_height, CStatusBar::EType a_type)
{
	m_maxValue = a_maxValue;
	m_type = a_type;
	m_width = a_width;
	m_height = a_height;
	SetToMax();
}

void CStatusBar::BindCallbackToOnEmpty(std::function<void()> a_callbackOnEmpty)
{
	m_callbackOnEmpty = a_callbackOnEmpty;
	m_hasCallback = true;
}

void CStatusBar::SetToMax()
{
	m_value = m_maxValue;
}

void CStatusBar::AddToValue(float a_valueToAdd)
{
	m_value = Math::Clamp<float>(m_value + a_valueToAdd, 0.f, m_maxValue);

	if (m_value == 0.f && m_hasCallback)
	{
		m_callbackOnEmpty();
	}

}

sf::Vector2f CStatusBar::GetSize() const
{
	sf::Vector2f size(m_width, m_height);

	return std::move(size);
}

void CStatusBar::Render(const sf::Vector2f & a_positionInUI)
{
	sf::RectangleShape shape;
	sf::Vector2f renderPos = a_positionInUI;

	float percentage = m_value / m_maxValue;

	if (m_type == EType::horizontal)
	{
		shape.setSize({ m_width * percentage, m_height });
		float wDiff = m_width - m_width * percentage;
		renderPos.x += wDiff;
	}
	else if (m_type == EType::vertical)
	{
		shape.setSize({ m_width, m_height * percentage});
		float hDiff = m_height - m_height * percentage;
		renderPos.y += hDiff;
	}

	shape.setFillColor(sf::Color::Green);
	shape.setPosition(renderPos);

	CRenderer::GetInstance().PushUIRenderCommand(shape);
}


