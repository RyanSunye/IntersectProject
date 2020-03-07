cmake_minimum_required(VERSION 3.15)
project(IntersectProject)

set(CMAKE_CXX_STANDARD 14)

add_executable(intersect src/main.cpp src/Line.cpp src/Line.h)

add_executable(test test/test.cpp src/Line.cpp src/Line.h)

add_executable(line_intersect_test src/Line.cpp src/Line.h test/line_intersect_test.cpp)