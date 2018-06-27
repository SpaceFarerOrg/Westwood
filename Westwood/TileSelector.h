#pragma once
#include "SFML/Graphics/Rect.hpp"

class CTileset;

class CTileSelector : public sf::FloatRect
{
public:
	CTileSelector();
	~CTileSelector();

	short Update();
	void Render();
	void SetTilesetPointer(CTileset* a_tilesetPtr);

private:

	CTileset* m_tileset;
	float m_tileSize;
};

