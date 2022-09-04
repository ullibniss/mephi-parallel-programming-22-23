# Initializing project
cmake_minimum_required(VERSION 3.10)
project(lab1)

# Add OpenMP
SET(GCC_COVERAGE_COMPILE_FLAGS "-fopenmp")
SET(CMAKE_C_FLAGS  "${CMAKE_C_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")

# Linking all files together and adding executable
add_executable(lab1 lab1_x10.c)