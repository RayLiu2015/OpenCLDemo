#!/bin/bash

rm -rf CMake*

CXX_FLAGS="-march=armv7-a -mfpu=neon -mfloat-abi=softfp -pie -fPIE -w -Wno-error=format-security -std=c++11"

TOOLCHAIN_FILE="../android.toolchain.cmake"
ABI="armeabi-v7a with NEON"
MODE="Release"
ANDROID_PLATFORM_VERSION="android-22"

cmake   ..  \
        -DANDROID_ABI="${ABI}" \
        -DCMAKE_BUILD_TYPE="${MODE}" \
        -DCMAKE_TOOLCHAIN_FILE="${TOOLCHAIN_FILE}" \
        -DANDROID_PLATFORM="${ANDROID_PLATFORM_VERSION}" \
        -DCMAKE_CXX_FLAGS="${CXX_FLAGS}" \
        -DANDROID=true \

make -j

adb push main /data/local/tmp/test_opencl
adb push ../HelloWorld_Kernel.cl /data/local/tmp/test_opencl
