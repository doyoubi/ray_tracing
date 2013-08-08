#include<iostream>
using std::cout;
using std::endl;
#include"exception.h"
int main()
{
    validate( 0, "oh yeah , error appear");
    cout<< "no error" <<endl;
    return 0;
}
