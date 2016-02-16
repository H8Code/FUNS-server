cmake_minimum_required(VERSION 2.8)

project(FUNS-server)

set (CMAKE_CXX_FLAGS "-std=c++11")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
#link_directories(/usr/lib/x86_64-linux-gnu/)

add_library(cpprest SHARED IMPORTED)

aux_source_directory(. SRC_LIST)

add_executable(funs-server ${SRC_LIST})
target_link_libraries(funs-server "cpprest.so")
