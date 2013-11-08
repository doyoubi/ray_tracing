#include<iostream>
using std::cout;
using std::cin;
using std::endl;
#include<gl/glut.h>

#include"../2d/2d.h"
using _2d::RGB;

namespace screen_manager
{

    class ScreenManager
    {
        public:
            static const int window_width = 7;
            static const int window_height = 5;

            ScreenManager();
            GLubyte (* generate_screem_image(void) )[window_height][3];
            void set_draw_square(int left_bottom_x, int left_bottom_y, int width, int height);
            void draw(int x, int y, RGB rgb);
            GLubyte (*operator[](int width))[window_height][3];
        private:
            GLubyte screen[window_width][window_height][3];
            int left_bottom_x_of_draw_square, left_bottom_y_of_draw_square;
            int width_of_draw_square, height_of_draw_square;
    };

    ScreenManager::ScreenManager()
    {
        for(int x = 0; x < window_width; x++)
            for(int y = 0; y < window_height; y++)
                for(int i = 0; i < 3; i++)
                    screen[x][y][i] = 0xff;
        left_bottom_x_of_draw_square = 0;
        left_bottom_y_of_draw_square = 0;
        width_of_draw_square = 0;
        height_of_draw_square = 0;
    }

    GLubyte (*ScreenManager::generate_screem_image(void))[ScreenManager::window_height][3]
    { return screen; }

    void ScreenManager::set_draw_square(int left_bottom_x, int left_bottom_y, int width, int height)
    {
        if(left_bottom_x < 0 || left_bottom_y < 0 || width < 0 || height < 0)
            return;
        left_bottom_x_of_draw_square = left_bottom_x;
        left_bottom_y_of_draw_square = left_bottom_y;
        width_of_draw_square = width;
        height_of_draw_square = height;
    }

    void ScreenManager::draw(int x, int y, RGB rgb)
    {
        if(x < 0 || y < 0 || x >= window_width || y >= window_height)
            return;
        screen[left_bottom_x_of_draw_square + x][left_bottom_y_of_draw_square + y][0] = rgb.r;
        screen[left_bottom_x_of_draw_square + x][left_bottom_y_of_draw_square + y][1] = rgb.g;
        screen[left_bottom_x_of_draw_square + x][left_bottom_y_of_draw_square + y][2] = rgb.b;
    }

    GLubyte (*ScreenManager::operator[](int width))[ScreenManager::window_height][3]
    { return screen; }
}
