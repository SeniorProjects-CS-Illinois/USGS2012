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

#include "../model/patch_struct.h"

using std::ifstream;
using std::cerr;
using std::cout;
using std::endl;
using std::string;

class RiverModelCL
{
    public:
    RiverModelCL(patch** patches, int size, string filename, string function);
    ~RiverModelCL();
    void goGPU(int x);

    private:
    int size;
    patch** patches;
    cl_context context;
    cl_device_id device;
    cl_program program;
    cl_kernel kernel;
    cl_command_queue cmd_queue;
    cl_mem inPatches;
    cl_mem outPatches;

    cl_program loadProgram(string filename);
    cl_kernel buildProgram(string function);
    cl_device_id getDevice();
    cl_context createContext();

    inline bool checkErr(cl_int error, const char* name, bool exitOnError)
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
