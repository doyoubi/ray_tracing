#include"tri.h"
#include<math.h>
#include<string.h>
#include"../exception/exception.h"
namespace _tri
{

    const int PRECISION = 1;
    const int TABLE_len = 360 / PRECISION;
    const double PI = ::acos( -1.0 );
    double sin_table[ TABLE_LEN ] ;
    double tan_table[ TABLE_LEN ] ;

    void init_table()
    {
        memset(sin_table, 0, ( TABLE_LEN ) * sizeof(double)) ;
        memset(cos_table, 0, ( TABLE_LEN ) * sizeof(double)) ;
        for(int i = 0 ; i < TABLE_LEN ; ++i )
        {
            sin_table[i] = ::sin( ang_to_rad( i * PRECISION ) );
            if( i * PRECISION != 90 )
                tan_table[i] = ::tan( ang_to_rad( i * PRECISION ) / 2 );
        }
    }
    double sin( double ang )
    {
        while( ang < 0 )
            ang += 360 ;
        while( ang >= 360 )
            ang -= 360 ;
        int i = ang / PRECISION ;
        return sin_table[i] + ( ( ang - i * PRECISION ) * ( sin_table[i+1] - sin_table[i] ) / PRECISION );
    }
    double cos( double ang )
    {
        return sin( ang + 90 );
    }
    double tan( double ang )
    {
        while( ang < 0 )
            ang +=180 ;
        while( ang >= 180 )
            ang -= 180 ;
        validate( ang != 90, "tri.cpp line 44, angle is 90 when run tan()");
        int i = ang / ( PRECISION/2 );
        return tan_table[i] + ( ( ang - i * PRECISION ) * ( tan_table[i+1] -tan_table[i] / ( PRECISION/2 ) ) );
    }
    double cot( double ang )
    {
        return 1 / tan( ang );
    }
}
