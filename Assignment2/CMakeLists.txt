cmake_minimum_required(VERSION 3.23)
project(Assignment2)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Assignment2
        FileIO.cpp
        FileIO.h
        main.cpp
        Mario.cpp
        Mario.h
        World.cpp
        World.h)
