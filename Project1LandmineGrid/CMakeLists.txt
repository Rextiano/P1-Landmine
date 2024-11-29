cmake_minimum_required(VERSION 3.29)
project(Project1LandmineGrid C)

set(CMAKE_C_STANDARD 11)

include_directories(src)

add_executable(Project1LandmineGrid
        src/landmineGame.c
        src/main.c)
add_executable(dijkstra
        src/dijkstra.c
        src/functions.h
        src/program.c)