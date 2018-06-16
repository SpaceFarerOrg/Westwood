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
	void Render();

	bool IsPositionWalkable(const sf::Vector2f& a_position) const;

private:

	void SetTile(const sf::Vector2f& a_position, STileData a_newTile);
	short ConvertPositionToTileIndex(const sf::Vector2f& a_position) const;
	sf::Vector2f GetTilePosition(short a_tileIndex) const;

private:
	ETextures m_texture;
	unsigned int m_tileCount;
	short* m_tiles;

	short m_tileHeight;
	short m_tileWidth;
	
	short m_width;
	short m_height;
	CTileset* m_tileset;
};