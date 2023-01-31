add_subdirectory(Src)

add_executable(Decoder main.cpp)

target_link_libraries(Decoder PRIVATE SteganoDecoder)