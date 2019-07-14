cmake_minimum_required(VERSION 2.8.10)

PROJECT (TEST_ANDROID)

include_directories(OpenCL-Headers/)
link_libraries(${CMAKE_CURRENT_LIST_DIR}/libs/libOpenCL.so)

SET(SRC_LIST main.cpp tool.cpp)
ADD_EXECUTABLE(main ${SRC_LIST})

if(ANDROID)
    message(STATUS " if android")
    # disable shared library on android
    set_property(GLOBAL PROPERTY TARGET_SUPPORTS_SHARED_LIBS FALSE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-rtti -fno-exceptions")
endif()
