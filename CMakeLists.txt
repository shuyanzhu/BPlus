cmake_minimum_required(VERSION 2.8)
project(BPlus)
add_definitions(-std=c++11)
include_directories(include)
add_subdirectory(src)
add_executable(main main.cc include/BPT_release.h include/BPT_insert.h include/BPT_remove.h include/BPT_solveOverflow.h include/BPT_solveUnderflow.h include/BPT_search.h)