cmake_minimum_required(VERSION 3.16)
project(implement_iterator)

set(CMAKE_CXX_FLAGS "-std=c++11 -Wall -O3")

file(GLOB SRC src/*.cpp)
add_executable(implement_iterator ${SRC})
