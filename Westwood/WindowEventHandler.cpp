#include "WindowEventHandler.h"
#include <SFML\Graphics\RenderWindow.hpp>
#include <SFML\Window\Event.hpp>

CWindowEventHandler::CWindowEventHandler(sf::RenderWindow & a_window)
	:m_window(a_window),
	m_tempHasClosed(false)
{
}

void CWindowEventHandler::RunEventHandling()
{
	sf::Event e;

	while (m_window.pollEvent(e))
	{
		if (e.type == sf::Event::Closed)
		{
			m_tempHasClosed = true;
		}
	}
}

bool CWindowEventHandler::GetHasClosed() const
{
	return m_tempHasClosed;
}
