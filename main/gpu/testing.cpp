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

cl_platform_id platform;
cl_context context;
cl_command_queue cmd_queue;
cl_device_id device;

inline void checkErr(cl_int error, const char* name);

int main(int argc, char** argv)
{
    cl_uint num;
    cl_int error;

    error = clGetPlatformIDs(1, &platform, &num);
    checkErr(error, "Error getting platform ID");

    cl_device_id device;

    //TODO: Possibly register a callback function with our context so we're not ignoring errors.
    cl_context_properties context_properties[2];
    context_properties[1] = 0;
    cl_context context;

    error = clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU, 1, &device, &num);
    checkErr(error, "Error getting GPU!");
    if(num != 1 || error != CL_SUCCESS)
    {
        cout << "Error, no GPU found!\nChecking for CPU" << endl;
        error = clGetDeviceIDs(platform, CL_DEVICE_TYPE_CPU, 1, &device, &num);
        checkErr(error, "Error getting CPU");
        if(num != 1 || error != CL_SUCCESS)
        {
            cout << "Error, no CPU found!\nCant recover!" << endl;
            exit(EXIT_FAILURE);
        }
    }

    context = clCreateContext(0, 1, &device, NULL, NULL, &error);
    checkErr(error, "Error creating context!");

    cmd_queue = clCreateCommandQueue(context, device, 0, &error);
    checkErr(error, "Error creating command queue!");


    //
    // Setup memory
    //
    const int size = 12345678;
    float* src_a_h = new float[size];
    float* src_b_h = new float[size];
    float* res_h = new float[size];

    for(int i = 0; i < size; i++)
    {
        src_a_h[i] = src_b_h[i] = (float) i;
    }

    const int mem_size = sizeof(float) * size;

    // Copy memory onto device
    cl_mem src_a_d = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, mem_size, src_a_h, &error);
    checkErr(error, "Error copying buffer src_a_d!");
    cl_mem src_b_d = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, mem_size, src_a_h, &error);
    checkErr(error, "Error copying buffer src_b_d!");
    cl_mem res_d = clCreateBuffer(context, CL_MEM_WRITE_ONLY, mem_size, NULL, &error);
    checkErr(error, "Error allocating buffer to copy to (res_d)!");


    //
    // Load source
    //
    cl_program program;

    std::ifstream kernelFile("testing.cl", std::ios::in);
    if(!kernelFile.is_open())
    {
        cerr << "Failed to open kernel file for reading!" << endl;
        clReleaseContext(context);
        return -1;
    }

    std::ostringstream oss;
    oss << kernelFile.rdbuf();
    
    std::string srcStr = oss.str();
    // Load source to cl_program
    cout << "Loading program source" << endl;
    program = clCreateProgramWithSource(context, 1, (const char**)&srcStr, NULL, NULL);
    checkErr(error, "Error loading program source!");

    // Build program
    cout << "Building program" << endl;
    error = clBuildProgram(program, 1, &device, NULL, NULL, NULL);
    checkErr(error, "Erorr building program!");

    //
    // Get build info
    //

    size_t log_size;

    // Get log size
    clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, 0, NULL, &log_size);
    char build_log[log_size+1];

    // Get and output the log
    clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, log_size, build_log, NULL);
    build_log[log_size] = '\0';
    cout << build_log << endl;

    cl_kernel kernel = clCreateKernel(program, "vector_add_gpu", &error);
    checkErr(error, "Create kernel failed!");

    error = clSetKernelArg(kernel, 0, sizeof(cl_mem), &src_a_d);
    error |= clSetKernelArg(kernel, 1, sizeof(cl_mem), &src_b_d);
    error |= clSetKernelArg(kernel, 2, sizeof(cl_mem), &res_d);
    error |= clSetKernelArg(kernel, 3, sizeof(size_t), &size);
    checkErr(error, "Setting kernel arguments failed!");

    size_t gWorkSize[1] = { size };
    size_t lWorkSize[1] = { 1 };

    error = clEnqueueNDRangeKernel(cmd_queue, kernel, 1, NULL, gWorkSize, lWorkSize, 0, NULL, NULL);
    checkErr(error, "Enqueue kernel failed!");
    
    float* check = new float[size];
    // Read output back
    error = clEnqueueReadBuffer(cmd_queue, res_d, CL_TRUE, 0, mem_size, check, 0, NULL, NULL);

    for(int i = 0; i < size; i++)
    {
        cout << i << ": " << check[i] << endl;
    }

    // Clean up memory
    clReleaseContext(context);
    clReleaseCommandQueue(cmd_queue);
    clReleaseProgram(program);
    clReleaseKernel(kernel);
    clReleaseMemObject(src_a_d); clReleaseMemObject(src_b_d); clReleaseMemObject(res_d);

    return 0;
}


inline void checkErr(cl_int error, const char* name)
{
    if(error != CL_SUCCESS)
    {
        cerr << "ERROR: " << name
            << " (" << error << ")" << endl;
    }
}
