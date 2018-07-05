#pragma once
#include <vector>
#include <SFML\Graphics\View.hpp>
#include <SFML\Graphics\Sprite.hpp>
#include <SFML\Graphics\RectangleShape.hpp>
#include <SFML\Graphics\Text.hpp>
#include <SFML\Graphics\RenderWindow.hpp>
#include <SFML\Graphics\RenderTexture.hpp>
#include <SFML\Graphics\Shader.hpp>
#include <SFML\System\Vector2.hpp>

#include <array>

#define LAYER_GROUND 0
#define LAYER_PATH	 1
#define LAYER_OBJECT 2
#define LAYER_UI	 3

class CRenderer
{
public:
	static CRenderer& GetInstance();

	void Initialize();
	void RenderToWindow();
	void Clear();

	sf::RenderWindow& GetWindow();

	void PushRenderCommand(const sf::Sprite& a_renderCommand, int a_layer = 0);
	void PushRenderCommand(const sf::RectangleShape& a_renderCommand, int a_layer = 0);
	void PushRenderCommand(const sf::Text& a_renderCommand, int a_layer = 0);
	void PushUIRenderCommand(const sf::Sprite& a_renderCommand, int a_layer = 0);
	void PushUIRenderCommand(const sf::RectangleShape& a_renderCommand, int a_layer = 0);
	void PushUIRenderCommand(const sf::Text& a_renderCommand, int a_layer = 0);

	void SetUniform(const sf::String& a_uniformName, float a_value);

	void RenderTileMap(const class CTileMap& a_tileMap);

	const sf::Vector2f& GetWindowDimensions();

	void SetCameraTarget(const sf::Vector2f& a_targetPosition);
	void SetShouldIgnoreCameraTarget(bool a_shouldIgnore);

	sf::View GetCamera();
private:
	CRenderer();
	~CRenderer();

	enum class ERenderCommandType
	{
		Sprite,
		RectangleShape,
		Text
	};

	struct SRenderCommand
	{
		ERenderCommandType m_type;
		int m_layer;

		sf::Sprite m_spriteData;
		sf::RectangleShape m_rectShapeData;
		sf::Text m_textData;

		bool operator<(const SRenderCommand& a_other)
		{
			return m_layer < a_other.m_layer;
		}
	};

	void RenderQueue(std::vector<SRenderCommand>& a_renderQueue);
	void ApplyFullscreenPasses();
	
	std::array<std::vector<SRenderCommand>, 4> m_renderCommands;

	std::vector<SRenderCommand> m_UIRenderCommands;
	
	sf::Vector2f m_currentWindowDimensions;

	sf::RenderWindow m_renderWindow;

	sf::RenderTexture m_renderTarget0;
	sf::RenderTexture m_renderTarget1;

	sf::RenderTarget* m_currentRenderTarget;

	sf::Vector2f m_cameraTarget;
	sf::View m_camera;
	bool m_shouldIgnoreCameraTarget;

	sf::Shader m_daytimeShader;
};