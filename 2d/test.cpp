#include<iostream>
using std::cout;
using std::cin;
using std::endl;

#include"2d.h"
using namespace _2d;

void check(bool to_check)
{
    if(to_check) cout<<"true"<<endl;
    else cout<<"false"<<endl;
}

bool test_operator()
{
    Vector_2d v1(1,1);
    Vector_2d v2(2,-1);

    cout<<"test operator == : ";
    check(v1 == Vector_2d(1,1));

    cout<<"test operator + : ";
    check(v1 + v2 == Vector_2d(3, 0));

    cout<<"test operator - : ";
    check(v1 - v2 == Vector_2d(-1, 2));

    cout<<"test operator vector * vector: ";
    check(v1 * v2 == 1);

    cout<<"test operator number * vector: ";
    check(v1 * 2 == Vector_2d(2,2));
    
    cout<<"test operator vector * number: ";
    check(2 * v1 == Vector_2d(2,2));

    cout<<"test operator = : ";
    v2 = v1;
    check(v1 == v2);
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
}

int main()
{
    test_operator();
    test_image();
    return 0;
}
