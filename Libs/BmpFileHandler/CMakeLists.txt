add_library(BmpHandler STATIC BmpFileHandler.cpp)
target_include_directories(BmpHandler INTERFACE ${CMAKE_CURRENT_LIST_DIR})