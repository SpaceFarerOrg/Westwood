#include "Game.h"
#include "InputManager.h"
#include "ItemBank.h"
#include "GameEventMaster.h"
#include "SoundBank.h"
#include "AudioManager.h"

CGame::CGame()
	:m_windowEventHandler(CRenderer::GetInstance().GetWindow())
	, m_worldEditor(&CRenderer::GetInstance().GetWindow())
{

}

void CGame::Initialize()
{
	CRenderer::GetInstance().Initialize();

	/*Load all graphical objects into the bank*/
	m_textureBank.LoadAllTextures();
	m_textureBank.LoadAllFonts();
	/*End gfx load*/

	/*Load data*/
	CItemBank::GetInstance().LoadAllItems("data/items.json");
	/*End load data*/

	/*Load sounds*/
	CAudioManager::GetInstance().Load();
	/*End load sounds*/

	m_tilesetBank.LoadAllTilesets();

	m_gameWorld.Load("data/gameWorld.json");
	m_worldEditor.Initialize();

	m_shouldRun = true;

	m_gameWorld.ChangeZone(0);

	CAudioManager::GetInstance().PlayMusic("sounds/music/theme.wav");
	CAudioManager::GetInstance().SetMusicVolume(25);
}

void CGame::Update()
{
	float deltaTime = m_deltaTimer.getElapsedTime().asSeconds();

	m_engineInfo.CalculateFPS(deltaTime);
	m_engineInfo.RenderInfo();

	m_deltaTimer.restart();

	m_windowEventHandler.RunEventHandling();

	m_worldEditor.Update(m_gameWorld.GetCurrentZone());

	m_gameWorld.Update(deltaTime);
	m_fader.Update(deltaTime);

	CAudioManager::GetInstance().SetListenerPosition(CRenderer::GetInstance().GetCamera().getCenter());

	CRenderer::GetInstance().Clear();
	m_gameWorld.Render();
	m_worldEditor.Render();
	CRenderer::GetInstance().RenderToWindow();

	if (m_windowEventHandler.GetHasClosed())
	{
		m_shouldRun = false;
	}

	CGameEventMaster::GetInstance().HandleFrameEvents();
}

bool CGame::ShouldRun() const
{
	return m_shouldRun;
}


