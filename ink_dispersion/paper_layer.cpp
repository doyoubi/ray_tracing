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
    const double w = 0.3; // relaxation parameter

    // class Lattice

    /* 6 2 5
     * 3 0 1
     * 7 4 8 */
    static const Point_2d Lattice::next_position[9] = {
        Point_2d(0,0),  Point_2d(1,0),   Point_2d(0,1),
        Point_2d(-1,0), Point_2d(0,-1),  Point_2d(1,1),
        Point_2d(-1,1), Point_2d(-1,-1), Point_2d(1,-1)
    };

    void Lattice::stream_fi_to_next_lattice(int direction)
    {
    }
    
    // class FlowLayer
    FlowLayer::FlowLayer(int width, int height):Image<Lattice>(width, height)
    {}

    void FlowLayer::stream()
    {
        for(vector<Point_2d>::iterator it = lattice_position_list.begin();
                it != lattice_position_list.end(); it++)
        {
            Point_2d p = *it;
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
