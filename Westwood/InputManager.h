#pragma once
#include "KeyCodes.h"
#include <map>
#include <windows.h>

class CInputManager
{
public:
	~CInputManager();

	static CInputManager& GetInstance();

	void Init(HWND aClientWindow);
	void Update(const MSG& aWindowsMessage);
	void UpdateKeys(const MSG& aWindowsMessage);
	void UpdateMouse(const MSG& aWindowsMessage);
	void OncePerFrameUpdate();

	bool IsKeyPressed(EKeyCode aKey);
	bool IsKeyDown(EKeyCode aKey);

	int GetScrollWheelDelta();

private:
	CInputManager();

	std::map<EKeyCode, EKeyState> myKeyStates;
	std::map<EKeyCode, EKeyState> myPreviousKeyStates;

	float myWheelDelta;

	HWND myHWND;
};

