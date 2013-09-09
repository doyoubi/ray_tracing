#include<iostream>
using std::cout;
using std::endl;
#include"bmp.h"
using _bmp::BmpFile;

int main()
{
    cout<<endl;

    BmpFile bmpfile("test.bmp");
    cout<< bmpfile.filehead.type1<< bmpfile.filehead.type2 << endl;
    for(int j = 0; j < 3; ++j)
    {
        for(int i = 0; i < 9; ++i)
            cout<< (int)bmpfile.pData[bmpfile.step*j + i] << ' ';
        cout<< endl;
    }

    cout<<endl;

    cout<<endl;
    return 0;
}
