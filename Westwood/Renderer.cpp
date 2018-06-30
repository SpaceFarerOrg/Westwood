#include "Renderer.h"
#include "InputManager.h"
#include "TileMap.h"

CRenderer::CRenderer()
	: m_currentRenderTarget(nullptr)
{
}

CRenderer::~CRenderer()
{
}

CRenderer & CRenderer::GetInstance()
{
	static CRenderer instance;

	return instance;
}

void CRenderer::Initialize()
{
	sf::VideoMode videoMode = sf::VideoMode::getDesktopMode();

	m_renderWindow.create(videoMode, "Game", sf::Style::Close);
	CInputManager::GetInstance().Init(&m_renderWindow);

	m_currentWindowDimensions.x = static_cast<float>(videoMode.width);
	m_currentWindowDimensions.y = static_cast<float>(videoMode.height);

	m_camera.setSize(m_currentWindowDimensions);
	m_shouldIgnoreCameraTarget = false;
}

void CRenderer::RenderToWindow()
{
	m_currentRenderTarget = &m_renderWindow;

	/*Camera space rendering*/
	m_renderWindow.setView(m_camera);

	m_camera.setCenter(m_cameraTarget);

	RenderQueue(m_renderCommands);

	/*End camera space rendering*/

	/*Screen space rendering*/
	sf::View view = m_renderWindow.getView();

	m_renderWindow.setView(m_renderWindow.getDefaultView());

	RenderQueue(m_UIRenderCommands);

	m_renderWindow.setView(view);
	/*End Screen space rendering*/

	m_renderWindow.display();
}

void CRenderer::Clear()
{
	m_renderWindow.clear(sf::Color(50, 150, 255, 255));
}

sf::RenderWindow & CRenderer::GetWindow()
{
	return m_renderWindow;
}

void CRenderer::PushRenderCommand(const sf::Sprite & a_renderCommand, int a_layer)
{
	SRenderCommand rc;
	rc.m_type = ERenderCommandType::Sprite;
	rc.m_layer = a_layer;
	rc.m_spriteData = a_renderCommand;
	m_renderCommands.push_back(rc);
}

void CRenderer::PushRenderCommand(const sf::RectangleShape & a_renderCommand, int a_layer)
{
	SRenderCommand rc;
	rc.m_type = ERenderCommandType::RectangleShape;
	rc.m_layer = a_layer;
	rc.m_rectShapeData = a_renderCommand;
	m_renderCommands.push_back(rc);
}

void CRenderer::PushRenderCommand(const sf::Text& a_renderCommand, int a_layer)
{
	SRenderCommand rc;
	rc.m_type = ERenderCommandType::Text;
	rc.m_layer = a_layer;
	rc.m_textData = a_renderCommand;
	m_renderCommands.push_back(rc);
}

const sf::Vector2f & CRenderer::GetWindowDimensions()
{
	return m_currentWindowDimensions;
}

void CRenderer::SetCameraTarget(const sf::Vector2f & a_targetPosition)
{
	if (m_shouldIgnoreCameraTarget == false)
	{
		m_cameraTarget = a_targetPosition;
	}
}

void CRenderer::SetShouldIgnoreCameraTarget(bool a_shouldIgnore)
{
	m_shouldIgnoreCameraTarget = a_shouldIgnore;
}

sf::View CRenderer::GetCamera()
{
	return m_camera;
}

void CRenderer::PushUIRenderCommand(const sf::Sprite & a_renderCommand, int a_layer)
{
	SRenderCommand rc;
	rc.m_type = ERenderCommandType::Sprite;
	rc.m_layer = a_layer;
	rc.m_spriteData = a_renderCommand;
	m_UIRenderCommands.push_back(rc);
}

void CRenderer::PushUIRenderCommand(const sf::RectangleShape & a_renderCommand, int a_layer)
{
	SRenderCommand rc;
	rc.m_type = ERenderCommandType::RectangleShape;
	rc.m_layer = a_layer;
	rc.m_rectShapeData = a_renderCommand;
	m_UIRenderCommands.push_back(rc);
}

void CRenderer::PushUIRenderCommand(const sf::Text & a_renderCommand, int a_layer)
{
	SRenderCommand rc;
	rc.m_type = ERenderCommandType::Text;
	rc.m_layer = a_layer;
	rc.m_textData = a_renderCommand;
	m_UIRenderCommands.push_back(rc);
}

void CRenderer::RenderTileMap(const CTileMap & a_tileMap)
{
	m_renderWindow.draw(a_tileMap);
}

void CRenderer::RenderQueue(std::vector<SRenderCommand>& a_renderQueue)
{
	std::sort(a_renderQueue.begin(), a_renderQueue.end());

	for (SRenderCommand& command : a_renderQueue)
	{
		switch (command.m_type)
		{
		case ERenderCommandType::Sprite:
			m_currentRenderTarget->draw(command.m_spriteData);
			break;
		case ERenderCommandType::Text:
			m_currentRenderTarget->draw(command.m_textData);
			break;
		case ERenderCommandType::RectangleShape:
			m_currentRenderTarget->draw(command.m_rectShapeData);
			break;
		}
	}

	a_renderQueue.clear();
}
