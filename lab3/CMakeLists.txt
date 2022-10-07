cmake_minimum_required(VERSION 3.8)

project(lab3 VERSION 1.0 LANGUAGES CXX)

set(MAIN main)
set(MAIN_SOURCE Matrix.hpp FuncMaker.hpp FuncMaker.cpp General.hpp General.cpp LU.hpp 3-1.hpp 3-1.cpp 3-2.hpp 3-2.cpp 3-3.hpp 3-3.cpp 3-4.hpp 3-4.cpp 3-5.hpp 3-5.cpp main.cpp)
#set(MAIN_SOURCE Graphic.hpp Graphic.cpp main.cpp)

set(BOOST_LIBS boost_iostreams boost_system boost_filesystem)

add_executable(${MAIN} ${MAIN_SOURCE})
target_link_libraries(${MAIN} ${BOOST_LIBS})

add_definitions(-std=c++11 -Wextra -Wall -Werror -Wno-sign-compare -Wno-unused-result)