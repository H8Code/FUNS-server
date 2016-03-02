cmake_minimum_required(VERSION 2.8)

project(FUNS-server)

set (CMAKE_CXX_FLAGS "-std=c++14")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
#link_directories(/usr/lib/x86_64-linux-gnu/)

include_directories("../restbed/distribution/include")
include_directories("/usr/local/include/bsoncxx/v_noabi")
include_directories("/usr/local/include/mongocxx/v_noabi")
include_directories("./spdlog/include")
link_directories("../restbed/distribution/library")
add_library(restbed SHARED IMPORTED)
add_library(mongocxx SHARED IMPORTED)
add_library(bsoncxx SHARED IMPORTED)
add_library(mhash SHARED IMPORTED)

aux_source_directory(. SRC_LIST)

add_executable(funs-server ${SRC_LIST})
target_link_libraries(funs-server "bsoncxx.so")
target_link_libraries(funs-server "mongocxx.so")
target_link_libraries(funs-server "restbed.so")
target_link_libraries(funs-server "pthread.so")
target_link_libraries(funs-server "mhash.so")
