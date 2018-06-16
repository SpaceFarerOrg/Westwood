#ifdef _DEBUG
#pragma comment (lib, "sfml-system-d")
#pragma comment (lib, "sfml-window-d")
#pragma comment (lib, "sfml-graphics-d")
#else
#pragma comment (lib, "sfml-system")
#pragma comment (lib, "sfml-window")
#pragma comment (lib, "sfml-graphics")
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