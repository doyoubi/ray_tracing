#include<iostream>
//using std::cout;
#include<fstream>
std::ofstream cout("error.txt");
using std::endl;
#include"../exception/exception.h"
#include<iomanip>
using std::setprecision;

#include"tri.h"
#include<math.h>
using _tri::PI;
double abs(double n)
{
    return n >= 0 ? n : -n;
}
int main()
{
    _tri::init_tri_table();
    for(double i = 0; i < 360; i += 0.25)
    {
        if( abs(sin(_tri::ang_to_rad(i)) - _tri::sin(i)) > 0.0001 )
            cout<< i <<' '<<setprecision(8)<< sin(_tri::ang_to_rad(i)) <<' '<< _tri::sin(i)<<' '<< abs(sin(_tri::ang_to_rad(i)) - _tri::sin(i)) <<endl;
    }
    cout<<"finish sin"<<endl<<endl;

    for(double i = 0; i < 360; i += 0.25)
    {
        if( abs(cos(_tri::ang_to_rad(i)) - _tri::cos(i)) > 0.0001 )
            cout<< i <<' '<<setprecision(8)<< cos(_tri::ang_to_rad(i)) <<' '<< _tri::cos(i)<<' '<< abs(cos(_tri::ang_to_rad(i)) - _tri::cos(i)) <<endl;
    }
    cout<<"finish cos"<<endl<<endl;
    
    for(double i = 0; i < 180; i += 0.25)
    {
        if( i != 90 && abs(tan(_tri::ang_to_rad(i)) - _tri::tan(i)) > 0.0001 )
            cout<< i <<' '<<setprecision(8)<< tan(_tri::ang_to_rad(i)) <<' '<< _tri::tan(i)<<' '<< abs(tan(_tri::ang_to_rad(i)) - _tri::tan(i)) <<endl;
    }
    cout<<"finish tan"<<endl<<endl;

    for(double i = 0; i < 180; i += 0.25)
    {
        if( i != 0 && abs(tan(PI/2 - _tri::ang_to_rad(i)) - _tri::cot(i)) > 0.0001 )
            cout<< i <<' '<<setprecision(8)<< tan(PI/2 - _tri::ang_to_rad(i)) <<' '<< _tri::cot(i)<<' '<< abs(tan(PI/2 - _tri::ang_to_rad(i)) - _tri::cot(i)) <<endl;
    }
    cout<<"finish cot"<<endl<<endl;


    cout<<"finish"<<endl;
    cout.close();
    return 0;
}
