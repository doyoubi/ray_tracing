#ifndef _SCREEN_MANAGER_H
#define _SCREEN_MANAGER_H

#include "settings.h"

#include "../GL/freeglut.h"
#include <iostream>
using std::cout;
using std::cin;
using std::endl;

#include "../2d/2d.h"
using _2d::RGB;

namespace _screen_manager
{

    class ScreenManager
    {
        public:
            static const int window_width = window_width; // global window_width, height
            static const int window_height = window_height;

            ScreenManager();
            typedef const GLubyte (*image)[window_width][3];
            image generate_screem_image()const;
            void set_draw_square(int left_bottom_x, int left_bottom_y, int width, int height);
            void draw(int x, int y, RGB rgb);
            const GLubyte (*operator[](int height)const)[3];
        private:
            GLubyte screen[window_height][window_width][3];
            int left_bottom_x_of_draw_square, left_bottom_y_of_draw_square;
            int width_of_draw_square, height_of_draw_square;
    };
}
#endif
