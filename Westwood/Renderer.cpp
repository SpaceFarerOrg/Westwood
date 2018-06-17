#include "Renderer.h"
#include "InputManager.h"

/*Declaration of static members*/
std::vector<sf::Sprite> CRenderer::m_renderQueue;
std::vector<sf::RectangleShape> CRenderer::m_rectangleQueue;
std::vector<sf::Text> CRenderer::m_textQueue;

sf::Vector2f CRenderer::m_currentWindowDimensions;
/*End static member declaration*/

CRenderer::CRenderer()
	: m_currentRenderTarget(nullptr)
{
}

CRenderer::~CRenderer()
{
}

void CRenderer::Initialize()
{
	sf::VideoMode videoMode = sf::VideoMode::getDesktopMode();

	m_renderWindow.create(videoMode, "Game", sf::Style::Close);
	CInputManager::GetInstance().Init(&m_renderWindow);

	m_currentWindowDimensions.x = static_cast<float>(videoMode.width);
	m_currentWindowDimensions.y = static_cast<float>(videoMode.height);
}

void CRenderer::RenderToWindow()
{
	m_currentRenderTarget = &m_renderWindow;

	m_currentRenderTarget->clear(sf::Color(50,150,255,255));

	for (sf::Sprite& command : m_renderQueue)
	{
		m_currentRenderTarget->draw(command);
	}

	for (sf::RectangleShape& command : m_rectangleQueue)
	{
		m_currentRenderTarget->draw(command);
	}

	for (sf::Text& command : m_textQueue)
	{
		m_currentRenderTarget->draw(command);
	}

	m_renderQueue.clear();
	m_rectangleQueue.clear();
	m_textQueue.clear();

	m_renderWindow.display();
}

sf::RenderWindow & CRenderer::GetWindow()
{
	return m_renderWindow;
}


void CRenderer::PushRenderCommand(const sf::Sprite & a_renderCommand)
{
	m_renderQueue.push_back(a_renderCommand);
}

void CRenderer::PushRenderCommand(const sf::RectangleShape & a_renderCommand)
{
	m_rectangleQueue.push_back(a_renderCommand);
}

void CRenderer::PushRenderCommand(const sf::Text& a_renderCommand)
{
	m_textQueue.push_back(a_renderCommand);
}

const sf::Vector2f & CRenderer::GetWindowDimensions()
{
	return m_currentWindowDimensions;
}
