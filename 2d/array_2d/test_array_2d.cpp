#include<iostream>
#include"array_2d.h"
#include"../2d.h"
using _2d::Point_2d;
using _2d::array_2d;
using std::cout;
using std::cin;
using std::endl;

bool all_test_pass = true;
void check(bool to_check)
{
    if(to_check) cout<<"true"<<endl;
    else { cout<<"false"<<endl; all_test_pass = false; }
}

bool test_const()
{
    // test whether const work
    //
    // const array_2d<int> const_image(3, 2);
    // const_image[1][0] = 0;
}

bool test_opertor()
{
    cout<<"test_opertor"<<endl;
    int width = 5, height = 3;
    array_2d<int> image1(width, height);
    array_2d<int> image2(width, height);

    int num = 0;
    for(int x = 0; x < width; ++x)
        for(int y = 0; y < height; ++y)
        {
            image1[x][y] = num;
            image2[x][y] = num;
            ++num;
        }
    for(int x = 0; x < width; ++x)
        for(int y = 0; y < height; ++y)
        {
            check(image1[x][y] == image2[x][y]);
            check(image1[Point_2d<int>(x, y)] == image2[x][y]);
        }
            
    check(image1.get_width() == width);
    check(image1.get_height() == height);
    cout<<endl;
    return all_test_pass;
}

bool test_pred()
{
    cout<<"test_pred"<<endl;
    array_2d<int> arr(3, 3);
    for(int x = 0; x < 3; x++)
        for(int y = 0; y < 3; y++)
        {
            check(arr.is_valid_position(x, y));
            check(arr.is_valid_position(Point_2d<int>(x, y)));
        }
    check(!arr.is_valid_position(-1, 0));
    check(!arr.is_valid_position(0, -1));
    check(!arr.is_valid_position(3, 0));
    check(!arr.is_valid_position(0, 3));

    check(arr.is_border(0, 0));
    check(arr.is_border(1, 0));
    check(arr.is_border(0, 1));
    check(arr.is_border(2, 0));
    check(arr.is_border(0, 1));
    check(!arr.is_border(1, 1));
    return all_test_pass;
}

bool test_iterator()
{
    cout<<"test_iterator"<<endl;
    struct test_struct
    { int mem; };
    array_2d<int> mat(3, 2);
    mat[0][0] = 0;
    mat[0][1] = 1;
    mat[1][0] = 2;
    mat[1][1] = 3;
    mat[2][0] = 4;
    mat[2][1] = 5;
    array_2d<int>::iterator a = mat.begin();
    array_2d<int>::iterator b = mat.begin();
    check(a == b);
    check(!(a != b));
    b++; a = b;
    check(*a == 1);

    array_2d<test_struct> mat2(2,2);
    for(auto it = mat2.begin(); it != mat2.end(); it++)
        (*it).mem = 1234;
    for(auto it = mat2.begin(); it != mat2.end(); it++)
        check(it->mem == 1234);
    for(auto s : mat2)
        check(s.mem == 1234);
    return all_test_pass;
}

bool test_copy()
{
    cout<<"test_copy"<<endl;
    array_2d<int> a1(3,2);
    array_2d<int> a2(5,4);
    a1 = a2;
    check(a1.get_width() == a2.get_width());
    check(a1.get_height() == a2.get_height());
    for(int x = 0; x < 5; x++)
        for(int y = 0; y < 4; y++)
            check(a1[x][y] == a2[x][y]);
    for(auto it1 = a1.begin(), it2 = a2.begin();
            it1 != a1.end() && it2 != a2.end(); it1++, it2++)
        check(*it1 == *it2);
    return all_test_pass;
}

int main()
{
    if(!test_opertor()) cout<<"test_opertor fail"<<endl;
    if(all_test_pass && !test_iterator()) cout<<"test_iterator fail"<<endl;
    if(all_test_pass && !test_pred()) cout<<"test_pred fail"<<endl;
    if(all_test_pass && !test_copy()) cout<<"test_copy fail"<<endl;
    if(all_test_pass)
        cout<<"all test pass!"<<endl;
    else 
        cout<<"some test fall!!!"<<endl;
    cout<<endl;
    return 0;
}
