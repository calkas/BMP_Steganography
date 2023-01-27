
add_executable(BmpFileHandlerTest BmpFileHandlerTest.cpp)
target_link_libraries(BmpFileHandlerTest 
    PRIVATE
        gtest 
        gmock 
        gtest_main
	BmpHandler
)

add_test(UT_BmpFileHandlerTest BmpFileHandlerTest)