#pragma once
#include "Renderer.h"
#include <SFML\System\Clock.hpp>
#include "GameWorld.h"
#include "TextureBank.h"
#include "WindowEventHandler.h"
#include "WorldEditor.h"
#include "TilesetBank.h"

class CGame
{
public:
	CGame();
	void Initialize();
	void Update();

	bool ShouldRun() const;
private:
	CWindowEventHandler m_windowEventHandler;
	CGameWorld m_gameWorld;

	CTextureBank m_textureBank;
	CTilesetBank m_tilesetBank;
	
	sf::Clock m_deltaTimer;
	CWorldEditor m_worldEditor;

	bool m_shouldRun : 1;
};