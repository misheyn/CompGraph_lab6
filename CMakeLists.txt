cmake_minimum_required(VERSION 3.20)
project(CompGraph_lab6)

set(CMAKE_CXX_STANDARD 20)

add_executable(CompGraph_lab6 main.cpp AreaFill.cpp AreaFill.h)

target_link_libraries(CompGraph_lab6 -lOpenGL32 -lfreeGLUT -lGLU32)