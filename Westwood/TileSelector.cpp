#include "TileSelector.h"
#include "Renderer.h"
#include "Tileset.h"
#include "TextureBank.h"

CTileSelector::CTileSelector()
{
}


CTileSelector::~CTileSelector()
{
}

void CTileSelector::Render()
{
	sf::RectangleShape background;
	background.setFillColor(sf::Color(150, 150, 150, 255));
	background.setSize({ width, height });
	background.setPosition(left, top);
	CRenderer::GetInstance().PushUIRenderCommand(background);

	sf::Texture texture = CTextureBank::GetUnorderedTexture(m_tileset->m_texture);

	for (int i = 0; i < m_tileset->m_tileCount; ++i)
	{
		STileData& tile = m_tileset->m_tiles[i];

		sf::Sprite tileRC;
		tileRC.setTexture(texture);
		tileRC.setPosition(left, top);

		CRenderer::GetInstance().PushUIRenderCommand(tileRC);
	}
}

void CTileSelector::SetTilesetPointer(CTileset * a_tilesetPtr)
{
	m_tileset = a_tilesetPtr;
}
