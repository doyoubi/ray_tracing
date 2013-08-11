#ifndef TRI_H_
#define TRI_H_
#include<cmath> 

namespace _tri
{
    // you must call init_table() before using tri funcion
    void init_tri_table();
    const double PI = ::acos( -1.0 );
    double sin( double ang );
    double cos( double ang );
    double tan( double ang );
    double cot( double ang );

    inline double ang_to_rad( double ang )
    {
        return PI * ang / 180 ;
    }
    inline double rad_to_ang( double rad )
    {
        return rad * 180 / PI ;
    }

}

#endif
