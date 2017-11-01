cmake_minimum_required(VERSION 3.7)
project(L1E3)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp CircularBuffer.h)
add_executable(L1E3 ${SOURCE_FILES})