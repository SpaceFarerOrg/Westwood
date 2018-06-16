#include "WorldEditor.h"
#include "InputManager.h"
#include "SFML/Graphics/RenderWindow.hpp"
#include "WorldZone.h"
#include "SFML/Graphics/RectangleShape.hpp"
#include "Renderer.h"

CWorldEditor::CWorldEditor()
{
	m_editMode = false;
}


CWorldEditor::~CWorldEditor()
{
}

void CWorldEditor::Update(CWorldZone& a_worldZone)
{
	a_worldZone.m_tileMap;
	CInputManager& inputManager = CInputManager::GetInstance();

	if (inputManager.IsKeyPressed(EKeyCode::F3))
	{
		m_editMode = !m_editMode;
	}

	if (m_editMode == false)
	{
		return;
	}

	sf::Vector2f mPos = inputManager.GetMousePosFloat();

	short tileIndex = a_worldZone.m_tileMap.ConvertPositionToTileIndex(mPos);
	sf::Vector2f currentBox = a_worldZone.m_tileMap.GetTilePosition(tileIndex);

	sf::RectangleShape rect;
	rect.setSize({(float)a_worldZone.m_tileMap.m_tileWidth, (float)a_worldZone.m_tileMap.m_tileHeight});
	rect.setPosition(currentBox);
	CRenderer::PushRenderCommand(rect);

	if (inputManager.IsKeyPressed(EKeyCode::MouseLeft))
	{
		STileData tileData;
		tileData.m_allowedInteraction = ETileInteraction::Count;
		tileData.m_isPassable = true;
		tileData.m_tileIndex = 0;
		
		a_worldZone.m_tileMap.SetTile(mPos, tileData);
	}
}

void CWorldEditor::Render(sf::RenderWindow* a_window)
{
	if (m_editMode)
	{
		sf::RectangleShape rect;
		rect.setOutlineThickness(5.f);
		rect.setOrigin(a_window->getView().getCenter());
		rect.setPosition((float)a_window->getView().getCenter().x + 5, (float)a_window->getView().getCenter().y + 5);
		rect.setSize({ (float)a_window->getSize().x - 10, (float)a_window->getSize().y - 10 });
		rect.setFillColor(sf::Color::Transparent);
		rect.setOutlineColor(sf::Color::Red);

		CRenderer::PushRenderCommand(rect);
	}
}

bool CWorldEditor::IsInEditMode()
{
	return m_editMode;
}
