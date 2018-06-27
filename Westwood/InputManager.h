#pragma once
#include "KeyCodes.h"
#include <map>
#include "SFML\Window\Window.hpp"
#include "SFML\System\Vector2.hpp"

class CInputManager
{
public:
	~CInputManager();

	static CInputManager& GetInstance();

	void Init(sf::Window* aClientWindow);
	void Update(const sf::Event& aWindowsMessage);
	void UpdateKeys(const sf::Event& aWindowsMessage);
	void UpdateMouse(const sf::Event& aWindowsMessage);
	void OncePerFrameUpdate();

	bool IsKeyPressed(EKeyCode aKey);
	bool IsKeyDown(EKeyCode aKey);
	bool IsKeyReleased(EKeyCode aKey);

	int GetScrollWheelDelta();
	sf::Vector2f GetMousePosFloat();
	sf::Vector2i GetMousePosInt();

private:
	CInputManager();

	std::map<EKeyCode, EKeyState> myKeyStates;
	std::map<EKeyCode, EKeyState> myPreviousKeyStates;

	std::map<EKeyCode, EKeyState> myMouseButtonStates;
	std::map<EKeyCode, EKeyState> myPreviousMouseButtonStates;

	float myWheelDelta;

	sf::Window* myHWND;
};

