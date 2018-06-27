#pragma once
#include <json.hpp>
#include <vector>
#include "TileData.h"
#include <SFML\System\Vector2.hpp>
#include <array>

class CTileset
{
	friend class CTileSelector;

public:
	void LoadFromJson(nlohmann::json& a_tilesetJson);
	void Unload();

	const STileData& GetTileData(short a_tileIndex) const;

	short CalculateAdaptiveTile(short a_tileIndex, const std::array<bool, 8>& a_neighbours);

	void DrawTileAtPosition(short a_tileIndex, const sf::Vector2f& a_position);
private:
	void LoadAdaptiveTile(short a_tileIndex, const char* a_adaptiveJson);

	STileData* m_tiles;
	short m_columns;
	short m_texture;
	short m_tileWidth;
	short m_tileHeight;
	short m_tileCount;
};