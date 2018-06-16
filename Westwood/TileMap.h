#pragma once
#include "TextureBank.h"
#include "TileInteraction.h"
#include <json.hpp>

class CTileMap
{

	friend class CWorldEditor;

public:
	void Load(nlohmann::json& a_tileMapJson);
	void Render();

	bool IsPositionWalkable(const sf::Vector2f& a_position) const;

private:
	struct STileData
	{
		operator short() const { return m_tileIndex; };
		void operator =(short a_index) { m_tileIndex = a_index; };

		ETileInteraction m_allowedInteraction;
		short m_tileIndex;
		bool m_isPassable : 1;
	};

	void SetTile(const sf::Vector2f& a_position, STileData a_newTile);
	short ConvertPositionToTileIndex(const sf::Vector2f& a_position) const;
	sf::Vector2f GetTilePosition(short a_tileIndex) const;

private:
	ETextures m_texture;
	unsigned int m_tileCount;
	STileData* m_tiles;

	short m_tilesheetTileCountX;
	
	short m_tileHeight;
	short m_tileWidth;
	
	short m_width;
	short m_height;
};