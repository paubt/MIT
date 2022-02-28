cmake_minimum_required(VERSION 3.16)
project(set_1 VERSION 0.1)


# specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_BUILD_TYPE Debug)

include_directories(${PROJECT_SOURCE_DIR})


add_executable (set_1_app src/main.cpp src/PartA/PartA.cpp)
