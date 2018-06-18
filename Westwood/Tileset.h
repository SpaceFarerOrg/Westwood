#pragma once
#include <json.hpp>
#include <vector>
#include "TileData.h"
#include <SFML\System\Vector2.hpp>

class CTileset
{
	friend class CTileSelector;

public:
	void LoadFromJson(nlohmann::json& a_tilesetJson);
	void Unload();

	const STileData& GetTileData(short a_tileIndex) const;

	void DrawTileAtPosition(short a_tileIndex, const sf::Vector2f& a_position);
private:
	STileData* m_tiles;
	short m_columns;
	short m_texture;
	short m_tileWidth;
	short m_tileHeight;
	short m_tileCount;
};