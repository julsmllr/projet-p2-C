cmake_minimum_required(VERSION 3.24)
project(2526_TI301_PJT C)

set(CMAKE_C_STANDARD 11)

add_executable(TI_301_PJT
        main.c
        src/utils.c
        src/cell.c
        src/list.c
        src/list_adjacence.c
        src/graphe.c
        src/tarjan_vertex.c
        include/tarjan_vertex.h)

