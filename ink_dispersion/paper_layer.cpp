#include<iostream>
using std::cout;
using std::cin;
using std::endl;

#include<paper_layer.h>

#include"screen_manager.h"
using screen_manager::ScreenManager;
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

    double fi(int direction, Lattice current_lattice);
    double f_eq(int direction, Lattice current_lattice);
    const double w[9] = {4/9, 1/9, 1/9, 1/9, 1/9, 1/36, 1/36, 1/36, 1/36};
    const double omega = 0.3; // relaxation parameter
    const double rho_0 = 1.0;

    // class Lattice

    /* 6 2 5
     * 3 0 1
     * 7 4 8 */
    static const Point_2d Lattice::next_position[9] = {
        Point_2d(0,0),  Point_2d(1,0),   Point_2d(0,1),
        Point_2d(-1,0), Point_2d(0,-1),  Point_2d(1,1),
        Point_2d(-1,1), Point_2d(-1,-1), Point_2d(1,-1)
    };

    double fi(int direction, Lattice current_lattice)
    {
        return current_lattice.f[direction] + f_eq(current_lattice);
    }
    double f_eq(int direction, Lattice current_lattice)
    {
        ei = Lattice::next_point[direction];
        return w[direction]*
        (
            current_lattice.rho + rho_0 * 
            ( 3*ei*current_lattice.u + 9/2*(ei*u)(ei*u) - 3/2*(u*u))
        );
    }
    
    // class FlowLayer
    FlowLayer::FlowLayer(int width, int height):Image<Lattice>(width, height) {}

    void FlowLayer::stream()
    {
        for(vector<Point_2d>::iterator it = lattice_position_list.begin();
                it != lattice_position_list.end(); it++)
        {
            Point_2d p = *it;
            // stream to 9 direction
            for(int i = 0; i < 9; i++)
            {
                Point_2d next_point = p + Lattice::next_position[i];
                Lattice curr_lattice = (*this)[p];
                if(is_valid_position(next_position))
                {
                    next_lattice = (*this)[next_position];
                    next_lattice.f[i] = omega*fi(i, current_lattice) + f_eq(i, current_lattice); 
                    next_lattice.rho += next_lattice.f[i];
                    next_lattice.u += next_position * next_lattice.f[i];
                }
            }
        }
    }

    void FlowLayer::draw()
    {
        for(vector<Point_2d>::iterator it = lattice_position_list.begin();
                it != lattice_position_list.end(); it++)
        {
            Point_2d p = *it;
            RGB rgb; rbg.r = rgb.g = rgb.b = 0xff * (*this)[p].rho;
            screen.draw(p.x, p.y, rgb);
        }
    }

}
