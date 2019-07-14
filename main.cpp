/*************************************************************************
	> File Name: main.cpp
	> Author: 
	> Mail: 
	> Created Time: 二  7/24 14:26:00 2018
 ************************************************************************/

#include <CL/cl.h>
#include "tool.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

int main(){
    cl_int    status;
    /**Step 1: Getting platforms and choose an available one(first).*/
    cl_platform_id platform;
    getPlatform(platform);
    /**Step 2:Query the platform and choose the first GPU device if has one.*/
    cl_device_id *devices = getCl_device_id(platform);
    /**Step 3: Create context.*/
    cl_context context = clCreateContext(NULL,1, devices,NULL,NULL,NULL);
    /**Step 4: Creating command queue associate with the context.*/
    cl_command_queue commandQueue = clCreateCommandQueue(context, devices[0], 0, &status);
    /**Step 5: Create program object */
    const char *filename = "HelloWorld_Kernel.cl";
    string sourceStr;
    status = convertToString(filename, sourceStr);
    const char *source = sourceStr.c_str();
    size_t sourceSize[] = {strlen(source)};
    cl_program program = clCreateProgramWithSource(context, 1, &source, sourceSize, NULL);
    status=clBuildProgram(program, 0, 0, 0, 0, 0);
    /**Step 7: Initial input,output for the host and create memory objects for the kernel*/
    const int NUM = 100000;
    float* input = new float[NUM];
    for(int i = 0;i < NUM;i++)
        input[i] = float(random());
    float* output = new float[NUM];
    cl_mem inputBuffer = clCreateBuffer(context, CL_MEM_READ_ONLY|CL_MEM_COPY_HOST_PTR, (NUM) * sizeof(float), (void *) input, NULL);
    cl_mem outputBuffer = clCreateBuffer(context, CL_MEM_WRITE_ONLY , NUM * sizeof(float), NULL, NULL);
    /**Step 8: Create kernel object */
    cl_kernel kernel = clCreateKernel(program,"helloworld", NULL);
    auto time0 = time();
    /**Step 9: Sets Kernel arguments.*/
    status = clSetKernelArg(kernel, 0, sizeof(cl_mem), &inputBuffer);
    status = clSetKernelArg(kernel, 1, sizeof(cl_mem), &outputBuffer);
    /**Step 10: Running the kernel.*/
    size_t global_work_size[1] = {NUM};
    cl_event enentPoint;
    status = clEnqueueNDRangeKernel(commandQueue, kernel, 1, NULL, global_work_size, NULL, 0, NULL, &enentPoint);
    SAMPLE_CHECK_ERRORS(status);
    clWaitForEvents(1,&enentPoint); ///wait
    clReleaseEvent(enentPoint);
    /**Step 11: Read the cout put back to host memory.*/
    status = clEnqueueReadBuffer(commandQueue, outputBuffer, CL_TRUE, 0, NUM * sizeof(float), output, 0, NULL, NULL);
    auto time1 = time();
    auto time_use = time_diff(time0, time1);
    std::cout << " time cost: " << time_use << std::endl;
    // for (int i = 0; i < NUM; i++)
    //     cout << output[i] << endl;

    /**Step 12: Clean the resources.*/
    status = clReleaseKernel(kernel);//*Release kernel.
    status = clReleaseProgram(program);    //Release the program object.
    status = clReleaseMemObject(inputBuffer);//Release mem object.
    status = clReleaseMemObject(outputBuffer);
    status = clReleaseCommandQueue(commandQueue);//Release  Command queue.
    status = clReleaseContext(context);//Release context.
    SAMPLE_CHECK_ERRORS(status);

    if (output != NULL)
    {
        free(output);
        output = NULL;
    }

    if (devices != NULL)
    {
        free(devices);
        devices = NULL;
    }
    return 0;
}
