#pragma once
#include "SFML/System/Vector2.hpp"
#include "ButtonManager.h"
#include "TileSelector.h"

class CWorldZone;
class CTileMap;
namespace sf
{
	class RenderWindow;
}

class CWorldEditor
{
public:

	enum class EDrawingMode
	{
		Pencil,
		Line,
		Rectangle,
		Circle
	};

	CWorldEditor(sf::RenderWindow* a_renderWindow);
	~CWorldEditor();

	void Initialize();
	void Update(CWorldZone& a_worldZone);
	void Render();
	bool IsInEditMode();
	
	void SetDrawingMode(EDrawingMode a_drawingMode);
	void SaveCurrentZone();

private:
	void AddButtons();

	void DrawRectangleOnZone(short a_startTile, short a_endTile, CTileMap& a_tileMap);
	void ShowPreviewRectangle(short a_startTile, short a_endTile);

	sf::RenderWindow* m_renderWindow;
	sf::Vector2f m_prevMPos;
	sf::Vector2f m_zoom;
	sf::Vector2f m_originalSize;
	CButtonManager m_buttonManager;
	EDrawingMode m_drawingMode;
	CTileSelector m_tileSelector;
	short m_selectedTile;
	short m_startTile;

	bool m_editMode : 1;
};

