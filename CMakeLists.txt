cmake_minimum_required(VERSION 3.30)
project(n2)

set(CMAKE_CXX_STANDARD 20)

add_executable(n2 main.cpp
        sharedPTR.h
)
