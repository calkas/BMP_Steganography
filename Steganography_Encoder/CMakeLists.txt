add_subdirectory(Src)

add_executable(Encoder main.cpp)

target_link_libraries(Encoder PRIVATE StegonoEncoder)
