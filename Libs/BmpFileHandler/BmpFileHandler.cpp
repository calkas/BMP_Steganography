#include "BmpFileHandler.hpp"
#include <fstream>
#include <array>

bool BmpFileHandler::IsBmp(std::ifstream &file)
{
    if(!file.is_open())
        return false;

    std::array<char, 2>bmpSignature;

    auto currentPos = file.tellg();

    file.seekg(0, file.beg);
    bmpSignature[0] = file.get();
    bmpSignature[1] = file.get();

    if((bmpSignature[0] != 'B') && (bmpSignature[1] != 'M'))
        return false;

    file.seekg(currentPos, file.beg);
    return true;
}

unsigned int BmpFileHandler::GetFileSizeInBytes(std::ifstream &file)
{
    return GetDataFromFile(BMP_FILE_SIZE_OFFSET, file);
}

std::pair<unsigned int, unsigned int> BmpFileHandler::GetImageWidthAndHeight(std::ifstream &file)
{
    return std::make_pair(GetDataFromFile(BMP_IMAGE_WIDTH_OFFSET, file),
                          GetDataFromFile(BMP_IMAGE_HEIGHT_OFFSET, file));
}

unsigned int BmpFileHandler::GetImageSize(std::ifstream &file)
{
    return GetDataFromFile(BMP_IMAGE_SIZE_OFFSET, file);
}

unsigned int BmpFileHandler::GetDataFromFile(const int offset, std::ifstream &file)
{
    std::array<unsigned char, 4> bmpData;

    auto currentPos = file.tellg();

    file.seekg(0, file.beg);
    file.seekg(offset, file.beg);

    for(auto i = 0; i < bmpData.size(); i++)
    {
        bmpData[i] = static_cast<unsigned char>(file.get());
    }

    file.seekg(currentPos, file.beg);

    return (bmpData[3] << 24) |
           (bmpData[2] << 16) |
           (bmpData[1] << 8)  |
           (bmpData[0] << 0);
}
