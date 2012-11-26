#include "RiverModelCL.h"

cl_context context;
cl_command_queue cmd_queue;
cl_device_id device;


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
    RiverModelCL::checkErr(error, "Error getting platform ID", true);

    error = clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU, 1, &device, &num);
    if(RiverModelCL::checkErr(error, "Error getting GPU!", false))
    {
        cout << "Error, no GPU found!\nChecking for CPU" << endl;
        error = clGetDeviceIDs(platform, CL_DEVICE_TYPE_CPU, 1, &device, &num);
        RiverModelCL::checkErr(error, "Error getting CPU!\n Cant recover!", true);
    }

    return device;
}

cl_context RiverModelCL::createContext(cl_device_id device)
{
    cl_int error;
    cl_context_properties context_properties[2];
    context_properties[1] = 0;
    context = clCreateContext(0, 1, &device, NULL, NULL, &error);
    RiverModelCL::checkErr(error, "Error creating context!", true);
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
cl_program RiverModelCL::loadProgram(string filename, cl_context& context)
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
    RiverModelCL::checkErr(error, "Error loading program source!", true);
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
cl_kernel RiverModelCL::buildProgram(cl_program program, cl_device_id device)
{
    cl_int error;
    cout << "Building program" << endl;
    error = clBuildProgram(program, 1, &device, NULL, NULL, NULL);
    RiverModelCL::checkErr(error, "Erorr building program!", true);

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

    RiverModelCL::checkErr(error, "Create kernel failed!", true);

    return kernel;
}
