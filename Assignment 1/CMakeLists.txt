cmake_minimum_required(VERSION 3.23)
project(Assignment_1)

set(CMAKE_CXX_STANDARD 17)

add_executable(Assignment_1 main.cpp
        FileProcessor.cpp
        Model.cpp
        Translator.cpp)
