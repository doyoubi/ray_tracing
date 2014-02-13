#include<iostream>
using std::cout;
using std::cin;
using std::endl;

#include"array_2d.h"
using namespace _2d;

struct test_struct
{ int mem; };

bool test_template_instantiation()
{
    array_2d<int> mat(3, 2);
    mat[0][0] = 0;
    mat[0][1] = 1;
    mat[1][0] = 2;
    mat[1][1] = 3;
    mat[2][0] = 4;
    mat[2][1] = 5;
    array_2d<int>::iterator a = mat.begin();
    array_2d<int>::iterator b = mat.begin();
    cout<< (a == b) <<endl;
    cout<< ((a != b) == false) <<endl;
    b++; a = b; cout<< (*a == 1) <<endl;

    array_2d<test_struct> mat2(2,2);
    for(auto it = mat2.begin(); it != mat2.end(); it++)
        (*it).mem = 1234;
    for(auto it = mat2.begin(); it != mat2.end(); it++)
        cout<< it->mem <<endl;
    return true;
}

int main()
{
    test_template_instantiation();
    return 0;
}

