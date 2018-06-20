#include "Game.h"
#include "InputManager.h"
#include "ItemBank.h"

CGame::CGame()
	:m_windowEventHandler(CRenderer::GetInstance().GetWindow())
	, m_player(m_avatarCollection.CreateNewAvatar())
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

	m_avatarCollection.BindGameWorld(m_gameWorld);
	m_avatarCollection.FinalizeAvatarCreation();

	m_gameWorld.ChangeZone(0);

	m_player.Init();

	/*Debug give player items*/
	short axeIndex = CItemBank::GetInstance().GetItemID("Axe");
	short pickaxeIndex = CItemBank::GetInstance().GetItemID("Pickaxe");
	short shovelIndex = CItemBank::GetInstance().GetItemID("Shovel");

	m_player.GetInventory().AddItemToInventory(axeIndex);
	m_player.GetInventory().AddItemToInventory(pickaxeIndex);
	m_player.GetInventory().AddItemToInventory(shovelIndex);
	/*End debug*/
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
	m_worldEditor.Render();

	m_avatarCollection.RenderAvatars();

	CRenderer::GetInstance().RenderToWindow();

	if (m_windowEventHandler.GetHasClosed())
	{
		m_shouldRun = false;
	}
}

bool CGame::ShouldRun() const
{
	return m_shouldRun;
}


