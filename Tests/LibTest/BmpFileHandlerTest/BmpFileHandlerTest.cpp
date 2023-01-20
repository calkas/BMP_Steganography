#include "BmpFileHandler.hpp"
#include <fstream>
#include <gtest/gtest.h>

TEST(BmpFileHandlerTest, BmpFileShouldHasProperValues)
{
    std::ifstream bmpFile("Test_Img.bmp", std::ifstream::in | std::ifstream::binary);
    ASSERT_TRUE(bmpFile.is_open());

    const unsigned int expBmpFileSizeInBytes {1254};
    const unsigned int expBmpImageSizeInBytes {1200};
    const unsigned int expBmpWidth {20};
    const unsigned int expBmpHeight {20};

    //------------------------------
    //BMP HEADER
    //66 77 230 4 0 0 0 0 0 0 54 0 0 0 40 0 0 0 20 0 0 0 20 0 0 0 1 0 24 0 0 0 0 0 176 4 0 0
    //------------------------------
    //BMP file parameters:
    // - BMP Width: 20 pix
    // - BMP Height: 20 pix
    // - BMP File Size in Bytes: 1254
    // - BMP Header Size in Bytes: 54
    // - BMP Image Size in Bytes: 1200
    //------------------------------

    BmpFileHandler bmpFileHandler;
    EXPECT_TRUE(bmpFileHandler.IsBmp(bmpFile));
    EXPECT_EQ(expBmpFileSizeInBytes, bmpFileHandler.GetFileSizeInBytes(bmpFile));
    EXPECT_EQ(expBmpImageSizeInBytes, bmpFileHandler.GetImageSize(bmpFile));

    auto [bmpWidth, bmpHeight] = bmpFileHandler.GetImageWidthAndHeight(bmpFile);
    EXPECT_EQ(expBmpWidth, bmpWidth);
    EXPECT_EQ(expBmpHeight, bmpHeight);

    bmpFile.close();
}
