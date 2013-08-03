#ifndef DRAW_H
#define DRAW_H

#include"2d.h"
using _2d::Point_2d;
using _2d::ARGB;
using _2d::Picture;

namespace _draw{

void draw_point(int x, int y, ARGB argb);
void draw_line(Point_2d start, Point_2d end, ARGB argb);
void draw_picture(Point_2d startpoint, Picture picure );

}

#endif