#pragma once
#include <vector>
#include <SFML\Graphics\Sprite.hpp>
#include <SFML\Graphics\RectangleShape.hpp>
#include <SFML\Graphics\Text.hpp>
#include <SFML\Graphics\RenderWindow.hpp>
#include <SFML\System\Vector2.hpp>

class CRenderer
{
public:
	CRenderer();
	~CRenderer();

	void Initialize();
	void RenderToWindow();

	sf::RenderWindow& GetWindow();

	static void PushRenderCommand(const sf::Sprite& a_renderCommand);
	static void PushRenderCommand(const sf::RectangleShape& a_renderCommand);
	static void PushRenderCommand(const sf::Text& a_renderCommand);
	static void PushUIRenderCommand(const sf::Sprite& a_renderCommand);
	static void PushUIRenderCommand(const sf::RectangleShape& a_renderCommand);
	
	static const sf::Vector2f& GetWindowDimensions();
private:
	static std::vector<sf::Sprite> m_renderQueue;
	static std::vector<sf::RectangleShape> m_rectangleQueue;
	static std::vector<sf::Sprite> m_UIRenderQueue;
	static std::vector<sf::Text> m_textQueue;
	static std::vector<sf::RectangleShape> m_UIRectangleQueue;
	
	static sf::Vector2f m_currentWindowDimensions;
	
	sf::RenderWindow m_renderWindow;
	sf::RenderTarget* m_currentRenderTarget;
};