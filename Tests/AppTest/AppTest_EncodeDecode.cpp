#include "SteganoEncoder.hpp"
#include "SteganoDecoder.hpp"
#include <algorithm>
#include <string>
#include <gtest/gtest.h>

static const std::string PATH {"Test_ImgEncodeDecode.bmp"};
static const std::string PATH_TO_CONVERTED_FILE {"Test_ImgEncodeDecodeConverted.bmp"};
static const std::string FAKE_PATH {"BlahBlah"};

TEST(SteganoEncoderTest, ShouldFalseIfInputFileDoesNotExist)
{
    SteganoEncoder encoder;
    EXPECT_FALSE(encoder.OpenBmpFile(FAKE_PATH));
}

TEST(SteganoEncoderTest, ShouldFalseIfNumberOfBytesToHideIsGreaterThanMax)
{
    SteganoEncoder encoder;
    EXPECT_TRUE(encoder.OpenBmpFile(PATH));

    unsigned int maxBytesToHide = encoder.GetMaxBytesToHide() + 1;
    std::string data(maxBytesToHide, 'x');

    EXPECT_FALSE(encoder.Encode(data));
}

TEST(SteganoDecoderTest, ShouldFalseIfPathIsWrong)
{
    SteganoDecoder decoder;
    std::string out;

    EXPECT_FALSE(decoder.Decode(FAKE_PATH, out));
    EXPECT_TRUE(out.empty());
}

TEST(AppTest, EncodeDecodeTest)
{
    SteganoEncoder encoder;
    std::string data {"Top Secret number #6999"};

    EXPECT_TRUE(encoder.OpenBmpFile(PATH));
    EXPECT_TRUE(encoder.Encode(data));

    SteganoDecoder decoder;
    std::string out;

    EXPECT_TRUE(decoder.Decode(PATH_TO_CONVERTED_FILE, out));
    EXPECT_EQ(out.compare(data), 0);
}
