#!/bin/bash

adb push ./bin/main /data/local/tmp/test_opencl
adb push ../HelloWorld_Kernel.cl /data/local/tmp/test_opencl
