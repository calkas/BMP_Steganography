cmake_minimum_required(VERSION 3.13)

project(R_StegonoDecoder LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(Src)

add_executable(R_StegonoDecoder main.cpp)
