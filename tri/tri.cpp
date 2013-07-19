#include"tri.h"
#include<math.h>
#include<string.h>

namespace _tri
{
    inline double ang_to_rad( double ang )
    {
        return PI * ang / 180 ;
    }
    inline double rad_to_ang( double rad )
    {
        return rad * 180 / PI ;
    }

    Tri_function::Tri_function()
    {
        memset(sin_table, 0, ( TABLE_LEN ) * sizeof(double)) ;
        memset(cos_table, 0, ( TABLE_LEN ) * sizeof(double)) ;
        int i;
        for( i = 0 ; i < TABLE_LEN ; ++i )
        {
            sin_table[i] = ::sin( ang_to_rad( i * PRECISION ) );
            cos_table[i] = ::cos( ang_to_rad( i * PRECISION ) );
        }
    }
    double Tri_function::sin( double ang )
    {
        while( ang < 0 )
            ang += 360 ;
        while( ang >= 360 )
            ang -= 360 ;
        int i = ang / PRECISION ;
        return sin_table[i] + ( ( ang - i * PRECISION ) * ( sin_table[i+1] - sin_table[i] ) / PRECISION );
    }
}