#ifndef DYB_DEBUG
#define DYB_DEBUG

#include <iostream>
#include <string>

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

#endif