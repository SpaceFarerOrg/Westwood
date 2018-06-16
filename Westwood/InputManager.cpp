#include "InputManager.h"
#include "SFML\Window\Mouse.hpp"
#include "SFML\Window.hpp"

CInputManager::CInputManager()
{
}


CInputManager::~CInputManager()
{
}

CInputManager & CInputManager::GetInstance()
{
	static CInputManager instance;

	return instance;
}

void CInputManager::Init(HWND aClientWindow)
{
	myHWND = aClientWindow;
	CreateKeyStates(myKeyStates);
	myPreviousKeyStates = myKeyStates;
}

void CInputManager::Update(const MSG& aWindowsMessage)
{
	UpdateKeys(aWindowsMessage);
	UpdateMouse(aWindowsMessage);
}

void CInputManager::UpdateKeys(const MSG & aWindowsMessage)
{
	switch (aWindowsMessage.message)
	{
	case WM_KEYDOWN:
	{
		EKeyCode key = static_cast<EKeyCode>(aWindowsMessage.wParam);

		if (myKeyStates.find(key) != myKeyStates.end())
		{
			myKeyStates[key] = EKeyState::Down;
		}

		break;
	}
	case WM_KEYUP:
	{
		EKeyCode key = static_cast<EKeyCode>(aWindowsMessage.wParam);

		if (myKeyStates.find(key) != myKeyStates.end())
		{
			myKeyStates[key] = EKeyState::Up;
		}

		break;
	}
	case WM_LBUTTONDOWN:
	{
		EKeyCode key = EKeyCode::MouseLeft;

		myKeyStates[key] = EKeyState::Down;

		break;
	}
	case WM_LBUTTONUP:
	{
		EKeyCode key = EKeyCode::MouseLeft;

		myKeyStates[key] = EKeyState::Up;

		break;
	}
	case WM_MBUTTONDOWN:
	{
		EKeyCode key = EKeyCode::MouseMiddle;

		myKeyStates[key] = EKeyState::Down;

		break;
	}
	case WM_MBUTTONUP:
	{
		EKeyCode key = EKeyCode::MouseMiddle;

		myKeyStates[key] = EKeyState::Up;

		break;
	}
	case WM_RBUTTONDOWN:
	{
		EKeyCode key = EKeyCode::MouseRight;

		myKeyStates[key] = EKeyState::Down;

		break;
	}
	case WM_RBUTTONUP:
	{
		EKeyCode key = EKeyCode::MouseRight;

		myKeyStates[key] = EKeyState::Up;

		break;
	}
	}
}

void CInputManager::UpdateMouse(const MSG & aWindowsMessage)
{
	if (aWindowsMessage.message == WM_MOUSEWHEEL)
	{
		myWheelDelta = static_cast<float>(GET_WHEEL_DELTA_WPARAM(aWindowsMessage.wParam)) / static_cast<float>(WHEEL_DELTA);
	}
}

void CInputManager::OncePerFrameUpdate()
{
	myPreviousKeyStates = myKeyStates;
	myWheelDelta = 0.0f;
}

bool CInputManager::IsKeyPressed(EKeyCode aKey)
{
	return myKeyStates[aKey] == EKeyState::Down && myPreviousKeyStates[aKey] == EKeyState::Up;
}

bool CInputManager::IsKeyDown(EKeyCode aKey)
{
	return myKeyStates[aKey] == EKeyState::Down;
}

int CInputManager::GetScrollWheelDelta()
{
	return myWheelDelta;
}

sf::Vector2f CInputManager::GetMousePosFloat()
{
	sf::Vector2i mPos = sf::Mouse::getPosition(sf::Window(myHWND));
	return sf::Vector2f(mPos.x, mPos.y);
}

sf::Vector2i CInputManager::GetMousePosInt()
{
	return sf::Mouse::getPosition(sf::Window(myHWND));
}
