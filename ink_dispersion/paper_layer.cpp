#include<iostream>
#include<numeric>
using std::cout;
using std::cin;
using std::endl;

#include"paper_layer.h"

//#include"screen_manager.h"
//using _screen_manager::ScreenManager;
//extern ScreenManager screen;

namespace _paper_layer
{

/* -------------------------------------------------------------
 *       Lattice Boltzmann Equation Approach
 *
 *   fi(x + ei*deltaT, t + deltaT) = (1-omega) * fi(x, t)  +  omega * f(eq)i (x, t)
 *   f(eq)i (x, y) = wi( rho + (3*ei*u + 9/2 * (ei*u)^2 - 3/2(u*u) ) )
 *                    rho = f0 + f1 + ... + f8
 *            u = e0 * f0 + e1 * f1 + ... + e8 * f8
 *
 * -------------------------------------------------------------*/

    double fi_next(int direction, Lattice current_lattice);
    double f_eq(int direction, Lattice current_lattice);
    const double w[9] = {4/9, 1/9, 1/9, 1/9, 1/9, 1/36, 1/36, 1/36, 1/36};
    const double omega = 0.5; // relaxation parameter
    const double rho_0 = 1.0;

    double fi_next(int i, Lattice current_lattice)
    {
        return (1 - omega) * current_lattice.f[i] + omega * f_eq(i, current_lattice);
    }
    double f_eq(int i, Lattice current_lattice)
    {
        const Vector_2d<double> ei = Lattice::next_position[i];
        const Vector_2d<double> u = current_lattice.u();
        return w[i]*
        (
            current_lattice.rho() + rho_0 * 
            ( 3*ei*u + 9.0/2*(ei*u)*(ei*u) - 3.0/2*(u*u))
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

    const Vector_2d<double> Lattice::u()const
    {
        Vector_2d<double> u(0, 0);
        for(int i = 0; i < 9; i++)
        {
            u += f[i] * next_position[i];
            Vector_2d<double> v = f[i] * next_position[i];
            cout<< v.x << v.y <<endl;
        }
        return u;
    }
    double Lattice::rho()const
    {
        return std::accumulate(f, f+9, 0.0);
    }

    
    // class FlowLayer
    FlowLayer::FlowLayer(int width, int height)
        :array_2d<Lattice>(width, height), has_water_table(width, height)
    {
        for(int x = 0; x < width; x++)
            for(int y = 0; y < height; y++)
                has_water_table[x][y] = false;
    }

    void FlowLayer::stream()
    {
        auto end = lattice_position_list.end();
        for(auto it = lattice_position_list.begin(); it != end; it++)
        {
            Point_2d<int> p = *it;
            Lattice & curr_lattice = (*this)[p];
            // 0.1 may not be appropriate
            if(curr_lattice.rho() < 0.001) continue;
            // stream to 9 direction
            for(int i = 0; i < 9; i++)
            {
                Point_2d<int> next_point = p + Lattice::next_position[i];
                if(is_valid_position(next_point))
                {
                    if(!has_water(next_point)) 
                    {
                        lattice_position_list.push_back(next_point);
                        has_water_table[next_point] = true;
                    }
                    Lattice & next_lattice = (*this)[next_point];
                    double f_i_next = fi_next(i, curr_lattice);
                    if(0.001 < f_i_next && f_i_next < curr_lattice.f[i])
                    {
                        next_lattice.f[i] = f_i_next;
                        curr_lattice.f[i] -= f_i_next;
                    }
                }
            }
        }
    }

    bool FlowLayer::has_water(Point_2d<int> p)
    { return has_water_table[p.x][p.y]; }

    //void FlowLayer::draw()
    //{
    //    for(vector< Point_2d<int> >::iterator it = lattice_position_list.begin();
    //            it != lattice_position_list.end(); it++)
    //    {
    //        Point_2d<int> p = *it;
    //        RGB rgb;
    //        rgb.r = rgb.g = rgb.b = 0xff - 0xff * (*this)[p].rho;
    //        screen.draw(p.x, p.y, rgb);
    //    }
    //}

    void FlowLayer::add_water(const Lattice & l, Point_2d<int> position)
    {
        (*this)[position] = l;
        lattice_position_list.push_back(position);
        has_water_table[position] = true;
    }

}
