#ifdef _DEBUG
#pragma comment (lib, "sfml-system-d")
#pragma comment (lib, "sfml-window-d")
#pragma comment (lib, "sfml-graphics-d")
#pragma comment (lib, "sfml-audio-d")
#else
#pragma comment (lib, "sfml-system")
#pragma comment (lib, "sfml-window")
#pragma comment (lib, "sfml-graphics")
#pragma comment (lib, "sfml-audio")
#endif


#include "Game.h"
#include "InputManager.h"

int main()
{
	CGame game;

	game.Initialize();

	while (game.ShouldRun())
	{
		CInputManager::GetInstance().OncePerFrameUpdate();

		game.Update();
	}

	return 0;
}