#include "gamemain.h"
#include "direct3D.h"
#include "flush.h"
using namespace _flush;

#include <windows.h>

extern _direct3D::Direct3D d3d;

namespace _gamemain{
	
	const int WAIT_TIME = 30;
	DWORD g_clock;

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

	//游戏循环的主函数
	int GameMain()
	{
		// 计时
		StartClock();
		
		// 表面加锁
		d3d.LockSurface();
		
		// 画图
		flushscreen();
		
		// 表面解锁
		d3d.UnlockSurface();
		
		// 输出
		d3d.FlipSurface();
		
		// 锁帧
		WaitClock();
		return 1;
	}
	
	
}

