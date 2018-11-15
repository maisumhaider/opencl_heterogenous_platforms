cmake_minimum_required(VERSION 3.12)
project(opencl_experiments)

set(CMAKE_CXX_STANDARD 14)
find_package(OpenCL REQUIRED)
add_executable(opencl_experiments main.cpp)
target_link_libraries(opencl_experiments OpenCL::OpenCL)