#include<iostream>
#include<numeric>
#include<algorithm>
#include<random>
using std::cout;
using std::cin;
using std::endl;

#include"paper_layer.h"
#include"formula.h"

#include"screen_manager.h"
using _screen_manager::ScreenManager;
extern ScreenManager screen;

namespace _paper_layer
{
// class Lattice

/* 6 2 5
 * 3 0 1
 * 7 4 8 */
const Point_2d<int> Lattice::next_position[9] = {
    Point_2d<int>(0,0),  Point_2d<int>(1,0),   Point_2d<int>(0,1),
    Point_2d<int>(-1,0), Point_2d<int>(0,-1),  Point_2d<int>(1,1),
    Point_2d<int>(-1,1), Point_2d<int>(-1,-1), Point_2d<int>(1,-1)
};

const int opposite_direction[9] = {0,3,4,1,2, 7,8,5,6};

double Lattice::rho()const
{
    return std::accumulate(f, f+9, 0.0);
}

const Vector_2d<double> Lattice::u()const
{
    Vector_2d<double> u(0, 0);
    for(int i = 0; i < 9; i++)
        u += f[i] * next_position[i];
    return u;
}

// class FlowLayer
FlowLayer::FlowLayer(int width, int height)
    :state1(width, height), state2(width, height)
{
    curr_state = &state1;
    last_state = &state2;
}

void FlowLayer::stream()
{
    std::swap(state1, state2);
    for(int y = 1; y < state1.get_height()-1; y++)
        for(int x = 1; x < state1.get_width()-1; x++)
        {
            for(int i = 0; i < 9; i++)
                (*curr_state)[x][y].f[i] =
                    fi_next(i, (*last_state)[x][y]);
        }
    std::swap(state1, state2);
    for(int y = 1; y < state1.get_height()-1; y++)
        for(int x = 1; x < state1.get_width()-1; x++)
        {
            double theshold = 0.1 + 0.1 * texture.alum[x][y];
            double k = 1;
            double sqrt_2 = 1.41421356237;
            for(int i = 1; i < 5; i++)
            if((*last_state)[Point_2d<int>(x,y) - Lattice::next_position[i]].rho() > theshold)
            {
                k = 0;
                break;
            }
            for(int i = 5; i < 9; i++)
            if((*last_state)[Point_2d<int>(x,y) - Lattice::next_position[i]].rho() > sqrt_2 * theshold)
            {
                k = 0;
                break;
            }

            for(int i = 0; i < 9; i++)
            {
                if(k != 1)
                {
                    k = (texture.alum[Point_2d<int>(x,y)-Lattice::next_position[i]]
                          + texture.alum[Point_2d<int>(x,y)]) * 0.1 / 2; 
                }
                (*curr_state)[x][y].f[i] =
                    (1-k) * (*last_state)[Point_2d<int>(x,y) - Lattice::next_position[i]].f[i]
                      + k * (*last_state)[x][y].f[opposite_direction[i]];
            }
        }
}

void FlowLayer::add_water(double seep, Point_2d<int> position)
{
    (*(this->curr_state))[position].f[0] += seep;
}

void FlowLayer::draw()
{
    for(int y = 0; y < state1.get_height(); y++)
    for(int x = 0; x < state1.get_width(); x++)
    {
        Lattice &lattice = (*curr_state)[x][y];
        RGB rgb;
        rgb.r = rgb.g = rgb.b = 0xff *(1 - lattice.rho());
        screen.draw(x, y, rgb);
    }
}

Texture::Texture() : alum(100, 100)
{
    std::random_device rd;
    std::mt19937 eng(rd());
    std::uniform_real_distribution<> dist(0,1);
    std::generate(alum.begin(), alum.end(), [&]{return dist(eng);});
}

}
