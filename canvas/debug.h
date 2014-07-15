#ifndef DYB_DEBUG
#define DYB_DEBUG

#include <iostream>
#include <string>
#include <cmath>
#include "../Eigen/Dense"

// only for debug, should not be used as checking function in runtime
void debugCheck(bool checkedExpression,
                const char * filename,
                int line,
                std::string errorMsg)
{
    if(checkedExpression) return;
    std::cerr<< filename <<" : "<<line<<endl
             << errorMsg <<endl;
    exit(1); 
}

bool checkNormalized(double num)
{
    return 0 <= num && num <= 1;
}

bool checkVectorNormalized(const Eigen::Vector3d & v)
{
    return abs(v.norm() - 1) < errorThreshold;
}

#endif