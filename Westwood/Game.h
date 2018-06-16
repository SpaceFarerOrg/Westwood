#pragma once
#include "Renderer.h"
#include <SFML\System\Clock.hpp>
#include "GameWorld.h"
#include "TextureBank.h"
#include "WindowEventHandler.h"
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
	CRenderer m_renderer;
	CGameWorld m_gameWorld;

	CTextureBank m_textureBank;
	CTilesetBank m_tilesetBank;
	
	sf::Clock m_deltaTimer;


	bool m_shouldRun : 1;
};