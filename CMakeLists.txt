cmake_minimum_required(VERSION 3.21)
project(LW_5d C)

set(CMAKE_C_STANDARD 11)

add_executable(solutions main.c libs/algorithms/array/array.c
        libs/algorithms/array/array.h)

add_subdirectory(libs)

target_link_libraries(solutions algorithms)
target_link_libraries(solutions data_structures)


