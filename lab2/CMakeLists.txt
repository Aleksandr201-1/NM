cmake_minimum_required(VERSION 3.8)

project(lab2 VERSION 1.0 LANGUAGES CXX)

#set(SFML_LIBS sfml-graphics sfml-window sfml-audio sfml-system)
set(BOOST_LIBS boost_iostreams boost_system boost_filesystem)

set(MAIN main)
set(MAIN_SOURCE main.cpp General.hpp General.cpp FuncMaker.hpp FuncMaker.cpp 2-1.hpp 2-1.cpp 2-2.hpp 2-2.cpp)
#set(MAIN_SOURCE Graphic.hpp Graphic.cpp main.cpp)


#add_library(${GRAPHIC} OBJECT Graphic.hpp Graphic.cpp)
#target_link_libraries(${GRAPHIC} ${SFML_LIBS})

add_executable(${MAIN} ${MAIN_SOURCE})
target_link_libraries(${MAIN} ${BOOST_LIBS} pthread)

add_definitions(-std=c++11 -Wextra -Wall -Werror -Wno-sign-compare -Wno-unused-result)