cmake_minimum_required(VERSION 3.30)
project(Version_1 C)

set(CMAKE_C_STANDARD 99)

add_executable(Version_1 main.c
        Spacegameheader.h
        movement.c
        Mapcreation.c)
