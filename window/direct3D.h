#ifndef DIRECT3D_H
#define DIRECT3D_H

#include <d3d9.h>
#include <d3dx9.h>

namespace _direct3D
{	
    inline void DrawPixel(int x, int y, DWORD color); //没有检查出界

class Direct3D
{
public:
    HRESULT initDirect3D(HWND hwnd,int width,int height); //初始化direct3d
    ~Direct3D(); //清理direct3d

    int LockSurface();
    int UnlockSurface();
    void FlipSurface();

    inline void DrawPixel(int x,int y, DWORD color);

private:
    LPDIRECT3DDEVICE9 g_pd3dDevice; //direct3d设备接口
    LPDIRECT3DSURFACE9 g_pd3dSurface;
    D3DLOCKED_RECT lockedRect;
    int wnd_width, wnd_height;
};

inline void Direct3D::DrawPixel(int x,int y, DWORD color)
{   
    DWORD* pBits = (DWORD*)lockedRect.pBits;
    pBits[x + y * (lockedRect.Pitch >> 2)] = color;
}  

	

}

#endif
