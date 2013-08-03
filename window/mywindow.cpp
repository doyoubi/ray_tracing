#include <windows.h>

#include "gamemain.h"
using namespace _gamemain;

const int WNDWIDTH = 640 ;
const int WNDHEIGHT = 480 ;

//消息处理函数
LRESULT CALLBACK myWndProc(HWND,UINT,WPARAM,LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd )
{
  //注册窗口类
	WNDCLASS mywndclass;
	mywndclass.cbClsExtra=0;
	mywndclass.cbWndExtra=0;
	mywndclass.hbrBackground=(HBRUSH)GetStockObject(WHITE_BRUSH);
	mywndclass.hCursor=LoadCursor(NULL,IDC_ARROW);
	mywndclass.hIcon=LoadIcon(NULL,IDI_APPLICATION);
	mywndclass.hInstance=hInstance;
	mywndclass.lpfnWndProc=myWndProc;
	mywndclass.lpszClassName="mywindow";
	mywndclass.lpszMenuName=NULL;
	mywndclass.style=CS_HREDRAW|CS_VREDRAW;
	if(!RegisterClass(&mywndclass))
		return 0;
	
	//创建窗口
	HWND hwnd;
	hwnd=CreateWindow("mywindow",
		NULL,
		WS_OVERLAPPEDWINDOW&(~WS_THICKFRAME),
		200,200,WNDWIDTH,WNDHEIGHT,
		NULL,
		NULL,
		hInstance,
		NULL
		);

	//D3D:初始化direct3d
	Game_Init(hwnd,WNDWIDTH,WNDHEIGHT);
	
	//显示窗口，更新窗口
	ShowWindow(hwnd,SW_SHOWNORMAL);
	UpdateWindow(hwnd);
	
	//消息循环
	MSG msg;
	ZeroMemory(&msg,sizeof(msg));
	while (msg.message!=WM_QUIT)
	{
		if(PeekMessage(&msg,NULL,0,0,PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		GameMain();
	}
	//释放D3D
	Game_Shutdown();

	UnregisterClass("mymsg",mywndclass.hInstance);
	return 0;
}

LRESULT CALLBACK myWndProc(HWND hwnd,UINT msg,WPARAM wparam,LPARAM lparam)
{
	switch (msg)
	{
	case WM_PAINT:
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hwnd,msg,wparam,lparam);
}
