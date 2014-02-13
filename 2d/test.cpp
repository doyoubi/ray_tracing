#include<iostream>
using std::cout;
using std::cin;
using std::endl;

#include"2d.h"
using namespace _2d;

bool all_test_pass = true;
void check(bool to_check)
{
    if(to_check) cout<<"true"<<endl;
    else { cout<<"false"<<endl; all_test_pass = false; }
}

bool test_const()
{
    // test whether const work
    // const Image<int> const_image;
    // const_image[0][0] = 0;
}

bool test_image()
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
    check(image1.get_width() == width);
    check(image1.get_height() == height);
    cout<<endl;
    return all_test_pass;
}

int main()
{
    test_image();
    if(all_test_pass)
        cout<<"all test pass!"<<endl;
    else 
        cout<<"some test fall!!!"<<endl;
    cout<<endl;
    return 0;
}
