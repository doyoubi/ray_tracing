#ifndef GAMEMAIN
#define GAMEMAIN

#include <windows.h>

namespace _gamemain
{
	int GameMain();
	int Game_Shutdown();
	int Game_Init(HWND hwnd,int width,int height);
}

#endif
