#include "Tileset.h"
#include "TextureBank.h"
#include "Renderer.h"


void CTileset::LoadFromJson(nlohmann::json & a_tilesetJson)
{
	m_tileWidth = a_tilesetJson["tilewidth"].get<short>();
	m_tileHeight = a_tilesetJson["tileheight"].get<short>();

	m_tileCount = a_tilesetJson["tilecount"].get<short>();
	m_tiles = new STileData[m_tileCount];

	m_columns = a_tilesetJson["columns"].get<short>();

	m_texture = CTextureBank::LoadUnorderedTexture(a_tilesetJson["name"].get<std::string>().c_str());

	for (short tileIndex = 0; tileIndex < m_tileCount; ++tileIndex)
	{
		m_tiles[tileIndex].m_tileIndex = tileIndex;

		m_tiles[tileIndex].m_textureRect.width = m_tileWidth;
		m_tiles[tileIndex].m_textureRect.height = m_tileHeight;
		m_tiles[tileIndex].m_textureRect.left = (tileIndex % m_columns) * m_tileWidth;
		m_tiles[tileIndex].m_textureRect.top = (tileIndex / m_columns) * m_tileHeight;


		m_tiles[tileIndex].m_isPassable = a_tilesetJson["tileproperties"][std::to_string(tileIndex)]["passable"].get<bool>();
	}
}

void CTileset::Unload()
{
	delete[] m_tiles;
}

const STileData & CTileset::GetTileData(short a_tileIndex) const
{
	return m_tiles[a_tileIndex];
}

void CTileset::DrawTileAtPosition(short a_tileIndex, const sf::Vector2f & a_position)
{
	sf::Sprite tileRenderCommand;
	tileRenderCommand.setTexture(CTextureBank::GetUnorderedTexture(m_texture));

	tileRenderCommand.setTextureRect(m_tiles[a_tileIndex].m_textureRect);
	tileRenderCommand.setPosition(a_position);

	CRenderer::GetInstance().PushRenderCommand(tileRenderCommand);
}
