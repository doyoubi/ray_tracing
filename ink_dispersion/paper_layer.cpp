#include<iostream>
#include<numeric>
using std::cout;
using std::cin;
using std::endl;

#include"paper_layer.h"
#include"formula.h"

//#include"screen_manager.h"
//using _screen_manager::ScreenManager;
//extern ScreenManager screen;

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

    const Vector_2d<double> Lattice::u()const
    {
        Vector_2d<double> u(0, 0);
        for(int i = 0; i < 9; i++)
            u += f[i] * next_position[i];
        return u / rho();
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
            // 0.001 may not be appropriate
            if(curr_lattice.rho() < 0.0001) continue;
            // stream to 9 direction
            double result[9] = {0};
            for(int i = 0; i < 9; i++)
            {
                Point_2d<int> next_point = p + Lattice::next_position[i];
                if(!is_valid_position(next_point)) continue;
                if(!has_water(next_point)) 
                {
                    lattice_position_list.push_back(next_point);
                    has_water_table[next_point] = true;
                }
                double f_i_next = fi_next(i, curr_lattice);

                if(f_i_next < 0) cout<< f_i_next <<endl;

                if(0.0001 < f_i_next && f_i_next < curr_lattice.rho())
                    result[i] = f_i_next;
            }
            for(int i = 0; i < 9; i++)
            {
                Point_2d<int> next_point = p + Lattice::next_position[i];
                if(!is_valid_position(next_point)) continue;
                Lattice & next_lattice = (*this)[next_point];
                next_lattice.f[i] = result[i];
                curr_lattice.f[i] -= result[i];
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
