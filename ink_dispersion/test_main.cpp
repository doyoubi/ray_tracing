#include<iostream>
#include"paper_layer.h"
#include"../2d/point_2d/point_2d.h"
using std::cout;
using std::endl;
using _2d::Point_2d;

using _paper_layer::FlowLayer;
using _paper_layer::Lattice;

void print(const FlowLayer &flow_layer)
{
    cout.precision(4);
    for(int y = flow_layer.get_height()-1; y >= 0; y--)
    {
        for(int x = 0; x < flow_layer.get_width(); x++)
        {
            cout<< '\t' << flow_layer[x][y].rho() <<' ';
        }
        cout<<endl;
    }
    cout<<endl;
} 

int main()
{
    FlowLayer flow_layer(5,5);

    Lattice lattice;
    for(int i = 0; i < 9; i++)
        lattice.f[i] = 0.1;
    flow_layer.add_water(lattice, Point_2d<int>(2,2) );

    for(int i = 0; i < 3; i++)
    {
        flow_layer.stream();
        print(flow_layer);
    }
    return 0;
}
