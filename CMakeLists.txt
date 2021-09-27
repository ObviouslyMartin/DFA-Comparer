cmake_minimum_required(VERSION 3.14)
project(dfacompare)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(dfacompare
        DFA.cpp
        DFA.hpp
        main.cpp
        README.md
        UnFi.cpp
        UnFi.hpp)
