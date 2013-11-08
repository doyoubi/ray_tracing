#ifndef PAPER_LAYER
#define PAPER_LAYER

/* ----------------------------------------------
 *       Lattice Boltzmann Equation Approach
 *
 * ----------------------------------------------*/

#include"../2d/2d.h"
using _2d::Image;

namespace paper_layer
{
    class Lattice
    {
        public:
            Lattice();
    };

    class Layer:public Image<Lattice>
    {
        public:
            Layer();
    };

    class SurfaceLayer
    {};

    class FlowLayer
    {};

    class FixtureLayer
    {};
}
#endif
