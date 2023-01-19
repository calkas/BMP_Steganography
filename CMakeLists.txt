cmake_minimum_required(VERSION 3.13)

project(R_SteganographyEncoder LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(Libs)
add_subdirectory(Steganography_Encoder)
add_subdirectory(Tests)

enable_testing()

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/Mics/Test_Img.bmp
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Tests/LibTest/BmpFileHandlerTest)
