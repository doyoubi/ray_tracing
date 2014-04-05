#ifndef LB_FORMULA
#define LB_FORMULA

#include"utils.h"
#include"paper_layer.h"

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

using utils::smoothstep;

double fi_next(int direction, const Lattice &current_lattice);
double f_eq(int direction, const Lattice &current_lattice);
const double w[9] = {4.0/9,
                     1.0/9, 1.0/9, 1.0/9, 1.0/9,
                     1.0/36, 1.0/36, 1.0/36, 1.0/36};
const double omega = 0.5; // relaxation parameter
const double rho_0 = 1.0;

inline double fi_next(int i, const Lattice &current_lattice)
{
    return (1 - omega) * current_lattice.f[i]
         + omega * f_eq(i, current_lattice);
}

inline double f_eq(int i, const Lattice &current_lattice)
{
    const Vector_2d<int> ei = Lattice::next_position[i];
    const Vector_2d<double> u = current_lattice.u();
    double psi = smoothstep(0.0, 0.2, current_lattice.rho());
    return w[i] *
    (
        current_lattice.rho() + rho_0 * psi *
        ( 3*(ei*u) + 9.0/2*(ei*u)*(ei*u) - 3.0/2*(u*u))
    );
}

}

#endif
