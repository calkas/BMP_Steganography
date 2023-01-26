add_executable(AppTestEncodeDecode AppTest_EncodeDecode.cpp)
target_link_libraries(AppTestEncodeDecode 
    PRIVATE
    	BmpHandler
	StegonoEncoder
	SteganoDecoder
        gtest 
        gmock 
        gtest_main
)

add_test(UT_AppTestEncodeDecode AppTestEncodeDecode)
