cmake_minimum_required(VERSION 3.8)

project(lab1 VERSION 1.0 LANGUAGES CXX)

set(MAIN main)
set(MAIN_SOURCE Matrix.hpp MatrixFunc.hpp main.cpp)

add_executable(${MAIN} ${MAIN_SOURCE})

add_definitions(-std=c++11 -Wextra -Wall -Werror -Wno-sign-compare -Wno-unused-result)