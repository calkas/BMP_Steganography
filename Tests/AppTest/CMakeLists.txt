add_executable(AppTestEncodeDecode AppTest_EncodeDecode.cpp)
target_link_libraries(AppTestEncodeDecode 
    PRIVATE
    	BmpHandler
	StegonoEncoder
	SteganoDecoder
        gtest_main
)

enable_testing()

add_test(UT_AppTestEncodeDecode AppTestEncodeDecode)
