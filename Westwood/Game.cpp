#include "Game.h"
#include "InputManager.h"
#include "ItemBank.h"
#include "GameEventMaster.h"

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

	m_tilesetBank.LoadAllTilesets();

	m_gameWorld.Load("data/gameWorld.json");
	m_worldEditor.Initialize();

	m_shouldRun = true;

	m_gameWorld.ChangeZone(0);
}

void CGame::Update()
{
	float deltaTime = m_deltaTimer.getElapsedTime().asSeconds();
	sf::Text deltaTimeText;
	deltaTimeText.setFont(CTextureBank::GetFont(EFonts::Debug));
	deltaTimeText.setString(std::to_string(static_cast<short>(1.f / deltaTime)));
	CRenderer::GetInstance().PushUIRenderCommand(deltaTimeText);

	m_deltaTimer.restart();

	m_windowEventHandler.RunEventHandling();

	m_worldEditor.Update(m_gameWorld.GetCurrentZone());

	m_gameWorld.Update(deltaTime);

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


