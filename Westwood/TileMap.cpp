#include "TileMap.h"
#include "Renderer.h"
#include <SFML\Graphics\Sprite.hpp>
#include "TilesetBank.h"
#include "WorldZone.h"
#include "Math.h"
#include "GameEventMaster.h"
#include "CommonUtilities.h"

void CTileMap::Load(nlohmann::json & a_tileMapJson, CWorldZone& a_zoneToBindTo)
{
	m_ownerZone = &a_zoneToBindTo;

	m_tileset = &CTilesetBank::GetTileset(0); //Todo: Make this load relevant tileset instead

	m_width = a_tileMapJson["width"].get<short>();
	m_height = a_tileMapJson["height"].get<short>();
	m_tileWidth = a_tileMapJson["tilewidth"].get<short>();
	m_tileHeight = a_tileMapJson["tileheight"].get<short>();

	m_tileCount = m_width * m_height;

	m_groundTiles = new short[m_tileCount];
	m_interactedTiles = new short[m_tileCount];
	m_wateredTiles = new bool[m_tileCount];

	//Todo: Make this scaleable with layers
	for (unsigned int i = 0; i < m_tileCount; ++i)
	{
		m_groundTiles[i] = a_tileMapJson["layers"][0]["data"][i].get<short>() - 1; //-1 here is compensating for the fact that 0 in a tiled file is null object 

		m_interactedTiles[i] = -1; //This must be loaded when loading a saved game but setting -1 for now
		m_wateredTiles[i] = false;
	}

	std::string tilesetSource = a_tileMapJson["tilesets"][0]["source"].get<std::string>();
	tilesetSource = SplitString(SplitString(tilesetSource, '/').back(), '.')[0];

	m_texture = CTextureBank::GetTextureIndex(tilesetSource.c_str()); //SCALE WITH LAYERS!!!

	const sf::Texture& tilesheetTexture = CTextureBank::GetTexture(m_texture);

	m_vertices.setPrimitiveType(sf::Quads);
	m_vertices.resize(m_width * m_height * 4);

	CGameEventMaster::GetInstance().SubscribeToEvent(EGameEvent::FadeReachBlack, [this] { this->ResetWateredTiles(); });
}

void CTileMap::Save()
{
}

void CTileMap::Render()
{
	CRenderer::GetInstance().RenderTileMap(*this);

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

sf::Vector2f CTileMap::GetClosestTilePosition(const sf::Vector2f & a_position)
{
	short tileIndex = ConvertPositionToTileIndex(a_position);
	sf::Vector2f tilePos = GetTilePosition(tileIndex);

	return std::move(tilePos);
}

bool CTileMap::PositionIsPlowed(const sf::Vector2f & a_position)
{
	short tileIndex = ConvertPositionToTileIndex(a_position);

	return TileIsPlowed(tileIndex);
}

bool CTileMap::TileIsPlowed(short a_tileIndex)
{
	if (m_interactedTiles[a_tileIndex] != -1)
	{
		return true;
	}

	return false;
}

bool CTileMap::IsTileWatered(short a_tileIndex)
{
	return m_wateredTiles[a_tileIndex];
}

void CTileMap::Dig(const sf::Vector2f & a_onPosition)
{
	short tileIndex = ConvertPositionToTileIndex(a_onPosition);
	const STileData& tileData = m_tileset->GetTileData(m_groundTiles[tileIndex]);

	if (tileData.IsInteractionAllowed(ETileInteraction::Dig))
	{
		short onDigTileToAdd = tileData.GetTileToAddOnInteraction(ETileInteraction::Dig);

		if (onDigTileToAdd != -1)
		{
			m_interactedTiles[tileIndex] = onDigTileToAdd;
		}
	}
}

void CTileMap::Water(const sf::Vector2f & a_onPosition)
{
	short tileIndex = ConvertPositionToTileIndex(a_onPosition);

	m_wateredTiles[tileIndex] = true;
}

bool CTileMap::IsTileWalkable(const sf::Vector2f & a_position) const
{
	short tileIndex = ConvertPositionToTileIndex(a_position);

	bool isWalkable = m_tileset->GetTileData(m_groundTiles[tileIndex]).IsInteractionAllowed(ETileInteraction::Pass);

	return isWalkable;
}

void CTileMap::draw(sf::RenderTarget& a_target, sf::RenderStates a_states) const
{
	a_states.transform *= getTransform();

	a_states.texture = &CTextureBank::GetUnorderedTexture(m_tileset->GetTexture());

	a_target.draw(m_vertices, a_states);
}

void CTileMap::SetTile(short a_tileIndex, STileData a_newTile)
{
	m_groundTiles[a_tileIndex] = a_newTile;
}

void CTileMap::RunItemSpawnForTileInteraction(ETileInteraction a_interaction, short a_tileIndexInTileSet, short a_tileIndexInMap)
{
	const std::vector<SItemSpawnData>& itemSpawnList = m_tileset->GetTileData(a_tileIndexInTileSet).m_onInteractionSpawnlist[static_cast<size_t>(a_interaction)];

	for (const SItemSpawnData& itemSpawnData : itemSpawnList)
	{
		if (itemSpawnData.m_itemId == -1)
		{
			continue;
		}
		
		bool shouldSpawn = Math::Chance(itemSpawnData.m_chance);

		if (shouldSpawn == false)
		{
			continue;
		}

		short amountToSpawn = 0;

		if (itemSpawnData.m_minSpawnAmount == itemSpawnData.m_maxSpawnAmount)
		{
			amountToSpawn = itemSpawnData.m_minSpawnAmount;
		}
		else
		{
			amountToSpawn = Math::RandomInRange(itemSpawnData.m_minSpawnAmount, itemSpawnData.m_maxSpawnAmount);
		}

		m_ownerZone->SpawnItem(itemSpawnData.m_itemId, amountToSpawn, GetTilePosition(a_tileIndexInMap));
	}
}

void CTileMap::ResetWateredTiles()
{
	for (size_t i = 0; i < m_tileCount; ++i)
	{
		m_wateredTiles[i] = false;
	}
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

	sf::View camera = CRenderer::GetInstance().GetCamera();
	sf::FloatRect cameraRect;
	sf::Vector2f cameraSize = camera.getSize() * 1.1f;

	cameraRect.left = camera.getCenter().x - cameraSize.x / 2;
	cameraRect.top = camera.getCenter().y - cameraSize.y / 2;
	cameraRect.width = cameraSize.x;
	cameraRect.height = cameraSize.y;

	if (!cameraRect.contains(tilePosition))
	{
		return;
	}

	short groundTileIndex = m_groundTiles[a_indexInMap];

	if (m_tileset->GetTileData(m_groundTiles[a_indexInMap]).m_isAdaptive)
	{
		groundTileIndex = m_tileset->CalculateAdaptiveTile(groundTileIndex, GetNeighbouringTiles(groundTileIndex, a_indexInMap, m_groundTiles));
	}

	sf::IntRect texRect = m_tileset->GetTileData(groundTileIndex).m_textureRect;

	sf::Vertex* quad = &m_vertices[a_indexInMap * 4];
	quad[0].position = sf::Vector2f(tilePosition.x, tilePosition.y);
	quad[1].position = sf::Vector2f(tilePosition.x + m_tileWidth, tilePosition.y);
	quad[2].position = sf::Vector2f(tilePosition.x + m_tileWidth, tilePosition.y + m_tileHeight);
	quad[3].position = sf::Vector2f(tilePosition.x, tilePosition.y + m_tileHeight);

	quad[0].texCoords =	sf::Vector2f(texRect.left, texRect.top);
	quad[1].texCoords = sf::Vector2f(texRect.left + texRect.width, texRect.top);
	quad[2].texCoords = sf::Vector2f(texRect.left + texRect.width, texRect.top + texRect.height);
	quad[3].texCoords = sf::Vector2f(texRect.left, texRect.top + texRect.height);

	//m_tileset->DrawTileAtPosition(groundTileIndex, tilePosition);

	sf::Color wetnessTint = sf::Color::White;
	bool wateredTileIndex = m_wateredTiles[a_indexInMap];
	if (wateredTileIndex)
	{
		wetnessTint = sf::Color(150, 150, 150, 255);
	}

	short interactedTileIndex = m_interactedTiles[a_indexInMap];
	if (interactedTileIndex != -1) //Do not render anything if no interaction was made to the tile
	{
		if (m_tileset->GetTileData(m_interactedTiles[a_indexInMap]).m_isAdaptive)
		{
			interactedTileIndex = m_tileset->CalculateAdaptiveTile(interactedTileIndex, GetNeighbouringTiles(interactedTileIndex, a_indexInMap, m_interactedTiles));
		}
		
		m_tileset->DrawTileAtPosition(interactedTileIndex, tilePosition, wetnessTint);
	}

}

