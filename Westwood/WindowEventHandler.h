#pragma once

namespace sf
{
	class RenderWindow;
}

class CWindowEventHandler
{
public:
	CWindowEventHandler() = delete;
	CWindowEventHandler(sf::RenderWindow& a_window);

	void RunEventHandling();

	bool GetHasClosed() const;
private:
	sf::RenderWindow& m_window;
	bool m_tempHasClosed; //Temp variable until event system is in place 
};