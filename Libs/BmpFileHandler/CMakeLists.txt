add_library(BmpHandler STATIC BmpFileHandler.cpp)
target_include_directories(BmpHandler PUBLIC ${CMAKE_CURRENT_LIST_DIR})