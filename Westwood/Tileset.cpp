#include "Tileset.h"
#include "TextureBank.h"
#include "Renderer.h"
#include "ItemBank.h"

void CTileset::LoadFromJson(nlohmann::json & a_tilesetJson)
{
	m_tileWidth = a_tilesetJson["tilewidth"].get<short>();
	m_tileHeight = a_tilesetJson["tileheight"].get<short>();

	m_tileCount = a_tilesetJson["tilecount"].get<short>();
	m_tiles = new STileData[m_tileCount];

	m_columns = a_tilesetJson["columns"].get<short>();

	m_tilesetName = a_tilesetJson["name"].get<std::string>();

	m_texture = CTextureBank::LoadUnorderedTexture(m_tilesetName.toAnsiString().c_str());

	for (short tileIndex = 0; tileIndex < m_tileCount; ++tileIndex)
	{
		nlohmann::json tileData = a_tilesetJson["tileproperties"][std::to_string(tileIndex)];

		LoadTileData(tileIndex, tileData);
	}

	LoadTilesInteractionData();
}

void CTileset::Unload()
{
	delete[] m_tiles;
}

const STileData & CTileset::GetTileData(short a_tileIndex) const
{
	return m_tiles[a_tileIndex];
}

short CTileset::CalculateAdaptiveTile(short a_tileIndex, const std::array<bool, 8>& a_neighbours)
{
	short tileIndex = a_tileIndex;

	if (a_neighbours[1] && a_neighbours[3] && a_neighbours[4] && a_neighbours[6])
	{
		tileIndex = m_tiles[a_tileIndex].GetAdaptiveIndex(EAdaptiveState::Center);
	}
	else if (a_neighbours[1] && a_neighbours[6] && a_neighbours[4])
	{
		tileIndex = m_tiles[a_tileIndex].GetAdaptiveIndex(EAdaptiveState::Left);
	}
	else if (a_neighbours[1] && a_neighbours[6] && a_neighbours[3])
	{
		tileIndex = m_tiles[a_tileIndex].GetAdaptiveIndex(EAdaptiveState::Right);
	}
	else if (a_neighbours[3] && a_neighbours[4] && a_neighbours[6])
	{
		tileIndex = m_tiles[a_tileIndex].GetAdaptiveIndex(EAdaptiveState::Top);
	}
	else if (a_neighbours[3] && a_neighbours[4] && a_neighbours[1])
	{
		tileIndex = m_tiles[a_tileIndex].GetAdaptiveIndex(EAdaptiveState::Bottom);
	}
	else if (a_neighbours[4] && a_neighbours[6])
	{
		tileIndex = m_tiles[a_tileIndex].GetAdaptiveIndex(EAdaptiveState::UpperLeftCorner);
	}
	else if (a_neighbours[3] && a_neighbours[6])
	{
		tileIndex = m_tiles[a_tileIndex].GetAdaptiveIndex(EAdaptiveState::UpperRightCorner);
	}
	else if (a_neighbours[1] && a_neighbours[4])
	{
		tileIndex = m_tiles[a_tileIndex].GetAdaptiveIndex(EAdaptiveState::LowerLeftCorner);
	}
	else if (a_neighbours[1] && a_neighbours[3])
	{
		tileIndex = m_tiles[a_tileIndex].GetAdaptiveIndex(EAdaptiveState::LowerRightCorner);
	}
	else if (a_neighbours[3] && a_neighbours[4])
	{
		tileIndex = m_tiles[a_tileIndex].GetAdaptiveIndex(EAdaptiveState::CenterOfHorizontalLine);
	}
	else if (a_neighbours[1] && a_neighbours[6])
	{
		tileIndex = m_tiles[a_tileIndex].GetAdaptiveIndex(EAdaptiveState::CenterOfVerticalLine);
	}
	else if (a_neighbours[3])
	{
		tileIndex = m_tiles[a_tileIndex].GetAdaptiveIndex(EAdaptiveState::LonelyWithLeftNeighbour);
	}
	else if (a_neighbours[4])
	{
		tileIndex = m_tiles[a_tileIndex].GetAdaptiveIndex(EAdaptiveState::LonelyWithRightNeighbour);
	}
	else if (a_neighbours[1])
	{
		tileIndex = m_tiles[a_tileIndex].GetAdaptiveIndex(EAdaptiveState::LonelyWithUpperNeighbour);
	}
	else if (a_neighbours[6])
	{
		tileIndex = m_tiles[a_tileIndex].GetAdaptiveIndex(EAdaptiveState::LonelyWithLowerNeighbour);
	}

	return tileIndex;
}

void CTileset::DrawTileAtPosition(short a_tileIndex, const sf::Vector2f & a_position, const sf::Color& a_colorTint)
{
	sf::Sprite tileRenderCommand;
	tileRenderCommand.setTexture(CTextureBank::GetUnorderedTexture(m_texture));

	tileRenderCommand.setTextureRect(m_tiles[a_tileIndex].m_textureRect);
	tileRenderCommand.setPosition(a_position);
	tileRenderCommand.setColor(a_colorTint);

	CRenderer::GetInstance().PushRenderCommand(tileRenderCommand);
}

short CTileset::GetTexture()
{
	return m_texture;
}

#include <fstream>
void CTileset::LoadAdaptiveTile(short a_tileIndex, const char* a_adaptiveJson)
{
	std::string adaptiveFilePath = "data/tilesets/adaptive/";
	adaptiveFilePath += a_adaptiveJson;
	adaptiveFilePath += ".json";

	std::ifstream adaptiveFile(adaptiveFilePath);
	nlohmann::json adaptiveJson;
	adaptiveFile >> adaptiveJson;
	adaptiveFile.close();

	for (size_t i = 0; i < adaptiveJson["adaptiveIndexes"].size(); ++i)
	{
		m_tiles[a_tileIndex].m_adaptiveIndexLUT[i] = adaptiveJson["adaptiveIndexes"][i].get<short>();
	}
}

void CTileset::LoadTileData(short a_tileIndex, nlohmann::json & a_tileInJson)
{
	m_tiles[a_tileIndex].m_tileIndex = a_tileIndex;

	m_tiles[a_tileIndex].m_textureRect.width = m_tileWidth;
	m_tiles[a_tileIndex].m_textureRect.height = m_tileHeight;
	m_tiles[a_tileIndex].m_textureRect.left = (a_tileIndex % m_columns) * m_tileWidth;
	m_tiles[a_tileIndex].m_textureRect.top = (a_tileIndex / m_columns) * m_tileHeight;

	if (a_tileInJson.find("passable") != a_tileInJson.end())
	{
		m_tiles[a_tileIndex].SetInteractionAllowance(ETileInteraction::Pass, true);
	}
	if (a_tileInJson.find("plowable") != a_tileInJson.end())
	{
		m_tiles[a_tileIndex].SetInteractionAllowance(ETileInteraction::Dig, true);
		m_tiles[a_tileIndex].SetInteractionAllowance(ETileInteraction::Water, true);
	}
	if (a_tileInJson.find("adaptive") != a_tileInJson.end())
	{
		m_tiles[a_tileIndex].m_isAdaptive = true;

		LoadAdaptiveTile(a_tileIndex, a_tileInJson["adaptiveFile"].get<std::string>().c_str());
	}
}

void CTileset::LoadTilesInteractionData()
{
	std::string interactionsDataFilePath = "data/tilesets/" + m_tilesetName + "InteractionData.json";
	nlohmann::json interactionDataJson;

	std::ifstream interactionDataFile(interactionsDataFilePath);
	interactionDataFile >> interactionDataJson;
	interactionDataFile.close();

	nlohmann::json interactedData = interactionDataJson["interactableTiles"];

	for (size_t i = 0; i < interactedData.size(); ++i)
	{
		short tileIndex = interactedData[i]["tile"].get<short>();
		STileData& tile = m_tiles[tileIndex];

		if (interactedData[i].find("dig") != interactedData[i].end()) //If dig exists
		{
			tile.SetTileToAddOnInteraction(ETileInteraction::Dig, interactedData[i]["dig"]["addInteractionLayerTile"].get<short>());

			LoadItemSpawnOnInteraction(ETileInteraction::Dig, tileIndex,interactedData[i]["dig"]["spawnItems"]);
		}
	}
}

void CTileset::LoadItemSpawnOnInteraction(ETileInteraction a_interaction, short a_tileIndex, nlohmann::json & a_spawnItemsData)
{
	for (size_t i = 0; i < a_spawnItemsData.size(); ++i)
	{
		short itemID = CItemBank::GetInstance().GetItemID(a_spawnItemsData[i]["itemName"].get<std::string>().c_str());
		short spawnChance = a_spawnItemsData[i]["chance"].get<short>();
		short minSpawnAmount = a_spawnItemsData[i]["minAmount"].get<short>();
		short maxSpawnAmount = a_spawnItemsData[i]["maxAmount"].get<short>();

		m_tiles[a_tileIndex].AddInteractionItemSpawn(itemID, spawnChance, a_interaction, minSpawnAmount, maxSpawnAmount);
	}
}
