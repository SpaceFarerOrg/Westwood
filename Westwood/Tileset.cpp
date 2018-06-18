#include "Tileset.h"
#include "TextureBank.h"
#include "Renderer.h"


void CTileset::LoadFromJson(nlohmann::json & a_tilesetJson)
{
	m_tileWidth = a_tilesetJson["tilewidth"].get<short>();
	m_tileHeight = a_tilesetJson["tileheight"].get<short>();

	m_tileCount = a_tilesetJson["tilecount"].get<short>();
	m_tiles = new STileData[m_tileCount];

	m_columns = a_tilesetJson["columns"].get<short>();

	m_texture = CTextureBank::LoadUnorderedTexture(a_tilesetJson["name"].get<std::string>().c_str());

	for (short tileIndex = 0; tileIndex < m_tileCount; ++tileIndex)
	{
		m_tiles[tileIndex].m_tileIndex = tileIndex;

		m_tiles[tileIndex].m_textureRect.width = m_tileWidth;
		m_tiles[tileIndex].m_textureRect.height = m_tileHeight;
		m_tiles[tileIndex].m_textureRect.left = (tileIndex % m_columns) * m_tileWidth;
		m_tiles[tileIndex].m_textureRect.top = (tileIndex / m_columns) * m_tileHeight;

		nlohmann::json tileData = a_tilesetJson["tileproperties"][std::to_string(tileIndex)];
		
		m_tiles[tileIndex].m_isPassable = false;
		m_tiles[tileIndex].m_isAdaptive = false;

		if (tileData.find("passable") != tileData.end())
		{
			m_tiles[tileIndex].m_isPassable = tileData["passable"].get<bool>();
		}
		if (tileData.find("adaptive") != tileData.end())
		{
			m_tiles[tileIndex].m_isAdaptive = true;

			LoadAdaptiveTile(tileIndex, tileData["adaptiveFile"].get<std::string>().c_str());
		}

	}
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

void CTileset::DrawTileAtPosition(short a_tileIndex, const sf::Vector2f & a_position)
{
	sf::Sprite tileRenderCommand;
	tileRenderCommand.setTexture(CTextureBank::GetUnorderedTexture(m_texture));

	tileRenderCommand.setTextureRect(m_tiles[a_tileIndex].m_textureRect);
	tileRenderCommand.setPosition(a_position);

	CRenderer::GetInstance().PushRenderCommand(tileRenderCommand);
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
