#pragma once
#include "SFML/Graphics/Rect.hpp"

class CTileset;

class CTileSelector : public sf::FloatRect
{
public:
	CTileSelector();
	~CTileSelector();

	void Render();
	void SetTilesetPointer(CTileset* a_tilesetPtr);

private:

	CTileset* m_tileset;
};

