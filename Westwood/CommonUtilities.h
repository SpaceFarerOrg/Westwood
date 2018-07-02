#pragma once
#include <vector>
#include <string>
#include <sstream>

std::vector<std::string> SplitString(const std::string& a_string, char a_delimiter)
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
