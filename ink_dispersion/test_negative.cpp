/*
 *  这个程序会把1的水量分成十分，每个格子有0到10份
 *  然后去找会让 f_eq 为负数的情况（invalid的情况）
 *  结果表明有多于三分一的情况下，f_eq为负数
 */
#include<iostream>
#include<vector>
#include<iterator>
#include<algorithm>

#include"paper_layer.h"
#include"formula.h"

using std::cout;
using std::endl;
using std::cin;
using std::vector;

using namespace _paper_layer;

int invalid_count = 0, total_test_count = 0;

int mat[10][10] = {0};
void init()
{
    for(int i = 0; i <= 9; i++)
        for(int j = 0; j <= 10-i; j++) 
            mat[i][j] = 1;
}

template<class T>
void print_lattice(const T result)
{
    cout<<result[6]<<' '<<result[2]<<' '<<result[5]<<endl
        <<result[3]<<' '<<result[0]<<' '<<result[1]<<endl
        <<result[7]<<' '<<result[4]<<' '<<result[8]<<endl;
}

void check(const vector<int> &s)
{
    total_test_count++;
    Lattice lattice;
    for(int i = 0 ; i < 9; i++)
        lattice.f[i] = s[i] * 0.1;
    double feq[9] = {0};
    for(int i = 0 ; i < 9; i++)
        feq[i] = f_eq(i, lattice);
    if(std::find_if(feq, feq+9, [](double num){ return num<0; })
            != feq+9)
    {
        invalid_count++;
        print_lattice(s);
        print_lattice(feq);
        cout<<endl;
    }
}

void permutation(vector<int> s)
{
    while(s.size() < 9) s.push_back(0);
    std::sort(s.begin(), s.end());
    do
    {
        //copy(s.begin(), s.end(),
        //        std::ostream_iterator<int>(cout, " "));
        //cout<<endl;
        check(s);
    }while(std::next_permutation(s.begin(), s.end()));
}

void trans(int sum, vector<int> &s) 
{
    if(sum)
        permutation(s);
    if(sum == 10) return;
    for(int i = s.empty()? 1:s.back(); mat[sum][i] && i <= 9; i++)
    {
        s.push_back(i);
        trans(sum+i, s);
        s.pop_back();
    }
}

int main()
{
    init();
    vector<int> s;
    trans(0, s);
    cout<< invalid_count <<'/'<< total_test_count <<endl;
    return 0;
}

