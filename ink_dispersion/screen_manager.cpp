#include"screen_manager.h"


namespace _screen_manager
{
    ScreenManager::ScreenManager()
    {
        for(int x = 0; x < window_width; x++)
            for(int y = 0; y < window_height; y++)
                for(int i = 0; i < 3; i++)
                    screen[y][x][i] = 0xff;
        left_bottom_x_of_draw_square = 0;
        left_bottom_y_of_draw_square = 0;
        width_of_draw_square = 0;
        height_of_draw_square = 0;
    }

    GLubyte (*ScreenManager::generate_screem_image(void))[ScreenManager::window_width][3]
    { return screen; }

    void ScreenManager::set_draw_square(int left_bottom_x, int left_bottom_y, int width, int height)
    {
        if(left_bottom_x < 0 || left_bottom_y < 0 || width < 0 || height < 0
        || left_bottom_x+width >= window_width || left_bottom_y+height>= window_height )
            throw "invalid square start point or size";
        left_bottom_x_of_draw_square = left_bottom_x;
        left_bottom_y_of_draw_square = left_bottom_y;
        width_of_draw_square = width;
        height_of_draw_square = height;
    }

    void ScreenManager::draw(int x, int y, RGB rgb)
    {
        if(x < 0 || x >= width_of_draw_square 
        || y < 0 || y >= height_of_draw_square)
            return;
        screen[left_bottom_y_of_draw_square + y][left_bottom_x_of_draw_square + x][0] = rgb.r;
        screen[left_bottom_y_of_draw_square + y][left_bottom_x_of_draw_square + x][1] = rgb.g;
        screen[left_bottom_y_of_draw_square + y][left_bottom_x_of_draw_square + x][2] = rgb.b;
    }

    const GLubyte (*ScreenManager::operator[](int width)const)[ScreenManager::window_width][3]
    { return screen; }

}
