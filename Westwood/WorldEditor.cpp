#include "WorldEditor.h"
#include "InputManager.h"
#include "SFML/Graphics/RenderWindow.hpp"
#include "WorldZone.h"
#include "SFML/Graphics/RectangleShape.hpp"
#include "Renderer.h"

CWorldEditor::CWorldEditor(sf::RenderWindow* a_renderWindow)
{
	m_editMode = false;
	m_renderWindow = a_renderWindow;
}


CWorldEditor::~CWorldEditor()
{
}

void CWorldEditor::Initialize()
{
	m_zoom = m_renderWindow->getView().getSize();
	m_originalSize = m_zoom;

	AddButtons();
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

	m_buttonManager.Update();

	sf::Vector2f mPos = inputManager.GetMousePosFloat();

	sf::Vector2f convertedPos = mPos;
	sf::Vector2f zoomAdjustedMovement = (m_renderWindow->getView().getCenter() - m_renderWindow->getView().getSize() / 2.f);

	zoomAdjustedMovement.x *= m_zoom.x / m_originalSize.x;
	zoomAdjustedMovement.y *= m_zoom.y / m_originalSize.y;

	convertedPos += zoomAdjustedMovement;

	short tileIndex = a_worldZone.m_tileMap.ConvertPositionToTileIndex(convertedPos, { m_zoom.x / m_originalSize.x, m_zoom.y / m_originalSize.y });
	sf::Vector2f currentBox = a_worldZone.m_tileMap.GetTilePosition(tileIndex);

	sf::RectangleShape rect;
	rect.setSize({(float)a_worldZone.m_tileMap.m_tileWidth, (float)a_worldZone.m_tileMap.m_tileHeight});
	rect.setPosition(currentBox);
	rect.setFillColor(sf::Color(100, 50, 50, 100));
	CRenderer::GetInstance().PushRenderCommand(rect);

	if (inputManager.IsKeyPressed(EKeyCode::MouseLeft))
	{
		STileData tileData;
		tileData.m_allowedInteraction = ETileInteraction::Count;
		tileData.m_isPassable = true;
		tileData.m_tileIndex = 0;
		
		a_worldZone.m_tileMap.SetTile(tileIndex, tileData);
	}

	sf::View view = m_renderWindow->getView();
	bool shouldUpdateView = false;
	//float scrollDelta = static_cast<float>(inputManager.GetScrollWheelDelta());
	//
	//if (scrollDelta != 0)
	//{
	//	m_zoom *= 1.f - 0.05f * scrollDelta;
	//	view.setSize(m_zoom);
	//	shouldUpdateView = true;
	//}

	if (inputManager.IsKeyDown(EKeyCode::MouseMiddle))
	{
		sf::Vector2f movement = (m_prevMPos - inputManager.GetMousePosFloat());

		movement.x *= m_zoom.x / m_originalSize.x;
		movement.y *= m_zoom.y / m_originalSize.y;

		view.setCenter(view.getCenter() + movement);
		shouldUpdateView = true;
	}

	if (shouldUpdateView)
	{
		m_renderWindow->setView(view);
	}

	m_prevMPos = inputManager.GetMousePosFloat();
}

void CWorldEditor::Render()
{
	if (m_editMode)
	{
		sf::RectangleShape rect;
		rect.setOutlineThickness(5.f);
		rect.setOrigin(m_renderWindow->getView().getCenter());
		rect.setPosition((float)m_renderWindow->getView().getCenter().x + 5, (float)m_renderWindow->getView().getCenter().y + 5);
		rect.setSize({ (float)m_renderWindow->getSize().x - 10, (float)m_renderWindow->getSize().y - 10 });
		rect.setFillColor(sf::Color::Transparent);
		rect.setOutlineColor(sf::Color::Red);

		CRenderer::GetInstance().PushUIRenderCommand(rect);

		sf::RectangleShape background;
		background.setSize({ (float)m_renderWindow->getView().getSize().x, (float)m_renderWindow->getView().getSize().y / 10.f });
		background.setFillColor(sf::Color(50, 50, 75, 255));
		CRenderer::GetInstance().PushUIRenderCommand(background);

		m_buttonManager.Render();
	}
}

bool CWorldEditor::IsInEditMode()
{
	return m_editMode;
}

void CWorldEditor::AddButtons()
{
	CUIButton& button = m_buttonManager.AddButton();

	button.top = 0;
	button.left = 0;
	button.width = 64;
	button.height = 64;
}
