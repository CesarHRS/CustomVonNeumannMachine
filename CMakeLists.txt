cmake_minimum_required(VERSION 3.29)
project(CustomVonNeumannMachine)

set(CMAKE_CXX_STANDARD 26)

add_executable(CustomVonNeumannMachine src/main.cpp
        src/ULA.cpp
        src/ULA.h
        src/REGISTER.cpp
        src/REGISTER.h
        src/REGISTER_BANK.cpp
        src/REGISTER_BANK.h)
