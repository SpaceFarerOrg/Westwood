#include "TextureBank.h"

std::array<sf::Texture, static_cast<size_t>(ETextures::Count)> CTextureBank::m_bank;
std::unordered_map<std::string, ETextures> CTextureBank::m_textureNameToIndexLUT;

CTextureBank::CTextureBank()
{
}

void CTextureBank::LoadAllTextures()
{
	LoadTexture(ETextures::TestTileset, "debugSpriteSheet");
}

const sf::Texture & CTextureBank::GetTexture(ETextures a_textureToGet)
{
	return m_bank[static_cast<size_t>(a_textureToGet)];
}

const ETextures CTextureBank::GetTextureIndex(const char* a_textureName)
{
	return m_textureNameToIndexLUT[a_textureName];
}

void CTextureBank::LoadTexture(ETextures a_texture, const sf::String& a_pathRelativeToGraphics)
{
	sf::String completePath = "graphics/" + a_pathRelativeToGraphics + ".png";

	m_textureNameToIndexLUT[a_pathRelativeToGraphics] = a_texture;

	m_bank[static_cast<size_t>(a_texture)].loadFromFile(completePath);
}
