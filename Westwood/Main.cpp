#ifdef _DEBUG
#pragma comment (lib, "sfml-system-d")
#pragma comment (lib, "sfml-window-d")
#pragma comment (lib, "sfml-graphics-d")
#else
#pragma comment (lib, "sfml-system")
#pragma comment (lib, "sfml-window")
#pragma comment (lib, "sfml-graphics")
#endif

#include <windows.h>
#include "Game.h"
#include "InputManager.h"

int WINAPI wWinMain(_In_ HINSTANCE hIntance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nShowCmd)
{
	CGame game;

	game.Initialize();

	MSG windowsMessage = {};

	while (game.ShouldRun())
	{
		CInputManager::GetInstance().OncePerFrameUpdate();

		while (PeekMessage(&windowsMessage, 0, 0, 0, PM_REMOVE))
		{
			CInputManager::GetInstance().Update(windowsMessage);

			TranslateMessage(&windowsMessage);
			DispatchMessage(&windowsMessage);
		}

		game.Update();
	}

	return 0;
}