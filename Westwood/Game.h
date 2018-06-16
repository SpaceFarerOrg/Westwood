#pragma once
#include "Renderer.h"
#include <SFML\System\Clock.hpp>
#include "GameWorld.h"
#include "TextureBank.h"

class CGame
{
public:
	void Initialize();
	void Update();

	bool ShouldRun() const;
private:
	CRenderer m_renderer;
	CGameWorld m_gameWorld;
	CTextureBank m_textureBank;
	sf::Clock m_deltaTimer;

	bool m_shouldRun : 1;
};