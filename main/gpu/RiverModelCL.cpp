#include "RiverModelCL.h"

RiverModelCL::RiverModelCL(patch** patches, int size, string filename, string function)
{
    cout << "input size: " << size << endl;
    cl_int error;
    RiverModelCL::patches = patches;
    RiverModelCL::size = size;
    device = RiverModelCL::getDevice(); 
    context = RiverModelCL::createContext();
    program = RiverModelCL::loadProgram(filename);
    kernel = RiverModelCL::buildProgram(function);

    cmd_queue = clCreateCommandQueue(context, device, 0, &error);
    checkErr(error, "Error creating command queue!", true);
}

RiverModelCL::~RiverModelCL()
{
    clReleaseContext(context);
    clReleaseCommandQueue(cmd_queue);
    clReleaseProgram(program);
    clReleaseKernel(kernel);
}

// Go function for GPU
// TODO: Need to put the loop above in here,
//       this is semi-temporary until we have everything running on GPU.
void RiverModelCL::goGPU(int x)
{
    cl_int error;

    int mem_size = size * sizeof(patch);

    inPatches = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                    mem_size, patches[x], &error);
    checkErr(error, "Error copying inPatches to GPU!", true);

    outPatches = clCreateBuffer(context, CL_MEM_WRITE_ONLY | CL_MEM_COPY_HOST_PTR,
                                     mem_size, patches[x], &error);
    checkErr(error, "Error copying outPatches to GPU!", true);


    error = clSetKernelArg(kernel, 0, sizeof(cl_mem), &inPatches);
    error |= clSetKernelArg(kernel, 1, sizeof(cl_mem), &outPatches);
    checkErr(error, "Error setting kernel args!", true);
}

RiverModelCL::~RiverModelCL()
{
    clReleaseContext(context);
    clReleaseCommandQueue(cmd_queue);
    clReleaseProgram(program);
    clReleaseKernel(kernel);
    clReleaseMemObject(inPatches);
    clReleaseMemObject(outPatches);
}

// Go function for GPU
// TODO: Need to put the loop above in here,
//       this is semi-temporary until we have everything running on GPU.
void RiverModelCL::goGPU(int x)
{
    size_t gWorkSize[1];
    gWorkSize[0] = size;
    size_t lWorkSize[1];
    lWorkSize[0] = 1;

    error = clEnqueueNDRangeKernel(cmd_queue, kernel, 1, NULL, gWorkSize, lWorkSize, 0, NULL, NULL);
    checkErr(error, "Error firing kernel!", true);

    // Copy back values into patches
    error = clEnqueueReadBuffer(cmd_queue, outPatches, CL_TRUE, 0, mem_size, patches[x], 0, NULL, NULL);
    checkErr(error, "Error copying from GPU buffer!", true);

    clReleaseMemObject(inPatches);
    clReleaseMemObject(outPatches);
}

/*
 * Attempt to get a cl_device, first trying for GPU, then CPU.
 * 
 * return - the cl_device_id that was available onthe system
 */
cl_device_id RiverModelCL::getDevice()
{
    cl_int error;
    cl_uint num;
    cl_platform_id platform;
    cl_device_id device;
    error = clGetPlatformIDs(1, &platform, &num);
    checkErr(error, "Error getting platform ID", true);

    error = clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU, 1, &device, &num);
    if(checkErr(error, "Error getting GPU!", false))
    {
        cout << "Error, no GPU found!\nChecking for CPU" << endl;
        error = clGetDeviceIDs(platform, CL_DEVICE_TYPE_CPU, 1, &device, &num);
        checkErr(error, "Error getting CPU!\n Cant recover!", true);
    }

    return device;
}

cl_context RiverModelCL::createContext()
{
    cl_int error;
    cl_context_properties context_properties[2];
    context_properties[1] = 0;
    context = clCreateContext(0, 1, &device, NULL, NULL, &error);
    checkErr(error, "Error creating context!", true);
    return context;
}


/*
 * Load program source based on filename.
 * 
 * filename - the file to load the source from
 * context - TODO - why does clCreateProgramWIthSource need this?
 *
 * return - the cl_program that was created
 */
cl_program RiverModelCL::loadProgram(string filename)
{
    cl_int error;
    std::ifstream kernelFile(filename.c_str(), std::ios::in);
    if(!kernelFile.is_open())
    {
        cerr << "Failed to open kernel file for reading!" << endl;
        clReleaseContext(context);
        return NULL;
    }

    std::ostringstream oss;
    oss << kernelFile.rdbuf();

    std::string srcStr = oss.str();
    // Load source to cl_program
    cout << "Loading program source" << endl;
    cl_program program = clCreateProgramWithSource(context, 1, (const char**)&srcStr, NULL, &error);
    checkErr(error, "Error loading program source!", true);
    if(error != CL_SUCCESS)
    {
        return NULL;
    }
    else
    {
        return program;
    }
}

/*
 * Build an OpenCL program and store it on the device.
 * 
 * program - The program to build
 * device - the device to build the program for
 *
 * return - a cl_kernel representing the program
 */
cl_kernel RiverModelCL::buildProgram(string function)
{
    cl_int error;
    cout << "Building program" << endl;
    error = clBuildProgram(program, 1, &device, NULL, NULL, NULL);
    //checkErr(error, "Erorr building program!", false);

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

    checkErr(error, "Error with build, exiting!", true);

    cl_kernel kernel = clCreateKernel(program, function.c_str(), &error);

    checkErr(error, "Create kernel failed!", true);

    return kernel;
}
