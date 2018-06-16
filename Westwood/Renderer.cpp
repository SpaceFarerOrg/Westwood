#include "Renderer.h"
#include "InputManager.h"

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
	CInputManager::GetInstance().Init(m_renderWindow.getSystemHandle());
}

void CRenderer::RenderToWindow()
{
	m_currentRenderTarget = &m_renderWindow;

	m_currentRenderTarget->clear(sf::Color(50,150,255,255));

	for (sf::Sprite& command : m_renderQueue)
	{
		m_currentRenderTarget->draw(command);
	}

	m_renderQueue.clear();

	m_renderWindow.display();
}

std::vector<sf::Sprite> CRenderer::m_renderQueue;

void CRenderer::PushRenderCommand(const sf::Sprite & a_renderCommand)
{
	m_renderQueue.push_back(a_renderCommand);
}
