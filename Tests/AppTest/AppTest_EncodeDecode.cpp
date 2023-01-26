#include "SteganoEncoder.hpp"
#include "SteganoDecoder.hpp"
#include <algorithm>
#include <string>
#include <gtest/gtest.h>

static const std::string PATH = "Test_ImgEncodeDecode.bmp";
static const std::string PATH_TO_CONVERTED_FILE = "Test_ImgEncodeDecodeConverted.bmp";

TEST(SteganoEncoderTest, ShouldFalseIfNumberOfBytesToHideIsGreaterThanMax)
{
    SteganoEncoder encoder(PATH);

    unsigned int maxBytesToHide = encoder.GetMaxBytesToHide() + 1;
    std::string data(maxBytesToHide, 'x');

    EXPECT_FALSE(encoder.Encode(data));
}

TEST(SteganoDecoderTest, ShouldFalseIfPathIsWrong)
{
    SteganoDecoder decoder;
    std::string wrongPath = "BlaBlaBla";
    std::string out;

    EXPECT_FALSE(decoder.Decode(wrongPath, out));
    EXPECT_TRUE(out.empty());
}

TEST(AppTest, EncodeDecodeTest)
{
    SteganoEncoder encoder(PATH);
    std::string data = "Top Secret number #6999";

    EXPECT_TRUE(encoder.Encode(data));

    SteganoDecoder decoder;
    std::string out;

    EXPECT_TRUE(decoder.Decode(PATH_TO_CONVERTED_FILE, out));
    EXPECT_EQ(out.compare(data), 0);
}
