cmake_minimum_required(VERSION 3.16)
project(CPP_OrgChart_a)

set(CMAKE_CXX_STANDARD 14)

add_executable(CPP_OrgChart_a Demo.cpp sources/OrgChart.cpp sources/OrgChart.hpp Test.cpp)
