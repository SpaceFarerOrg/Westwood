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

	m_groundTiles = new short[m_tileCount];
	m_interactedTiles = new short[m_tileCount];

	//Todo: Make this scaleable with layers
	for (unsigned int i = 0; i < m_tileCount; ++i)
	{
		m_groundTiles[i] = a_tileMapJson["layers"][0]["data"][i].get<short>() - 1; //-1 here is compensating for the fact that 0 in a tiled file is null object 

		m_interactedTiles[i] = -1; //This must be loaded when loading a saved game but setting -1 for now
	}

	m_texture = CTextureBank::GetTextureIndex(a_tileMapJson["tilesets"][0]["name"].get<std::string>().c_str()); //SCALE WITH LAYERS!!!

	const sf::Texture& tilesheetTexture = CTextureBank::GetTexture(m_texture);
}

void CTileMap::Save()
{
}

void CTileMap::Render()
{
	for (unsigned int indexInMap = 0; indexInMap < m_tileCount; ++indexInMap)
	{
		RenderLayersOnTile(indexInMap);
	}
}

sf::Vector2f CTileMap::CheckForAllowedMove(const sf::Vector2f & a_targetPosition, const sf::Vector2f& a_currentPosition) const
{
	sf::Vector2f allowedMove;

	if (IsTileWalkable({ a_targetPosition.x, a_currentPosition.y }))
	{
		allowedMove.x = a_targetPosition.x - a_currentPosition.x;
	}
	if (IsTileWalkable({ a_currentPosition.x, a_targetPosition.y }))
	{
		allowedMove.y = a_targetPosition.y - a_currentPosition.y;
	}

	return std::move(allowedMove);
}

void CTileMap::PerformInteraction(const sf::Vector2f & a_positionToPerformInteractionOn, ETileInteraction a_interaction)
{
	short tileIndex = ConvertPositionToTileIndex(a_positionToPerformInteractionOn);

	if (m_tileset->GetTileData(m_groundTiles[tileIndex]).IsInteractionAllowed(a_interaction))
	{
		//VERY UGLY QUICK FIX FOR TESTING
		if (a_interaction == ETileInteraction::Dig)
		{
			m_interactedTiles[tileIndex] = 5;
		}
	}
}

bool CTileMap::IsTileWalkable(const sf::Vector2f & a_position) const
{
	short tileIndex = ConvertPositionToTileIndex(a_position);

	bool isWalkable = m_tileset->GetTileData(m_groundTiles[tileIndex]).IsInteractionAllowed(ETileInteraction::Pass);

	return isWalkable;
}

void CTileMap::SetTile(short a_tileIndex, STileData a_newTile)
{
	m_groundTiles[a_tileIndex] = a_newTile;
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

	rv.x = static_cast<float>((a_tileIndex % m_width) * m_tileWidth);
	rv.y = static_cast<float>((a_tileIndex / m_width) * m_tileHeight);

	return rv;
}

std::array<bool, 8> CTileMap::GetNeighbouringTiles(short a_tileIndex, short a_tileIndexInMap, short* a_layer)
{
	std::array<bool, 8> neighbours;

	neighbours[0] = a_layer[a_tileIndexInMap - m_width - 1] == a_tileIndex; //Top left
	neighbours[1] = a_layer[a_tileIndexInMap - m_width] == a_tileIndex;; //Top
	neighbours[2] = a_layer[a_tileIndexInMap - m_width + 1] == a_tileIndex;; //Top right
	neighbours[3] = a_layer[a_tileIndexInMap - 1] == a_tileIndex;; // Left
	neighbours[4] = a_layer[a_tileIndexInMap + 1] == a_tileIndex;; // Right
	neighbours[5] = a_layer[a_tileIndexInMap + m_width - 1] == a_tileIndex;; //Bottom left
	neighbours[6] = a_layer[a_tileIndexInMap + m_width] == a_tileIndex;; //Bottom
	neighbours[7] = a_layer[a_tileIndexInMap + m_width + 1] == a_tileIndex;; //Bottom right

	return std::move(neighbours);
}

void CTileMap::RenderLayersOnTile(short a_indexInMap)
{
	sf::Vector2f tilePosition;
	tilePosition.x = static_cast<float>((a_indexInMap % m_width) * m_tileWidth);
	tilePosition.y = static_cast<float>((a_indexInMap / m_width) * m_tileHeight);

	short groundTileIndex = m_groundTiles[a_indexInMap];

	if (m_tileset->GetTileData(m_groundTiles[a_indexInMap]).m_isAdaptive)
	{
		groundTileIndex = m_tileset->CalculateAdaptiveTile(groundTileIndex, GetNeighbouringTiles(groundTileIndex, a_indexInMap, m_groundTiles));
	}

	m_tileset->DrawTileAtPosition(groundTileIndex, tilePosition);

	short interactedTileIndex = m_interactedTiles[a_indexInMap];
	if (interactedTileIndex != -1) //Do not render anything if no interaction was made to the tile
	{
		if (m_tileset->GetTileData(m_interactedTiles[a_indexInMap]).m_isAdaptive)
		{
			interactedTileIndex = m_tileset->CalculateAdaptiveTile(interactedTileIndex, GetNeighbouringTiles(interactedTileIndex, a_indexInMap, m_interactedTiles));
		}
		
		m_tileset->DrawTileAtPosition(interactedTileIndex, tilePosition);
	}
}

