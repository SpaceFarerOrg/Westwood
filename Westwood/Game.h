#pragma once
#include "Renderer.h"
#include <SFML\System\Clock.hpp>
#include "GameWorld.h"
#include "TextureBank.h"
#include "WindowEventHandler.h"
#include "WorldEditor.h"
#include "TilesetBank.h"
#include "AvatarCollection.h"
#include "Player.h"

class CGame
{
public:
	CGame();
	void Initialize();
	void Update();

	bool ShouldRun() const;
private:
	CWindowEventHandler m_windowEventHandler;
	CRenderer m_renderer;
	CGameWorld m_gameWorld;

	CAvatarCollection m_avatarCollection;
	CTextureBank m_textureBank;
	CTilesetBank m_tilesetBank;
	
	sf::Clock m_deltaTimer;
	CWorldEditor m_worldEditor;

	CPlayer m_player;

	bool m_shouldRun : 1;
};