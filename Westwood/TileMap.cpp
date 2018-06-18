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

void CTileMap::Save()
{
}

void CTileMap::Render()
{
	sf::Vector2f tilePosition;

	for (unsigned int i = 0; i < m_tileCount; ++i)
	{
		tilePosition.x = static_cast<float>((i % m_width) * m_tileWidth);
		tilePosition.y = static_cast<float>((i / m_width) * m_tileHeight);

		short tileIndex = m_tiles[i];

		if (m_tileset->GetTileData(m_tiles[i]).m_isAdaptive)
		{
			tileIndex = m_tileset->CalculateAdaptiveTile(m_tiles[i], GetNeighbouringTiles(m_tiles[i], i));
		}

		m_tileset->DrawTileAtPosition(tileIndex, tilePosition);
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
	short tileIndex = ConvertPositionToTileIndex(a_position);

	bool isWalkable = m_tileset->GetTileData(m_tiles[tileIndex]).m_isPassable;

	return isWalkable;
}

void CTileMap::SetTile(short a_tileIndex, STileData a_newTile)
{
	m_tiles[a_tileIndex] = a_newTile;
}

short CTileMap::ConvertPositionToTileIndex(const sf::Vector2f & a_position, const sf::Vector2f& a_zoomFactor) const
{
	sf::Vector2i positionInTiles;
	positionInTiles.x = static_cast<int>(a_position.x / m_tileWidth * a_zoomFactor.x) + 1;
	positionInTiles.y = static_cast<int>(a_position.y / m_tileHeight * a_zoomFactor.y) + 1;

	short tileIndex = m_width * positionInTiles.y;
	tileIndex -= m_width - positionInTiles.x;
	tileIndex -= 1;

	return tileIndex;
}

sf::Vector2f CTileMap::GetTilePosition(short a_tileIndex) const
{
	sf::Vector2f rv;

	rv.x = (a_tileIndex % m_width) * m_tileWidth;
	rv.y = (a_tileIndex / m_width) * m_tileHeight;

	return rv;
}

std::array<bool, 8> CTileMap::GetNeighbouringTiles(short a_tileIndex, short a_tileIndexInMap)
{
	std::array<bool, 8> neighbours;

	neighbours[0] = m_tiles[a_tileIndexInMap - m_width - 1] == a_tileIndex; //Top left
	neighbours[1] = m_tiles[a_tileIndexInMap - m_width] == a_tileIndex;; //Top
	neighbours[2] = m_tiles[a_tileIndexInMap - m_width + 1] == a_tileIndex;; //Top right
	neighbours[3] = m_tiles[a_tileIndexInMap - 1] == a_tileIndex;; // Left
	neighbours[4] = m_tiles[a_tileIndexInMap + 1] == a_tileIndex;; // Right
	neighbours[5] = m_tiles[a_tileIndexInMap + m_width - 1] == a_tileIndex;; //Bottom left
	neighbours[6] = m_tiles[a_tileIndexInMap + m_width] == a_tileIndex;; //Bottom
	neighbours[7] = m_tiles[a_tileIndexInMap + m_width + 1] == a_tileIndex;; //Bottom right

	return std::move(neighbours);
}

