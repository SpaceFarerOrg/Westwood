#pragma once
#include <vector>
#include <SFML\Graphics\Sprite.hpp>
#include <SFML\Graphics\RenderWindow.hpp>

class CRenderer
{
public:
	CRenderer();
	~CRenderer();

	void Initialize();
	void RenderToWindow();

	static void PushRenderCommand(const sf::Sprite& a_renderCommand);
private:
	static std::vector<sf::Sprite> m_renderQueue;
	
	sf::RenderWindow m_renderWindow;
	sf::RenderTarget* m_currentRenderTarget;
};