#include "SteganoDecoder.hpp"
#include <iostream>
#include <fstream>
#include <bitset>
#include "BmpFileHandler.hpp"

bool SteganoDecoder::Decode(const std::string &bmpPath, std::string &out)
{
    std::ifstream file(bmpPath.c_str(), std::ifstream::in | std::ifstream::binary);
    if(!file.is_open())
    {
        std::cout<<"Error No Bmp file loaded\n";
        return false;
    }

    out.clear();
    BmpFileHandler bmpFileHandler;
    const unsigned int bmpHeaderSize = bmpFileHandler.GetFileSizeInBytes(file) - bmpFileHandler.GetImageSize(file);
    file.seekg(bmpHeaderSize, std::ios_base::beg);

    for(auto byteId = 0; byteId < bmpFileHandler.GetImageSize(file); ++byteId)
    {
        char stringChar;
        std::bitset<8> bsetString(stringChar);
        for(int bitIndex = 0U; bitIndex < 8; bitIndex++ )
        {
            char tempChar = file.get();
            std::bitset<8> bsetBmp(tempChar);
            bsetString.set(bitIndex,bsetBmp[0]);
        }

        stringChar = static_cast<char>(bsetString.to_ulong());
        if(stringChar == endOfTextSign)
        {
            break;
        }

        out.push_back(stringChar);
    }

    file.close();
    return true;
}
