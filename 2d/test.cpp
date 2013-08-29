#include<iostream>
using std::cout;
using std::cin;
using std::endl;

#include"2d.h"
#include"../test/test.h"

int main()
{
    int width = 5, height = 3;
    Image<int> image1;
    image1.create(width, height);
    Image<int> image2(width, height);

    num = 0;
    for(int x = 0; x < width, ++x)
        for(int y = 0; y < height, ++y)
        {
            image1[x][y] = num;
            image2[x][y] = num;
            ++num;
        }

    for(int n = 0; n < width*height; ++n)
        cout<<image1<<' '<<image2<<' ';
    cout<<endl;
    return 0;
}
