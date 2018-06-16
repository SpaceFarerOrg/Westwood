#pragma once
#include "TextureBank.h"
#include "TileInteraction.h"
#include <json.hpp>
#include "TileData.h"
#include "Tileset.h"

class CTileMap
{
public:
	void Load(nlohmann::json& a_tileMapJson);
	void Render();

	bool IsPositionWalkable(const sf::Vector2f& a_position) const;
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