#pragma once
#include <vector>
#include <SFML\Graphics\View.hpp>
#include <SFML\Graphics\Sprite.hpp>
#include <SFML\Graphics\RectangleShape.hpp>
#include <SFML\Graphics\Text.hpp>
#include <SFML\Graphics\RenderWindow.hpp>
#include <SFML\System\Vector2.hpp>

class CRenderer
{
public:
	static CRenderer& GetInstance();

	void Initialize();
	void RenderToWindow();

	sf::RenderWindow& GetWindow();

	void PushRenderCommand(const sf::Sprite& a_renderCommand);
	void PushRenderCommand(const sf::RectangleShape& a_renderCommand);
	void PushRenderCommand(const sf::Text& a_renderCommand);
	void PushUIRenderCommand(const sf::Sprite& a_renderCommand);
	void PushUIRenderCommand(const sf::RectangleShape& a_renderCommand);
	
	const sf::Vector2f& GetWindowDimensions();

	void SetCameraTarget(const sf::Vector2f& a_targetPosition);
private:
	CRenderer();
	~CRenderer();
	
	std::vector<sf::Sprite> m_renderQueue;
	std::vector<sf::RectangleShape> m_rectangleQueue;
	std::vector<sf::Sprite> m_UIRenderQueue;
	std::vector<sf::Text> m_textQueue;
	std::vector<sf::RectangleShape> m_UIRectangleQueue;
	
	sf::Vector2f m_currentWindowDimensions;

	sf::RenderWindow m_renderWindow;
	sf::RenderTarget* m_currentRenderTarget;

	sf::Vector2f m_cameraTarget;
	sf::View m_camera;
};