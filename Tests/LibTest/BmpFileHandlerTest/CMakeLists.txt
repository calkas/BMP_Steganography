
add_executable(BmpFileHandlerTest BmpFileHandlerTest.cpp)
target_link_libraries(BmpFileHandlerTest 
    PRIVATE
        gtest_main
	    BmpHandler
)

enable_testing()

add_test(UT_BmpFileHandlerTest BmpFileHandlerTest)