#include "RiverModelCL.h"

int main(int argc, char** argv)
{

    //
    // Get devices and setup context and command queue.
    //
    cl_int error;

    cl_device_id device = RiverModelCL::getDevice();

    cl_context context = RiverModelCL::createContext(device);

    cl_command_queue cmd_queue = clCreateCommandQueue(context, device, 0, &error);
    RiverModelCL::checkErr(error, "Error creating command queue!", true);


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
    RiverModelCL::checkErr(error, "Error copying buffer src_a_d!", true);
    cl_mem src_b_d = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, mem_size, src_a_h, &error);
    RiverModelCL::checkErr(error, "Error copying buffer src_b_d!", true);
    cl_mem res_d = clCreateBuffer(context, CL_MEM_WRITE_ONLY, mem_size, NULL, &error);
    RiverModelCL::checkErr(error, "Error allocating buffer to copy to (res_d)!", true);



    // Create and build program
    cl_program program = RiverModelCL::loadProgram("testing.cl", context);

    cl_kernel kernel = RiverModelCL::buildProgram(program, device);


    // Load arguments
    error = clSetKernelArg(kernel, 0, sizeof(cl_mem), &src_a_d);
    error |= clSetKernelArg(kernel, 1, sizeof(cl_mem), &src_b_d);
    error |= clSetKernelArg(kernel, 2, sizeof(cl_mem), &res_d);
    error |= clSetKernelArg(kernel, 3, sizeof(size_t), &size);
    RiverModelCL::checkErr(error, "Setting kernel arguments failed!", true);

    size_t gWorkSize[1] = { size };
    size_t lWorkSize[1] = { 1 };

    // Fire the device
    cout << "Start adding vector." << endl;
    error = clEnqueueNDRangeKernel(cmd_queue, kernel, 1, NULL, gWorkSize, lWorkSize, 0, NULL, NULL);
    RiverModelCL::checkErr(error, "Enqueue kernel failed!", true);
    cout << "Done adding vector." << endl;
    
    float* check = new float[size];
    // Read output back
    error = clEnqueueReadBuffer(cmd_queue, res_d, CL_TRUE, 0, mem_size, check, 0, NULL, NULL);


    // Clean up memory
    clReleaseContext(context);
    clReleaseCommandQueue(cmd_queue);
    clReleaseProgram(program);
    clReleaseKernel(kernel);
    clReleaseMemObject(src_a_d); clReleaseMemObject(src_b_d); clReleaseMemObject(res_d);

    return 0;
}
