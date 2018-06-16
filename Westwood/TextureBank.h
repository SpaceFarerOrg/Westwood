#pragma once
#include <array>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <SFML\Graphics\Texture.hpp>
#include <SFML\System\String.hpp>

enum class ETextures
{
	TestTileset,
	Count,
};

class CTextureBank
{
public:
	CTextureBank();
	void LoadAllTextures();
	static short LoadUnorderedTexture(const char* a_textureName);

	static const sf::Texture& GetTexture(ETextures a_textureToGet);
	static const sf::Texture& GetUnorderedTexture(short a_textureID);
	static const ETextures GetTextureIndex(const char* a_textureName);
private:
	void LoadTexture(ETextures a_texture, const sf::String& a_pathRelativeToGraphics);
	static std::unordered_map<std::string, ETextures> m_textureNameToIndexLUT;
	static std::array<sf::Texture, static_cast<size_t>(ETextures::Count)> m_bank;

	static std::vector<sf::Texture> m_unorderedBank;
};