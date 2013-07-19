#ifndef TRI_H_
#define TRI_H_

#define PRECISION 1
#define TABLE_LEN 360 / PRECISION
#include<math.h>

namespace _tri
{
    const double PI = ::acos( -1.0 );
    inline double ang_to_rad( double ang );
    inline double rad_to_ang( double rad );

    class Tri_function
    {
    private:
        double sin_table[ TABLE_LEN ] ;
        double cos_table[ TABLE_LEN ] ;
    public:
        Tri_function();
        double sin( double ang );
        // double cos( double ang );
        // double tan( double ang );
        // double cot( double ang );
    };

}

#endif