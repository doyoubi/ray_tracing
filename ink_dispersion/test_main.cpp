#include<iostream>
#include"paper_layer.h"
using std::cout;
using std::endl;

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
    lattice.f[2] = 0.9;
    flow_layer.add_water(lattice, Point_2d<int>(2,1) );

    for(int i = 0; i < 1; i++)
    {
        flow_layer.stream();
        print(flow_layer);
    }
    return 0;
}
