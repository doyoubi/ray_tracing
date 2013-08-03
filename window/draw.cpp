#include"draw.h"
#include"direct3D.h"
using _direct3D::drawpixel;

namespace _draw{
    
    inline int DrawPoint(int x, int y, DWORD color)
    {
        extern D3DLOCKED_RECT lockedRect;
        //检查所画的点有没有越界
        if(x>=WNDWIDTH || y>=WNDHEIGHT)
            return 0;
        
        DWORD* pBits=(DWORD*)lockedRect.pBits;
        pBits[x + y * (lockedRect.Pitch >> 2)] = color;
//      byte alpha=(color&0xff000000)>>24;
//      DWORD backgroundColor=pBits[x + y * (lockedRect.Pitch >> 2)]&0x00ffffff;
//      color=color&0x00ffffff;
//      color=( ( color*alpha )>>8 )+( ( backgroundColor*(0xff-alpha) )>>8 );
//      color=color|(alpha<<24);
//      pBits[x + y * (lockedRect.Pitch >> 2)] = color;
        return 1;
    }
    
    int DrawLine(int x0, int y0, int x1, int y1, DWORD color)  
    {  
        int x, y, dx, dy, dx2, dy2, xstep, ystep, error, index;  
        x = x0;  
        y = y0;  
        dx = x1 - x0;  
        dy = y1 - y0;  
        
        if (dx >= 0) // 从左往右画  
        {  
            xstep = 1; // x步进正1  
        }  
        else // 从右往左画  
        {  
            xstep = -1; // x步进负1  
            dx = -dx; // 取绝对值  
        }  
        
        if (dy >= 0) // 从上往下画  
        {  
            ystep = 1; // y步进正1  
        }  
        else // 从下往上画  
        {  
            ystep = -1; // y步进负1  
            dy = -dy; // 取绝对值  
        }  
        
        dx2 = dx << 1; // 2 * dx  
        dy2 = dy << 1; // 2 * dy  
        
        if (dx > dy) // 近X轴直线  
        {  
            error = dy2 - dx;  
            for (index = 0; index <= dx; ++index)  
            {  
                DrawPoint(x, y, color);  
                if (error >= 0)  
                {  
                    error -= dx2;  
                    y += ystep;  
                }  
                error += dy2;  
                x += xstep;  
            }  
        }  
        else // 近Y轴直线  
        {  
            error = dx2 - dy;  
            for (index = 0; index <= dy; ++index)  
            {  
                DrawPoint(x, y, color);  
                if (error >= 0)  
                {  
                    error -= dy2;  
                    x += xstep;  
                }  
                error += dx2;  
                y += ystep;  
            }  
        }  
        
        return 1;  
    }  
}