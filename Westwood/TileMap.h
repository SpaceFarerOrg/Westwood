#pragma once
#include "TextureBank.h"
#include "TileInteraction.h"
#include <json.hpp>
#include "TileData.h"
#include "Tileset.h"

class CWorldZone;

class CTileMap
{

	friend class CWorldEditor;

public:
	void Load(nlohmann::json& a_tileMapJson, CWorldZone& a_zoneToBindTo);
	void Save();
	void Render();

	bool IsTileWalkable(const sf::Vector2f& a_position) const;

	sf::Vector2f CheckForAllowedMove(const sf::Vector2f& a_targetPosition, const sf::Vector2f& a_currentPosition) const;

	void PerformInteraction(const sf::Vector2f& a_positionToPerformInteractionOn, ETileInteraction a_interaction);
private:
	void SetTile(short a_tileIndex, STileData a_newTile);
	short ConvertPositionToTileIndex(const sf::Vector2f& a_position, const sf::Vector2f& a_zoomFactor = { 1,1 }) const;
	sf::Vector2f GetTilePosition(short a_tileIndex) const;

private:
	std::array<bool, 8> GetNeighbouringTiles(short a_tileIndex, short a_tileIndexInMap, short* a_layer);

	void RenderLayersOnTile(short a_indexInMap);

	CWorldZone* m_ownerZone;

	CTileset* m_tileset;
	ETextures m_texture;
	unsigned int m_tileCount;
	
	//Layers
	short* m_groundTiles;
	short* m_interactedTiles;

	short m_tileHeight;
	short m_tileWidth;
	
	short m_width;
	short m_height;
};