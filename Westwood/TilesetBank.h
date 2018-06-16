#pragma once
#include "Tileset.h"
#include <vector>
#include <json.hpp>
#include <unordered_map>


class CTilesetBank
{
public:
	void LoadAllTilesets();

	static CTileset& GetTileset(short a_tilesetID);
	static short GetTilesetIndex(const char* a_tilesetName);
private:
	static std::vector<CTileset> m_tilesets;
	static std::unordered_map<std::string, short> m_tilesetNameToIndexLUT;
};