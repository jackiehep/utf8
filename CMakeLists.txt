cmake_minimum_required(VERSION 3.22)
project(utf8)

set(CMAKE_CXX_STANDARD 11)
include_directories(/usr/include)
add_executable(utf8 main.cpp)
target_link_libraries(utf8 -lpthread)
