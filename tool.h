/*************************************************************************
	> File Name: tool.h
	> Author: 
	> Mail: 
	> Created Time: 二  7/24 14:15:09 2018
 ************************************************************************/

#ifndef TOOLH
#define TOOLH

#include <android/bitmap.h>
#include <android/log.h>
#include <CL/cl.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

/** convert the kernel file into a string */
int convertToString(const char *filename, std::string& s);

/**Getting platforms and choose an available one.*/
int getPlatform(cl_platform_id &platform);

/**Step 2:Query the platform and choose the first GPU device if has one.*/
cl_device_id *getCl_device_id(cl_platform_id &platform);
const char* opencl_error_to_str (cl_int error);

#define  LOG_TAG    "AndroidBasic"
// #define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
//#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)
/*
#define SAMPLE_CHECK_ERRORS(ERR)                                                      \
        if(ERR != CL_SUCCESS)                                                             \
        {                                                                                 \
         LOGE                                                                          \
         (                                                                             \
          "OpenCL error with code %s happened in file %s at line %d. Exiting.\n",   \
          opencl_error_to_str(ERR), __FILE__, __LINE__                              \
         );                                                                            \
         \
        }
*/

#define SAMPLE_CHECK_ERRORS(ERR)                                                      \
        if(ERR != CL_SUCCESS)                                                             \
        {                                                                                 \
         printf(                                                                             \
          "OpenCL error with code %s happened in file %s at line %d. Exiting.\n",   \
          opencl_error_to_str(ERR), __FILE__, __LINE__                              \
         );                                                                            \
         \
        }
#endif

