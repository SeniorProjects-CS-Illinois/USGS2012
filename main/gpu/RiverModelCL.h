#ifndef __RIVERMODELCL_H__
#define __RIVERMODELCL_H__

#include <utility>
#define __NO_STD_VECTOR

#include <CL/cl.h>

#include <stdlib.h>

#include <iostream>
#include <fstream>
#include <sstream>

#include <string>
#include <iterator>
#include <vector>

using std::ifstream;
using std::cerr;
using std::cout;
using std::endl;
using std::string;

class RiverModelCL
{
    public:
    static cl_program loadProgram(string filename, cl_context& context);
    static cl_kernel buildProgram(cl_program program, cl_device_id device);
    static cl_device_id getDevice();
    static cl_context createContext(cl_device_id device);

    static inline bool checkErr(cl_int error, const char* name, bool exitOnError)
    {
        if(error != CL_SUCCESS)
        {
            cerr << "ERROR: " << name
                << " (" << error << ")" << endl;
            if(exitOnError)
            {
                exit(EXIT_FAILURE);
            }
            else return false;
        }
        return true;
    }

    private:
    static cl_int error;
};

#endif
