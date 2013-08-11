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
double abs(double n)
{
    return n > 0 ? n : -n;
}
int main()
{
    _tri::init_tri_table();
    for(double i = 0; i < 360; i += 0.25)
    {
        if( abs(sin(_tri::ang_to_rad(i)) - _tri::sin(i)) < 0.0001 )
            cout<< i <<' '<<setprecision(8)<< sin(_tri::ang_to_rad(i)) <<' '<< _tri::sin(i)<<endl;
    }
    cout<<"finish"<<endl;
    cout.close();
    return 0;
}
