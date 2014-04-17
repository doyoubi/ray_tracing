#include<iostream>
#include<numeric>
#include<algorithm>
#include<random>
using std::cout;
using std::cin;
using std::endl;

#include"paper_layer.h"
#include"utils.h"

#include"screen_manager.h"

/* -------------------------------------------------------------
 *       Lattice Boltzmann Equation Approach
 *
 *   fi(x + ei*deltaT, t + deltaT) = (1-omega) * fi(x, t)  +  omega * f(eq)i (x, t)
 *   f(eq)i (x, y) = wi( rho + (3*ei*u + 9/2 * (ei*u)^2 - 3/2(u*u) ) )
 *                    rho = f0 + f1 + ... + f8
 *            u = e0 * f0 + e1 * f1 + ... + e8 * f8
 *
 * -------------------------------------------------------------*/

namespace _paper_layer
{

Point_2d<int> e[9] = {
    Point_2d<int>(0,0),  Point_2d<int>(1,0),   Point_2d<int>(0,1),
    Point_2d<int>(-1,0), Point_2d<int>(0,-1),  Point_2d<int>(1,1),
    Point_2d<int>(-1,1), Point_2d<int>(-1,-1), Point_2d<int>(1,-1)
};
const int opposite[9] = {0,3,4,1,2, 7,8,5,6};
const double weight[9] = {4.0/9,
                     1.0/9, 1.0/9, 1.0/9, 1.0/9,
                     1.0/36, 1.0/36, 1.0/36, 1.0/36};
const double omega = 0.5; // relaxation parameter
const double rho_0 = 1.0;

// lattice
/* 6 2 5
 * 3 0 1
 * 7 4 8 */


// class FlowLayer
FlowLayer::FlowLayer(int width, int height)
    : w(width, height), curr(width, height),
    temp(width, height), u(width, height)
{
    std::fill(w.begin(), w.end(), 0.0);
    FlowLayer::F zero;
    std::fill(zero.f, zero.f+9, 0.0);
    std::fill(curr.begin(), curr.end(), zero);
    std::fill(temp.begin(), temp.end(), zero);
    std::fill(u.begin(), u.end(), Point_2d<double>(0,0));
}

void FlowLayer::stream()
{
    for(int y = 0; y < w.get_height(); y++)
        for(int x = 0; x < w.get_width(); x++)
            for(int i = 0; i < 9; i++)
            {
                double feq, eiu, uu;
                double a = u[x][y].x, b = u[x][y].y;
                uu = a*a + b*b;
                eiu = e[i] * u[x][y];
                double psi = utils::smoothstep(0.0, 0.2, w[x][y]);
                feq = weight[i] * (w[x][y] + rho_0 * psi * ( 3*eiu + 9.0/2*eiu*eiu - 3.0/2*uu));
                temp[x][y].f[i] = utils::lerp(curr[x][y].f[i], feq, omega);
            }
    for(int y = 1; y < w.get_height()-1; y++)
        for(int x = 1; x < w.get_width()-1; x++)
            for(int i = 0; i < 9; i++)
                curr[x][y].f[i] = temp[Point_2d<int>(x,y) - e[i]].f[i];
    update_w();
    update_u();
}

void FlowLayer::update_w()
{
    for(int y = 0; y < w.get_height(); y++)
        for(int x = 0; x < w.get_width(); x++)
            w[x][y] = std::accumulate(curr[x][y].f, curr[x][y].f+9, 0.0);
}

void FlowLayer::update_u()
{
    for(int y = 0; y < u.get_height(); y++)
        for(int x = 0; x < u.get_width(); x++)
        {
            u[x][y].x = u[x][y].y = 0.0;
            for(int i = 0; i < 9; i++)
                u[x][y] += e[i] * curr[x][y].f[i];
        }
}

SurfaceLayer::SurfaceLayer(int width, int height) 
    : w(width, height)
{
    std::fill(w.begin(), w.end(), 0.0);
}

void SurfaceLayer::seep(FlowLayer & flowlayer)
{
    for(int y = 0; y < w.get_height(); y++)
    {
        for(int x = 0; x < w.get_width(); x++)
        {
            double phi = utils::clamp(w[x][y], 0, 1-flowlayer.w[x][y]);
            w[x][y] = std::max(w[x][y]-phi, 0.0);
            flowlayer.w[x][y] += phi;
            flowlayer.curr[x][y].f[0] += phi;
        }
    }
    flowlayer.update_u();
}


}
