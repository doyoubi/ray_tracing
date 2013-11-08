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
using std::vector;

#include"../2d/2d.h"
using _2d::Image;
using _2d::Point_2d;

namespace paper_layer
{
    class Lattice
    {
        public:
            Lattice(){ rho = 0; u = 0; }
            double f[9];
            double rho, u;

            // update  rho and u of next lattice at the same time
            void stream_fi_to_next_lattice(int direction);
        private:
            static const Point_2d next_position[9];
    };

    class SurfaceLayer
    {};

    class FlowLayer:public Image<Lattice>
    {
        public:
            FlowLayer(int width, int height);
            void draw();
            void stream();
        private:
            vector<Point_2d> lattice_position_list;
    };

    class FixtureLayer
    {};
}
#endif
