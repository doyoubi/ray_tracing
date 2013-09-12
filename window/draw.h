#ifndef DRAW_H
#define DRAW_H

#include<windows.h>


extern const int WNDWIDTH;
extern const int WNDHEIGHT;

#include"../2d/2d.h"
using _2d::Point_2d;
using _2d::ARGB;
using _2d::Image;
#include"direct3D.h"
extern _direct3D::Direct3D d3d;

namespace _draw{

    int draw_point(int x, int y, ARGB argb);
    int draw_point(int x, int y, ARGB argb);
	void draw_image(int start_x, int start_y, const Image<ARGB> & image);

    inline DWORD ARGB_to_DWORD(const ARGB & color)
    {
        return ((DWORD)(color.a) << 24 )
             + ((DWORD)(color.r) << 16 )
             + ((DWORD)(color.g) << 8 )
             + ((DWORD)(color.b) << 0) ;
    }
    
    inline int draw_point(int x, int y, ARGB color)
    {
        if(x < 0 || x >= WNDWIDTH || y < 0 || y >= WNDHEIGHT)
            return 1;
        d3d.DrawPixel(x, y, ARGB_to_DWORD(color));
        return 0;
    }
}

#endif