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

	for (short i = 0; i < m_tileCount; ++i)
	{
		m_tiles[i].m_tileIndex = i;
		m_tiles[i].m_isPassable = a_tilesetJson["tileproperties"][std::to_string(i)]["passable"].get<bool>();
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
	sf::IntRect textureRectangle;
	tileRenderCommand.setTexture(CTextureBank::GetUnorderedTexture(m_texture));

	textureRectangle.width = m_tileWidth;
	textureRectangle.height = m_tileHeight;
	textureRectangle.left = (a_tileIndex % m_columns) * m_tileWidth;
	textureRectangle.top = (a_tileIndex / m_columns) * m_tileHeight;

	tileRenderCommand.setTextureRect(textureRectangle);
	tileRenderCommand.setPosition(a_position);

	CRenderer::PushRenderCommand(tileRenderCommand);
}
