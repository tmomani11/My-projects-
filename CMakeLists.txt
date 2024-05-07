cmake_minimum_required(VERSION 3.23)
project(CPSC_350)

set(CMAKE_CXX_STANDARD 14)

include_directories("Assignment 3")

add_executable(CPSC_350
        "Assignment 3/main.cpp"
        "Assignment 3/MonoStack.h"
        "Assignment 3/readme"
        "Assignment 3/sampleInput.txt"
        "Assignment 3/SpeakerView.cpp"
        "Assignment 3/SpeakerView.h")
