cmake_minimum_required(VERSION 3.28)
project(Assignment5)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Assignment5
        BST.h
        DataBase.cpp
        DataBase.h
        Faculty.cpp
        Faculty.h
        ListNode.h
        main.cpp
        Student.cpp
        Student.h
        Menu.cpp
        Menu.h
)
