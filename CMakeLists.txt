cmake_minimum_required(VERSION 3.22)
project(dsa_project C)

set(CMAKE_C_STANDARD 99)

add_executable(autoadjust
        main.c bmp.c bmp.h helper_functions.c helper_functions.h)
