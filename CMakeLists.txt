cmake_minimum_required(VERSION 3.29)
project(P1_Landmine C)

set(CMAKE_C_STANDARD 11)

include_directories(src)

add_executable(P1_Landmine
    src/dijkstra.c
    src/functions.h
    src/program.c)
