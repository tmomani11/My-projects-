cmake_minimum_required(VERSION 3.28)
project(Lazily_Balanced_Tree_main)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Lazily_Balanced_Tree_main
        BST.h
        DataBase.cpp
        DataBase.h
        Faculty.cpp
        Faculty.h
        ListNode.h
        main.cpp
        Student.cpp
        Student.h
        Terminal.cpp
        Terminal.h
)
