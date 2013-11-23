#include<iostream>
using std::cout;
using std::cin;
using std::endl;

#include"2d.h"
using namespace _2d;
#define Vector_2d Point_2d

bool all_test_pass = true;
void check(bool to_check)
{
    if(to_check) cout<<"true"<<endl;
    else { cout<<"false"<<endl; all_test_pass = false; }
}


bool test_operator_double()
{
    Vector_2d<double> v1(1.0,1.0);
    Vector_2d<double> v2(2.0,-1.0);

    cout<<"test operator == : ";
    check(v1 == Vector_2d<double>(1,1));

    cout<<"test operator + : ";
    check(v1 + v2 == Vector_2d<double>(3, 0));

    cout<<"test operator - : ";
    check(v1 - v2 == Vector_2d<double>(-1, 2));

    cout<<"test operator vector * vector: ";
    check(v1 * v2 == 1);

    cout<<"test operator number * vector: ";
    check(v1 * 2 == Vector_2d<double>(2,2));
    
    cout<<"test operator vector * number: ";
    check(2 * v1 == Vector_2d<double>(2,2));

    cout<<"test operator = : ";
    v2 = v1;
    check(v1 == v2);
    cout<<endl;
}

bool test_operator_int()
{
    Vector_2d<int> v1(1,1);
    Vector_2d<int> v2(2,-1);

    cout<<"test operator == : ";
    check(v1 == Vector_2d<int>(1,1));

    cout<<"test operator + : ";
    check(v1 + v2 == Vector_2d<int>(3, 0));

    cout<<"test operator - : ";
    check(v1 - v2 == Vector_2d<int>(-1, 2));

    cout<<"test operator vector * vector: ";
    check(v1 * v2 == 1);

    cout<<"test operator number * vector: ";
    check(v1 * 2 == Vector_2d<int>(2,2));
    
    cout<<"test operator vector * number: ";
    check(2 * v1 == Vector_2d<int>(2,2));

    cout<<"test operator = : ";
    v2 = v1;
    check(v1 == v2);
    cout<<endl;
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
}

int main()
{
    test_operator_double();
    test_operator_int();
    test_image();
    if(all_test_pass)
        cout<<"all test pass!"<<endl;
    return 0;
}
