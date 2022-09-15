cmake_minimum_required(VERSION 3.8)

project(lab3 VERSION 1.0 LANGUAGES CXX)

set(MAIN main)
set(MAIN_SOURCE 3-1.hpp 3-1.cpp main.cpp)
#set(MAIN_SOURCE Graphic.hpp Graphic.cpp main.cpp)


#add_library(${FIRST} OBJECT 3-1.hpp 3-1.cpp)
#target_link_libraries(${GRAPHIC} ${SFML_LIBS})

add_executable(${MAIN} ${MAIN_SOURCE})
#target_link_libraries(${MAIN} ${FIRST})

add_definitions(-std=c++11 -Wextra -Wall -Werror -Wno-sign-compare -Wno-unused-result)