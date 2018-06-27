#include "TileSelector.h"
#include "Renderer.h"
#include "Tileset.h"
#include "TextureBank.h"
#include "InputManager.h"
#include <iostream>

CTileSelector::CTileSelector()
{
}


CTileSelector::~CTileSelector()
{
}

short CTileSelector::Update()
{
	CInputManager& inputManager = CInputManager::GetInstance();

	if (inputManager.IsKeyPressed(EKeyCode::MouseLeft))
	{
		sf::Vector2f mPos = inputManager.GetMousePosFloat();
		if (contains(mPos))
		{
			sf::Vector2f offseted = mPos - sf::Vector2f(left, top);

			offseted.x = static_cast<int>(offseted.x / m_tileSize) + 1;
			offseted.y = static_cast<int>(offseted.y / m_tileSize) + 1;

			short tileIndex = width * offseted.y;
			tileIndex -= width - offseted.x;

			std::cout << "Selected tile " << tileIndex << std::endl;

			return tileIndex;
		}
	}

	return -1;
}

void CTileSelector::Render()
{
	sf::RectangleShape background;
	background.setFillColor(sf::Color(150, 150, 150, 255));
	background.setSize({ width, height });
	background.setPosition(left, top);
	CRenderer::GetInstance().PushUIRenderCommand(background);

	const sf::Texture& texture = CTextureBank::GetUnorderedTexture(m_tileset->m_texture);

	for (int i = 0; i < m_tileset->m_tileCount; ++i)
	{
		STileData& tile = m_tileset->m_tiles[i];

		sf::Sprite tileRC;
		tileRC.setTexture(texture);
		tileRC.setPosition(left + i * m_tileSize, top);
		tileRC.setTextureRect(tile.m_textureRect);
		tileRC.setScale((m_tileSize / m_tileset->m_tileWidth) * sf::Vector2f(1.f, 1.f));

		CRenderer::GetInstance().PushUIRenderCommand(tileRC);
	}
}

void CTileSelector::SetTilesetPointer(CTileset * a_tilesetPtr)
{
	m_tileset = a_tilesetPtr;

	m_tileSize = height / 2.f;
}
