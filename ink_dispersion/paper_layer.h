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


class FlowLayer
{
public:
    FlowLayer(int width, int height);
    void stream();

    struct F{ double f[9]; };
    array_2d<double> w;
    array_2d<F> curr;
    array_2d<F> temp;
    array_2d<Vector_2d<double>> u;
};

class SurfaceLayer
{
public:
    SurfaceLayer(int width, int height);
    void seep(FlowLayer &flowlayer);

    array_2d<double> w;
};


}
#endif
