#include <utility>
#define __NO_STD_VECTOR

#include <CL/cl.h>

#include <stdlib.h>
#include <iostream>
#include <string>

using std::cerr;
using std::cout;
using std::endl;

cl_platform_id platform;
cl_context context;
cl_command_queue cmd_queue;
cl_device_id device;

inline void checkErr(cl_int error, const char* name);


int main(int argc, char** argv)
{
    cl_uint num_platforms;
    cl_int error = clGetPlatformIDs(1, &platform, &num_platforms);
    checkErr(error, "Error getting platform ID");
    if( num_platforms == 1)
        cout << "Success!" << endl;
    else
    {
        cout << "ERROR!" << endl;
        return -1;
    }
    return 0;
}


inline void checkErr(cl_int error, const char* name)
{
    if(error != CL_SUCCESS)
    {
        cerr << "ERROR: " << name
             << " (" << error << ")" << endl;
        exit(EXIT_FAILURE);
    }
}
