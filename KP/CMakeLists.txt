cmake_minimum_required(VERSION 3.8)

project(lab4 VERSION 1.0 LANGUAGES CXX)

set(MAIN main)
set(MAIN_SOURCE General.hpp General.cpp FuncMaker.hpp FuncMaker.cpp ImproperIntegral.hpp ImproperIntegral.cpp main.cpp)

#set(BOOST_LIBS boost_iostreams boost_system boost_filesystem)

add_executable(${MAIN} ${MAIN_SOURCE})
#target_link_libraries(${MAIN} ${BOOST_LIBS})

add_definitions(-std=c++11 -Wextra -Wall -Werror -Wno-sign-compare -Wno-unused-result)