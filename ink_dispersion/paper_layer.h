#ifndef PAPER_LAYER
#define PAPER_LAYER

/* -------------------------------------------------------------
 *       Lattice Boltzmann Equation Approach
 *
 *   fi(x + ei*deltaT, t + deltaT) = (1-w) * fi(x, t)  +  w * f(eq)i (x, t)
 *                    rho = f0 + f1 + ... + f8
 *            u = e0 * f0 + e1 * f1 + ... + e8 * f8
 *
 * -------------------------------------------------------------*/

#include<vector>

#include"../2d/array_2d/array_2d.h"

namespace _paper_layer
{
using std::vector;
using _2d::array_2d;
using _2d::Point_2d;
using _2d::Vector_2d;

    class Lattice
    {
    public:
        Lattice()
        { 
            for(int i = 0; i < 9; i++)
                f[i] = 0.0;
        }
        /* 6 2 5
         * 3 0 1
         * 7 4 8 */
        double f[9];

        const Vector_2d<double> u()const;
        double rho()const;

        static const Point_2d<int> next_position[9];
    };

    class SurfaceLayer
    {};

    class FlowLayer:public array_2d<Lattice>
    {
    public:
        FlowLayer(int width, int height);
        void stream();
        //void draw();
        void add_water(const Lattice & l, Point_2d<int> position);
    private:
        vector< Point_2d<int> > lattice_position_list;
        bool has_water(Point_2d<int> p);
        array_2d<bool> has_water_table;
    };

    class FixtureLayer
    {};
}
#endif
