cmake_minimum_required(VERSION 2.6)

project(R_BMP_STEGANOGRAPHY LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#Bring the headers into the project

set(INCLUDE_DIRECTORIES
    R_BMP_Steganography)

include_directories(${INCLUDE_DIRECTORIES})

set(SOURCES
    main.cpp
	R_BMP_Steganography/HideData_BMP_R.cpp)

#However, the file(GLOB...) allows for wildcard additions:
#file(GLOB SOURCES "src/*.cpp")

add_executable(R_BMP_STEGANOGRAPHY ${SOURCES})
