#pragma once
#include <vector>
#include <string>
#include <sstream>
#include <json.hpp>
#include <fstream>

static std::vector<std::string> SplitString(const std::string& a_string, char a_delimiter)
{
	std::stringstream ss(a_string);
	std::string item;
	std::vector<std::string> items;
	while (std::getline(ss, item, a_delimiter)) 
	{
		items.push_back(item);
	}
	return items;
}

static nlohmann::json OpenJson(const char* a_filePath)
{
	std::ifstream jsonFile(a_filePath);
	nlohmann::json json;
	jsonFile >> json;
	jsonFile.close();

	return std::move(json);
}
