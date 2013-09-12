#include"draw.h"


namespace _draw{
    
void draw_image(int start_x, int start_y, const Image<ARGB> & image)
{
    for(int y = 0; y < image.height; ++y)
        for(int x = 0; x < image.width; ++x)
            draw_point(start_x + x, start_y + y, image[x][y]);
}


}