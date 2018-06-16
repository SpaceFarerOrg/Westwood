#include "Game.h"
#include "InputManager.h"

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

	m_gameWorld.Render();

	m_renderer.RenderToWindow();
}

bool CGame::ShouldRun() const
{
	return m_shouldRun;
}


