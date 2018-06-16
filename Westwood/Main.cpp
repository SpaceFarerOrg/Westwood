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
#include <stdio.h>
#include <io.h>
#include <fcntl.h>

int WINAPI wWinMain(_In_ HINSTANCE hIntance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nShowCmd)
{
	AllocConsole();

	HANDLE handle_out = GetStdHandle(STD_OUTPUT_HANDLE);
	int hCrt = _open_osfhandle((long)handle_out, _O_TEXT);
	FILE* hf_out = _fdopen(hCrt, "w");
	setvbuf(hf_out, NULL, _IONBF, 1);
	*stdout = *hf_out;

	HANDLE handle_in = GetStdHandle(STD_INPUT_HANDLE);
	hCrt = _open_osfhandle((long)handle_in, _O_TEXT);
	FILE* hf_in = _fdopen(hCrt, "r");
	setvbuf(hf_in, NULL, _IONBF, 128);
	*stdin = *hf_in;

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