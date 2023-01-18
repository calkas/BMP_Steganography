cmake_minimum_required(VERSION 3.13)

project(R_SteganographyEncoder LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(Src)
#add_subdirectory(Tests)

add_executable(Encoder main.cpp)

target_link_libraries(Encoder PRIVATE StegonoEncoder)