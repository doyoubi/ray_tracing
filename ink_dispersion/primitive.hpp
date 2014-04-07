#include<functional>
#include<iostream>
#include<cmath>
using std::function;

void draw_circle(const int r, function<void (int,int)> func)
{
    int x = 0; int y = r;
    double l = r / std::sqrt(2) + 1;
    while(x <= l)
    {
        func(x, y);
        func(y, x);
        func(x, -y);
        func(y, -x);
        //func(-x, y);
        //func(-y, x);
        //func(-x, -y);
        //func(-y, -x);
        if(x*x + y*y > r*r) y--;
        x++;
    }
}

