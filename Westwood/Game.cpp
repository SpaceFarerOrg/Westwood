#include "Game.h"
#include "InputManager.h"

CGame::CGame()
	:m_windowEventHandler(m_renderer.GetWindow())
{
	
}

void CGame::Initialize()
{
	m_renderer.Initialize();
	m_textureBank.LoadAllTextures();

	m_gameWorld.Load("data/gameWorld.json");

	m_shouldRun = true;
}

void CGame::Update()
{
	float deltaTime = m_deltaTimer.getElapsedTime().asSeconds();
	m_deltaTimer.restart();

	m_windowEventHandler.RunEventHandling();

	m_gameWorld.Render();

	m_renderer.RenderToWindow();

	if (m_windowEventHandler.GetHasClosed())
	{
		m_shouldRun = false;
	}
}

bool CGame::ShouldRun() const
{
	return m_shouldRun;
}


