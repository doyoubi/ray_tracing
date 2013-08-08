#ifndef TRI_H_
#define TRI_H_

namespace _tri
{
    #include<math.h>
    
    // you must call init_table() before using tri funcion
    void init_table();

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
