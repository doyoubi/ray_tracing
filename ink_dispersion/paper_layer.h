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
{
};

class Texture
{
public:
    Texture();
    // array_2d<double> paper_grain;
    array_2d<double> alum;
};

class FlowLayer
{
public:
    FlowLayer(int width, int height);
    void stream();
    void add_water(double seep, Point_2d<int> position);
    array_2d<Lattice> * curr_state;
    void draw();
private:
    Texture texture;
    array_2d<Lattice> * last_state;
    array_2d<Lattice> state1;
    array_2d<Lattice> state2;
};

class FixtureLayer
{};
}
#endif
