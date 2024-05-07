cmake_minimum_required(VERSION 3.28)
project(Assignment4)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Assignment4
        Customer.cpp
        Customer.h
        DblList.h
        ListNode.h
        ListQueue.h
        main.cpp
        Office.cpp
        Office.h
        ServiceCenter.cpp
        ServiceCenter.h
        Window.cpp
        Window.h
)
