#include "TileMap.h"
#include "Renderer.h"
#include <SFML\Graphics\Sprite.hpp>

void CTileMap::Load(nlohmann::json & a_tileMapJson)
{
	m_width = a_tileMapJson["width"].get<short>();
	m_height = a_tileMapJson["height"].get<short>();
	m_tileWidth = a_tileMapJson["tilewidth"].get<short>();
	m_tileHeight = a_tileMapJson["tileheight"].get<short>();

	m_tileCount = m_width * m_height;

	m_tiles = new STileData[m_tileCount];

	//Todo: Make this scaleable with layers
	for (unsigned int i = 0; i < m_tileCount; ++i)
	{
		m_tiles[i] = a_tileMapJson["layers"][0]["data"][i].get<short>() - 1; //-1 here is compensating for the fact that 0 in a tiled file is null object 
	}

	m_texture = CTextureBank::GetTextureIndex(a_tileMapJson["tilesets"][0]["name"].get<std::string>().c_str()); //SCALE WITH LAYERS!!!

	const sf::Texture& tilesheetTexture = CTextureBank::GetTexture(m_texture);

	m_tilesheetTileCountX = tilesheetTexture.getSize().x / m_tileWidth;
}

void CTileMap::Render()
{
	sf::Sprite tileRenderCommand;
	sf::Vector2f tilePosition;
	sf::IntRect textureRectangle;
	tileRenderCommand.setTexture(CTextureBank::GetTexture(m_texture));

	for (unsigned int i = 0; i < m_tileCount; ++i)
	{
		tilePosition.x = static_cast<float>((i % m_width) * m_tileWidth);
		tilePosition.y = static_cast<float>((i / m_width) * m_tileHeight);

		textureRectangle.width = m_tileWidth;
		textureRectangle.height = m_tileHeight;
		textureRectangle.left = (m_tiles[i] % m_tilesheetTileCountX) * m_tileWidth;
		textureRectangle.top = (m_tiles[i] / m_tilesheetTileCountX) * m_tileHeight;

		tileRenderCommand.setTextureRect(textureRectangle);
		tileRenderCommand.setPosition(tilePosition);

		CRenderer::PushRenderCommand(tileRenderCommand);
	}

}

bool CTileMap::IsPositionWalkable(const sf::Vector2f & a_position) const
{
	sf::Vector2i positionInTiles;
	positionInTiles.x = static_cast<int>(a_position.x / m_tileWidth);
	positionInTiles.y = static_cast<int>(a_position.y / m_tileHeight);

	short tileIndex = m_width * positionInTiles.y;
	tileIndex -= m_width - positionInTiles.x;

	return m_tiles[tileIndex].m_isPassable;
}
