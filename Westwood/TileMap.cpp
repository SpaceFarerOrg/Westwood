#include "TileMap.h"
#include "Renderer.h"
#include <SFML\Graphics\Sprite.hpp>
#include "TilesetBank.h"

void CTileMap::Load(nlohmann::json & a_tileMapJson)
{
	m_tileset = &CTilesetBank::GetTileset(0);

	m_width = a_tileMapJson["width"].get<short>();
	m_height = a_tileMapJson["height"].get<short>();
	m_tileWidth = a_tileMapJson["tilewidth"].get<short>();
	m_tileHeight = a_tileMapJson["tileheight"].get<short>();

	m_tileCount = m_width * m_height;

	m_tiles = new short[m_tileCount];

	//Todo: Make this scaleable with layers
	for (unsigned int i = 0; i < m_tileCount; ++i)
	{
		m_tiles[i] = a_tileMapJson["layers"][0]["data"][i].get<short>() - 1; //-1 here is compensating for the fact that 0 in a tiled file is null object 
	}

	m_texture = CTextureBank::GetTextureIndex(a_tileMapJson["tilesets"][0]["name"].get<std::string>().c_str()); //SCALE WITH LAYERS!!!

	const sf::Texture& tilesheetTexture = CTextureBank::GetTexture(m_texture);
}

void CTileMap::Render()
{
	sf::Vector2f tilePosition;

	for (unsigned int i = 0; i < m_tileCount; ++i)
	{
		tilePosition.x = static_cast<float>((i % m_width) * m_tileWidth);
		tilePosition.y = static_cast<float>((i / m_width) * m_tileHeight);

		m_tileset->DrawTileAtPosition(m_tiles[i], tilePosition);
	}
}

sf::Vector2f CTileMap::CheckForAllowedMove(const sf::Vector2f & a_targetPosition, const sf::Vector2f& a_currentPosition) const
{
	sf::Vector2f allowedMove = a_currentPosition;

	if (IsTileWalkable({ a_targetPosition.x, a_currentPosition.y }))
	{
		allowedMove.x = a_targetPosition.x;
	}
	if (IsTileWalkable({ a_currentPosition.x, a_targetPosition.y }))
	{
		allowedMove.y = a_targetPosition.y;
	}

	return std::move(allowedMove);
}

bool CTileMap::IsTileWalkable(const sf::Vector2f & a_position) const
{
	sf::Vector2i positionInTiles;
	positionInTiles.x = static_cast<int>(a_position.x / m_tileWidth) + 1;
	positionInTiles.y = static_cast<int>(a_position.y / m_tileHeight) + 1;

	short tileIndex = m_width * positionInTiles.y;
	tileIndex -= m_width - positionInTiles.x;
	tileIndex -= 1;

	bool isWalkable = m_tileset->GetTileData(m_tiles[tileIndex]).m_isPassable;

	return isWalkable;
}

