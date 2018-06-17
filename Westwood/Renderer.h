#pragma once
#include <vector>
#include <SFML\Graphics\Sprite.hpp>
#include <SFML\Graphics\RectangleShape.hpp>
#include <SFML\Graphics\RenderWindow.hpp>

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

	static void PushUIRenderCommand(const sf::Sprite& a_renderCommand);
	static void PushUIRenderCommand(const sf::RectangleShape& a_renderCommand);
private:
	static std::vector<sf::Sprite> m_renderQueue;
	static std::vector<sf::RectangleShape> m_rectangleQueue;
	static std::vector<sf::Sprite> m_UIRenderQueue;
	static std::vector<sf::RectangleShape> m_UIRectangleQueue;
	
	sf::RenderWindow m_renderWindow;
	sf::RenderTarget* m_currentRenderTarget;
};