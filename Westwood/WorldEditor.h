#pragma once

class CWorldZone;
namespace sf
{
	class RenderWindow;
}

class CWorldEditor
{
public:
	CWorldEditor();
	~CWorldEditor();

	void Update(CWorldZone& a_worldZone);
	void Render(sf::RenderWindow* a_window);
	bool IsInEditMode();

private:
	bool m_editMode : 1;
};

