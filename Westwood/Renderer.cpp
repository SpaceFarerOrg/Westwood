#include "Renderer.h"
#include "InputManager.h"


CRenderer::CRenderer()
	: m_currentRenderTarget(nullptr)
{
}

CRenderer::~CRenderer()
{
}

CRenderer & CRenderer::GetInstance()
{
	static CRenderer instance;

	return instance;
}

void CRenderer::Initialize()
{
	sf::VideoMode videoMode = sf::VideoMode::getDesktopMode();

	m_renderWindow.create(videoMode, "Game", sf::Style::Close);
	CInputManager::GetInstance().Init(&m_renderWindow);

	m_currentWindowDimensions.x = static_cast<float>(videoMode.width);
	m_currentWindowDimensions.y = static_cast<float>(videoMode.height);

	m_camera.setSize(m_currentWindowDimensions);
}

void CRenderer::RenderToWindow()
{
	m_currentRenderTarget = &m_renderWindow;

	m_currentRenderTarget->clear(sf::Color(50,150,255,255));

	/*Camera space rendering*/
	m_renderWindow.setView(m_camera);

	m_camera.setCenter(m_cameraTarget);

	for (sf::Sprite& command : m_renderQueue)
	{
		m_currentRenderTarget->draw(command);
	}

	for (sf::RectangleShape& command : m_rectangleQueue)
	{
		m_currentRenderTarget->draw(command);
	}

	/*End camera space rendering*/

	/*Screen space rendering*/
	sf::View view = m_renderWindow.getView();

	m_renderWindow.setView(m_renderWindow.getDefaultView());
	
	for (sf::Text& command : m_textQueue)
	{
		m_currentRenderTarget->draw(command);
	}

	for (sf::Sprite& command : m_UIRenderQueue)
	{
		m_currentRenderTarget->draw(command);
	}

	for (sf::RectangleShape& command : m_UIRectangleQueue)
	{
		m_currentRenderTarget->draw(command);
	}

	m_renderWindow.setView(view);
	/*End Screen space rendering*/

	m_UIRenderQueue.clear();
	m_UIRectangleQueue.clear();
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

void CRenderer::SetCameraTarget(const sf::Vector2f & a_targetPosition)
{
	m_cameraTarget = a_targetPosition;
}

void CRenderer::PushUIRenderCommand(const sf::Sprite & a_renderCommand)
{
	m_UIRenderQueue.push_back(a_renderCommand);
}

void CRenderer::PushUIRenderCommand(const sf::RectangleShape & a_renderCommand)
{
	m_UIRectangleQueue.push_back(a_renderCommand);
}
