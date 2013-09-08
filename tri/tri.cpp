#include"tri.h"
#include<math.h>
#include<string.h>
#include"../test/test.h"
namespace _tri
{

    const int PRECISION = 1;
    const int TABLE_LEN = 360 / PRECISION;
    double sin_table[ TABLE_LEN ];
    double tan_table[ TABLE_LEN ];
    double asin_table[ TABLE_LEN ];
    double atan_table[ TABLE_LEN ];

    void init_tri_table()
    {
        memset(sin_table, 0, ( TABLE_LEN ) * sizeof(double)) ;
        memset(tan_table, 0, ( TABLE_LEN ) * sizeof(double)) ;
        for(int i = 0 ; i < TABLE_LEN ; ++i )
        {
            sin_table[i] = ::sin( ang_to_rad( i * PRECISION ) );
            if( i * PRECISION/2.0 != 90 )
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
        validate( ang != 90, "tri.cpp, function tan(), angle is 90 when running tan()");
        int i = ang / ( PRECISION/2.0 );
        return tan_table[i] + ( ( ang - i * PRECISION/2.0 ) * ( (tan_table[i+1] -tan_table[i]) / ( PRECISION/2.0 ) ) );
    }

    double cot( double ang )
    {
        return tan( 90 - ang );
    }

    double asin(double value)
    {
    }

    double acos(double value)
    {
    }

    double atan(double value)
    {
    }

    double acot(double value)
    {
    }
}
