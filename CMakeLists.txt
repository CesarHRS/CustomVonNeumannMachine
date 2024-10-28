cmake_minimum_required(VERSION 3.16)
project(CustomVonNeumannMachine)

set(CMAKE_CXX_STANDARD 20)

add_executable(CustomVonNeumannMachine
        src/main.cpp
        src/cpu/CONTROL_UNIT.cpp
        src/cpu/CONTROL_UNIT.h
        src/cpu/REGISTER.cpp
        src/cpu/REGISTER.h
        src/cpu/REGISTER_BANK.cpp
        src/cpu/REGISTER_BANK.h
        src/cpu/ALU.cpp
        src/cpu/ALU.h
        src/memory/MEMORYCELL.cpp
        src/memory/MEMORYCELL.h
        src/memory/MAINMEMORY.h
        src/memory/MAINMEMORY.cpp
        src/memory/SECONDARY_MEMORY.cpp
        src/memory/SECONDARY_MEMORY.h
)
