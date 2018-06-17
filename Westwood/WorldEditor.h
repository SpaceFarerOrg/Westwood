#pragma once
#include "SFML/System/Vector2.hpp"

class CWorldZone;
namespace sf
{
	class RenderWindow;
}

class CWorldEditor
{
public:
	CWorldEditor(sf::RenderWindow* a_renderWindow);
	~CWorldEditor();

	void Initialize();
	void Update(CWorldZone& a_worldZone);
	void Render();
	bool IsInEditMode();

private:
	sf::RenderWindow* m_renderWindow;
	sf::Vector2f m_prevMPos;
	sf::Vector2f m_zoom;
	sf::Vector2f m_originalSize;
	bool m_editMode : 1;
};

