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

	m_renderTarget0.create(m_currentWindowDimensions.x, m_currentWindowDimensions.y);
	m_renderTarget1.create(m_currentWindowDimensions.x, m_currentWindowDimensions.y);

	m_daytimeShader.loadFromFile("shaders/daytime.vfx", sf::Shader::Type::Fragment);
}

void CRenderer::RenderToWindow()
{
	/*Camera space rendering*/
	m_renderWindow.setView(m_camera);

	m_camera.setCenter(m_cameraTarget);

	for (int i = 0; i < m_renderCommands.size(); ++i)
	{
		RenderQueue(m_renderCommands[i]);
	}

	m_renderTarget0.display();
	/*End camera space rendering*/

	//*Fullscreen passes*
	ApplyFullscreenPasses();
	//End fullscreen passes

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
	rc.m_layer = a_renderCommand.getPosition().y;
	rc.m_spriteData = a_renderCommand;
	m_renderCommands[a_layer].push_back(rc);
}

void CRenderer::PushRenderCommand(const sf::RectangleShape & a_renderCommand, int a_layer)
{
	SRenderCommand rc;
	rc.m_type = ERenderCommandType::RectangleShape;
	rc.m_layer = a_renderCommand.getPosition().y;
	rc.m_rectShapeData = a_renderCommand;
	m_renderCommands[a_layer].push_back(rc);
}

void CRenderer::PushRenderCommand(const sf::Text& a_renderCommand, int a_layer)
{
	SRenderCommand rc;
	rc.m_type = ERenderCommandType::Text;
	rc.m_layer = a_renderCommand.getPosition().y;
	rc.m_textData = a_renderCommand;
	m_renderCommands[a_layer].push_back(rc);
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

void CRenderer::SetUniform(const sf::String & a_uniformName, float a_value)
{
	m_daytimeShader.setUniform(a_uniformName, a_value);
}

void CRenderer::RenderTileMap(const CTileMap & a_tileMap)
{
	m_currentRenderTarget = &m_renderTarget0;
	m_currentRenderTarget->draw(a_tileMap);
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

void CRenderer::ApplyFullscreenPasses()
{
	sf::Vertex vertices[4] = {
		sf::Vertex({0,0}, {0,1}),
		sf::Vertex({ m_currentWindowDimensions.x,0 },{ 1,1 }),
		sf::Vertex({ m_currentWindowDimensions.x,m_currentWindowDimensions.y },{ 1,0 }),
		sf::Vertex({ 0,m_currentWindowDimensions.y },{ 0,0 }),
	};

	m_daytimeShader.setUniform("texture", m_renderTarget0.getTexture());
	//sprite.setTexture(m_renderTarget0.getTexture());

	// Swap render targets between passes
	m_currentRenderTarget = &m_renderWindow;
	m_currentRenderTarget->draw(vertices, 4, sf::PrimitiveType::Quads, &m_daytimeShader);
	//m_currentRenderTarget->draw(sprite, &m_daytimeShader);

	// Finish and draw to render window
	m_currentRenderTarget = &m_renderWindow;
	
	//sprite.setTexture(m_renderTarget1.getTexture()); // Should match the last draw call

	//m_currentRenderTarget->draw(sprite);
}
