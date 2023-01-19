#include "BmpFileHandler.hpp"
#include <iostream>
#include <fstream>
#include <array>

bool BmpFileHandler::IsBmp(std::ifstream &file)
{
    if(!file.is_open())
    {
        std::cout << "[Error] Problem with processing file\n";
        return false;
    }

    char bmpSignature[2];

    file.seekg(0, file.beg);
    bmpSignature[0] = file.get();
    bmpSignature[1] = file.get();

    if((bmpSignature[0U] != 'B') && ( bmpSignature[1U] != 'M'))
    {
        return false;
    }

    file.seekg(0, file.beg);
    return true;
}

unsigned int BmpFileHandler::GetFileSizeInBytes(std::ifstream &file)
{
    return GetDataFromFile(BMP_FILE_SIZE_OFFSET, file);
}

std::pair<unsigned int, unsigned int> BmpFileHandler::GetImageWidthAndHeight(std::ifstream &file)
{
    return std::make_pair(GetDataFromFile(BMP_IMAGE_WIDTH_OFFSET, file), GetDataFromFile(BMP_IMAGE_HEIGHT_OFFSET, file));
}

unsigned int BmpFileHandler::GetImageSize(std::ifstream &file)
{
    return GetDataFromFile(BMP_IMAGE_SIZE_OFFSET, file);
}

unsigned int BmpFileHandler::GetDataFromFile(const int offset, std::ifstream &file)
{
    std::array<unsigned char, 4> bmpData;

    file.seekg(0, file.beg);
    file.seekg(offset, file.beg);

    for (size_t i = 0; i < bmpData.size(); i++)
    {
        bmpData[i] = static_cast<unsigned char>(file.get());
        std::cout << "B:" <<(unsigned int)bmpData[i] <<std::endl;
    }

    file.seekg(0, file.beg);

    return (bmpData[3] << 24) |
           (bmpData[2] << 16) |
           (bmpData[1] << 8)  |
           (bmpData[0] << 0);



}


//66 77 230 4 0 0 0 0 0 0 54 0 0 0 40 0 0 0 20 0 0 0 20 0 0 0 1 0 24 0 0 0 0 0 176 4 0 0
//------------------------------
//BMP file parameters:
// - BMP Width: 20 pix
// - BMP Height: 20 pix
// - BMP File Size in Bytes: 1254
// - BMP Header Size in Bytes: 54
// - BMP Image Size in Bytes: 1200
// - Nr of Bytes To Hide: 150
//------------------------------

