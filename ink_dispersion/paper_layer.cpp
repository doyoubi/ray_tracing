#include<iostream>
using std::cout;
using std::cin;
using std::endl;

#include"paper_layer.h"

#include"screen_manager.h"
using _screen_manager::ScreenManager;
extern ScreenManager screen;

namespace paper_layer
{

/* -------------------------------------------------------------
 *       Lattice Boltzmann Equation Approach
 *
 *   fi(x + ei*deltaT, t + deltaT) = (1-omega) * fi(x, t)  +  omega * f(eq)i (x, t)
 *   f(eq)i(x, y) = wi( rho + (3*ei*u + 9/2 * (ei*u)^2 - 3/2(u*u) ) )
 *                    rho = f0 + f1 + ... + f8
 *            u = e0 * f0 + e1 * f1 + ... + e8 * f8
 *
 * -------------------------------------------------------------*/

    double fi_next(int direction, Lattice current_lattice);
    double f_eq(int direction, Lattice current_lattice);
    const double w[9] = {4/9, 1/9, 1/9, 1/9, 1/9, 1/36, 1/36, 1/36, 1/36};
    const double omega = 0.3; // relaxation parameter
    const double rho_0 = 1.0;

    double fi_next(int i, Lattice current_lattice)
    {
        return omega * current_lattice.f[i] + (1-omega) * f_eq(i, current_lattice);
    }
    double f_eq(int i, Lattice current_lattice)
    {
        Vector_2d<double> ei = Lattice::next_position[i];
        Vector_2d<double> u = current_lattice.u;
        return w[i]*
        (
            current_lattice.rho + rho_0 * 
            ( 3*ei*u + 9/2*(ei*u)*(ei*u) - 3/2*(u*u))
        );
    }
    

    // class Lattice

    /* 6 2 5
     * 3 0 1
     * 7 4 8 */
    const Point_2d<int> Lattice::next_position[9] = {
        Point_2d<int>(0,0),  Point_2d<int>(1,0),   Point_2d<int>(0,1),
        Point_2d<int>(-1,0), Point_2d<int>(0,-1),  Point_2d<int>(1,1),
        Point_2d<int>(-1,1), Point_2d<int>(-1,-1), Point_2d<int>(1,-1)
    };

    
    // class FlowLayer
    FlowLayer::FlowLayer(int width, int height):Image<Lattice>(width, height)
    {
        has_water_table = Image<bool>(width, height);
        for(int x = 0; x < width; x++)
            for(int y = 0; y < height; y++)
                has_water_table[x][y] = false;
    }

    void FlowLayer::stream()
    {
        vector< Point_2d<int> >::iterator end = lattice_position_list.end();
        for(vector< Point_2d<int> >::iterator it = lattice_position_list.begin();
                it != end; it++)
        {
            Point_2d<int> p = *it;
            // stream to 9 direction
            for(int i = 0; i < 9; i++)
            {
                Point_2d<int> next_point = p + Lattice::next_position[i];
                Lattice curr_lattice = (*this)[p];
                if(is_valid_position(next_point))
                {
                    if(!has_water(next_point)) 
                        lattice_position_list.push_back(next_point);
                    Lattice & next_lattice = (*this)[next_point];
                    next_lattice.f[i] = fi_next(i, curr_lattice);
                    next_lattice.rho += next_lattice.f[i];
                    next_lattice.u += next_point * next_lattice.f[i];
                }
            }
        }
    }

    bool FlowLayer::has_water(Point_2d<int> p)
    { return has_water_table[p.x][p.y]; }

    void FlowLayer::draw()
    {
        for(vector< Point_2d<int> >::iterator it = lattice_position_list.begin();
                it != lattice_position_list.end(); it++)
        {
            Point_2d<int> p = *it;
            RGB rgb;
            rgb.r = rgb.g = rgb.b = 0xff * (*this)[p].rho;
            screen.draw(p.x, p.y, rgb);
        }
    }

}
