cmake_minimum_required(VERSION 3.13)
project(parallel2019)

set(CMAKE_CXX_STANDARD 17)

add_executable(parallel2019 labm15.cpp labm19.cpp labm18.cpp master.cpp slave.cpp)