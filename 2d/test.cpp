#include<iostream>
using std::cout;
using std::cin;
using std::endl;

#include"2d.h"
using namespace _2d;

int main()
{
    int width = 5, height = 3;
    Image<int> image1;
    image1.create(width, height);
    Image<int> image2(width, height);

    int num = 0;
    for(int x = 0; x < width; ++x)
        for(int y = 0; y < height; ++y)
        {
            image1[x][y] = num;
            image2[x][y] = num;
            ++num;
        }

    image1.output();
    image2.output();

    cout<< image1.get_width() << ' '
        << image1.get_height() << endl;

    // const Image<int> const_image;
    // const_image[0][0] = 0;
    return 0;
}
