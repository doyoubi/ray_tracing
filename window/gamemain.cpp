#include "gamemain.h"
#include "direct3D.h"
#include "flush.h"

//#define ARGB(a, r, g, b) ((b) + ((g) << 8) + ((r) << 16) + ((a) << 24))

//using namespace _direct3D;
using namespace _flush;


const int WAIT_TIME = 30;

namespace _gamemain{
	
	DWORD g_clock;
	
	int Game_Shutdown()
	{
		_direct3D::Direct3DCleanup();
		return 1;
	}
	DWORD GetClock()
	{
		return GetTickCount(); 
	}
	
	void StartClock()
	{
		g_clock = GetClock();
	}
	
	void WaitClock()
	{
		while((GetClock() - g_clock) < WAIT_TIME)
		{
			Sleep(5);
		}
	}
	
	int Game_Init(HWND hwnd,int width,int height)
	{
		_direct3D::InitDirect3D(hwnd,width,height);
		return 1;
	}

	//游戏循环的主函数
	int GameMain()
	{
		// 计时
		StartClock();
		
		// 表面加锁
		_direct3D::LockSurface();
		
		// 画图
		flushscreen();
		
		// 表面解锁
		_direct3D::UnlockSurface();
		
		// 输出
		_direct3D::FlipSurface();
		
		// 锁帧
		WaitClock();
		return 1;
	}
	
	
}

