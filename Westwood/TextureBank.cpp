#include "TextureBank.h"

std::array<sf::Texture, static_cast<size_t>(ETextures::Count)> CTextureBank::m_bank;
std::array<sf::Font, static_cast<size_t>(EFonts::Count)> CTextureBank::m_fontBank;
std::unordered_map<std::string, ETextures> CTextureBank::m_textureNameToIndexLUT;
std::unordered_map<std::string, short> CTextureBank::m_unorderedTexturesLUT;
std::vector<sf::Texture> CTextureBank::m_unorderedBank;

CTextureBank::CTextureBank()
{
	m_unorderedBank.reserve(256);

}

void CTextureBank::LoadAllTextures()
{
	LoadTexture(ETextures::TestTileset, "debugSpriteSheet");
	LoadTexture(ETextures::PlayerCharacter, "debugPlayerSprite");
	LoadTexture(ETextures::Items, "items");
	LoadTexture(ETextures::Objects, "objects");
	LoadTexture(ETextures::Plants, "plants");
}

void CTextureBank::LoadAllFonts()
{
	LoadFont(EFonts::Debug, "debug");
}

short CTextureBank::LoadUnorderedTexture(const char * a_textureName)
{
	if (m_unorderedTexturesLUT.find(a_textureName) != m_unorderedTexturesLUT.end())
	{
		return m_unorderedTexturesLUT[a_textureName];
	}

	sf::String textureName = a_textureName;
	sf::String completePath = "graphics/" + textureName + ".png";

	m_unorderedBank.push_back(sf::Texture());
	m_unorderedBank.back().loadFromFile(completePath);

	m_unorderedTexturesLUT[textureName.toAnsiString().c_str()] = static_cast<short>(m_unorderedBank.size() - 1);


	return static_cast<short>(m_unorderedBank.size() - 1);
}

const sf::Texture & CTextureBank::GetTexture(ETextures a_textureToGet)
{
	return m_bank[static_cast<size_t>(a_textureToGet)];
}

const sf::Texture & CTextureBank::GetUnorderedTexture(short a_textureID)
{
	return m_unorderedBank[a_textureID];
}

const ETextures CTextureBank::GetTextureIndex(const char* a_textureName)
{
	return m_textureNameToIndexLUT[a_textureName];
}

const sf::Font & CTextureBank::GetFont(EFonts a_font)
{
	return m_fontBank[static_cast<size_t>(a_font)];
}

void CTextureBank::LoadTexture(ETextures a_texture, const sf::String& a_pathRelativeToGraphics)
{
	sf::String completePath = "graphics/" + a_pathRelativeToGraphics + ".png";

	m_textureNameToIndexLUT[a_pathRelativeToGraphics] = a_texture;

	m_bank[static_cast<size_t>(a_texture)].loadFromFile(completePath);
}

void CTextureBank::LoadFont(EFonts a_font, const sf::String & a_pathRelativeToFonts)
{
	sf::String fullPath = "graphics/fonts/";
	fullPath += a_pathRelativeToFonts;
	fullPath += ".ttf";

	m_fontBank[static_cast<size_t>(a_font)].loadFromFile(fullPath);
}
