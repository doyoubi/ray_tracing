#include "flush.h"
#include <stdlib.h> //random function
#include "draw.h"
using _draw::draw_point;
using _draw::draw_image;
#include "direct3D.h"
#include"../2d/2d.h"
using _2d::ARGB;
#include"../bmp/bmp.h"
using _bmp::BmpImage;
BmpImage image("test.bmp");

namespace _flush{

	int flushscreen()
    {
        ARGB color;
        color.a = 255;
        color.r = 0;
        color.g = 0;
        color.b = 255;
		for(int i = 0; i < 50; ++i)
            draw_point(50, i, color);

		draw_image(0,0, image);
		return 0;
	}
	
}
