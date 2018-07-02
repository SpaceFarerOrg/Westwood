#pragma once
#include "TextureBank.h"
#include "TileInteraction.h"
#include <json.hpp>
#include "TileData.h"
#include "Tileset.h"
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/VertexArray.hpp>

class CWorldZone;

class CTileMap : public sf::Drawable, public sf::Transformable
{

	friend class CWorldEditor;

public:
	void Load(nlohmann::json& a_tileMapJson, CWorldZone& a_zoneToBindTo);
	void Save();
	void Render();

	bool IsTileWalkable(const sf::Vector2f& a_position) const;

	sf::Vector2f CheckForAllowedMove(const sf::Vector2f& a_targetPosition, const sf::Vector2f& a_currentPosition) const;
	sf::Vector2f GetTilePosition(short a_tileIndex) const;
	sf::Vector2f GetClosestTilePosition(const sf::Vector2f& a_position);
	short ConvertPositionToTileIndex(const sf::Vector2f& a_position, const sf::Vector2f& a_zoomFactor = { 1,1 }) const;

	bool PositionIsPlowed(const sf::Vector2f& a_position);
	bool IsTileWatered(short a_tileIndex);

	void Dig(const sf::Vector2f& a_onPosition);
	void Water(const sf::Vector2f& a_onPosition);
private:

	virtual void draw(sf::RenderTarget& a_target, sf::RenderStates a_states) const;

	void SetTile(short a_tileIndex, STileData a_newTile);
	void RunItemSpawnForTileInteraction(ETileInteraction a_interaction, short a_tileIndexInTileSet, short a_tileIndexInMap);

private:
	std::array<bool, 8> GetNeighbouringTiles(short a_tileIndex, short a_tileIndexInMap, short* a_layer);

	void RenderLayersOnTile(short a_indexInMap);

	sf::VertexArray m_vertices;

	CWorldZone* m_ownerZone;

	CTileset* m_tileset;
	ETextures m_texture;
	unsigned int m_tileCount;
	
	//Layers
	short* m_groundTiles;
	short* m_interactedTiles;
	bool* m_wateredTiles;

	short m_tileHeight;
	short m_tileWidth;
	
	short m_width;
	short m_height;
};