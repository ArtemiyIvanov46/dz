cmake_minimum_required(VERSION 3.20)

project(Hw1)

add_executable(MyProject main.cpp
               utils/calculator.cpp
               utils/calculator.h)

message(STATUS "Project configured with C++17 standard")
