#include "TilesetBank.h"
#include <filesystem>
#include <json.hpp>
#include <string>
#include <fstream>


std::vector<CTileset> CTilesetBank::m_tilesets;
std::unordered_map<std::string, short> CTilesetBank::m_tilesetNameToIndexLUT;

void CTilesetBank::LoadAllTilesets()
{
	for (auto& path : std::experimental::filesystem::directory_iterator("data/tilesets/"))
	{
		std::experimental::filesystem::path fileP = path;
		
		/*Avoid loading only*/
		if (!fileP.has_extension())
			continue;

		std::wstring pathString = fileP.c_str();
		
		

		nlohmann::json tilesetJson;

		std::ifstream tilesetFile(pathString);
		tilesetFile >> tilesetJson;
		tilesetFile.close();

		m_tilesets.push_back(CTileset());

		m_tilesets.back().LoadFromJson(tilesetJson);

		m_tilesetNameToIndexLUT[tilesetJson["name"].get<std::string>()] = static_cast<short>(m_tilesets.size() - 1);
	}
}

CTileset & CTilesetBank::GetTileset(short a_tilesetID)
{
	return m_tilesets[a_tilesetID];
}

short CTilesetBank::GetTilesetIndex(const char * a_tilesetName)
{
	return m_tilesetNameToIndexLUT[a_tilesetName];
}
