cmake_minimum_required(VERSION 3.29)
project(P1_Landmine C)

set(CMAKE_C_STANDARD 11)

include_directories(Project1LandmineGrid/src)

add_executable(P1_Landmine
        Project1LandmineGrid/src/dijkstra.c
        Project1LandmineGrid/src/functions.h
        Project1LandmineGrid/src/program.c)
