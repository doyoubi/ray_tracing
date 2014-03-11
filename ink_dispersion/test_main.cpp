#include<iterator>
#include<algorithm>
#include<iostream>
#include"../2d/point_2d/point_2d.h"
#include"paper_layer.h"
#include"formula.h"
#include"paper_layer.h"
using std::cout;
using std::endl;
using _2d::Point_2d;
using _paper_layer::FlowLayer;

void init();
void cal_fi(int x, int y);
void output();

FlowLayer flowlayer(7,7);

int main()
{
    init();
    output(); cout<<endl;
    for(int i = 0; i < 2; i++)
    {
        flowlayer.stream();
        output(); cout<<endl;
        flowlayer.add_water(0.3, Point_2d<int>(3,3));
    }
    return 0;
}

void init()
{
    cout.precision(3);
    flowlayer.add_water(1, Point_2d<int>(3,3));
}

void output()
{
    for(int i = 0; i < 7; i++)
    {
        for(int j = 0; j < 7; j++)
            cout<<'\t'<< (*(flowlayer.curr_state))[j][i].rho() <<' ';
        cout<<endl;
    }
}
