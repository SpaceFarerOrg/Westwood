#pragma once
#include "TextureBank.h"
#include "TileInteraction.h"
#include <json.hpp>
#include "TileData.h"
#include "Tileset.h"

class CTileMap
{

	friend class CWorldEditor;

public:
	void Load(nlohmann::json& a_tileMapJson);
	void Save();
	void Render();

	bool IsTileWalkable(const sf::Vector2f& a_position) const;
	sf::Vector2f CheckForAllowedMove(const sf::Vector2f& a_targetPosition, const sf::Vector2f& a_currentPosition) const;

private:
	void SetTile(short a_tileIndex, STileData a_newTile);
	short ConvertPositionToTileIndex(const sf::Vector2f& a_position, const sf::Vector2f& a_zoomFactor = { 1,1 }) const;
	sf::Vector2f GetTilePosition(short a_tileIndex) const;

private:
	CTileset* m_tileset;
	ETextures m_texture;
	unsigned int m_tileCount;
	short* m_tiles;

	short m_tileHeight;
	short m_tileWidth;
	
	short m_width;
	short m_height;
};