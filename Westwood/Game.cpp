#include "Game.h"
#include "InputManager.h"

CGame::CGame()
	:m_windowEventHandler(m_renderer.GetWindow())
	, m_player(m_avatarCollection.CreateNewAvatar())
{
	
}

void CGame::Initialize()
{
	m_renderer.Initialize();
	m_textureBank.LoadAllTextures();
	m_tilesetBank.LoadAllTilesets();

	m_gameWorld.Load("data/gameWorld.json");

	m_shouldRun = true;

	m_avatarCollection.BindGameWorld(m_gameWorld);
	m_avatarCollection.FinalizeAvatarCreation();

	m_gameWorld.ChangeZone(0);
}

void CGame::Update()
{
	float deltaTime = m_deltaTimer.getElapsedTime().asSeconds();
	m_deltaTimer.restart();

	m_windowEventHandler.RunEventHandling();

	m_worldEditor.Update(m_gameWorld.GetCurrentZone());
	m_player.Update();

	m_gameWorld.Update(deltaTime);

	m_gameWorld.Render();
	m_worldEditor.Render(&m_renderer.GetWindow());

	m_avatarCollection.RenderAvatars();

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


