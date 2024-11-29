cmake_minimum_required(VERSION 3.29)
project(Project1LandmineGrid C)

set(CMAKE_C_STANDARD 11)

add_executable(Project1LandmineGrid src/main.c)
add_executable(landmineGame src/landmineGame.c
                            src/main.c)
add_executable(dijkstra src/dijkstra.c
                        src/program.c
                        src/functions.h)
