#ifndef TEST
#define TEST

#include<stdlib.h>
#include<fstream>
using std::endl;
std::ofstream fout("error_message.txt");
#include<time.h>

void validate(bool to_be_validated, const char * const error_message)
{
    if( ! to_be_validated )
    {
        time_t now;
        time( &now );
        fout<< asctime( gmtime(&now) )
            << error_message <<endl<<endl;
        fout.close();
        exit(1);
    }
}

#endif
