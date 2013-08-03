#ifndef DIRECT3D_H
#define DIRECT3D_H

#include <d3d9.h>
#include <d3dx9.h>

namespace _direct3D
{	
    inline void DrawPixel(int x, int y, DWORD color); //没有检查出界

	HRESULT InitDirect3D(HWND hwnd,int width,int height);//初始化direct3d
	void Direct3DCleanup();//清理direct3d

	int LockSurface();
	int UnlockSurface();
	void FlipSurface();    
	
	inline void DrawPixel(int x,int y, DWORD color)
    {
        extern D3DLOCKED_RECT lockedRect;
        
        DWORD* pBits = (DWORD*)lockedRect.pBits;
        pBits[x + y * (lockedRect.Pitch >> 2)] = color;
    }
}

#endif
