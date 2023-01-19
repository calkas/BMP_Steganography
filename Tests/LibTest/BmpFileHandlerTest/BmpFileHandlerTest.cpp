#include "BmpFileHandler.hpp"
#include <fstream>
#include <gtest/gtest.h>

TEST(BmpFileHandlerTest, test)
{
    std::ifstream bmpFile;

    bmpFile.open("Test_Img.bmp", std::ifstream::in | std::ifstream::binary);
    EXPECT_TRUE(bmpFile.is_open());


    bmpFile.close();


    EXPECT_TRUE(true);
}
