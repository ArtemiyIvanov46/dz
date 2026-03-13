cmake_minimum_required(VERSION 3.20)

project(Hw1.3)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


include_directories(include)


add_executable(MyProject main.cpp
               src/gradient.cpp
               src/vec3.cpp
               src/transformations.cpp)
