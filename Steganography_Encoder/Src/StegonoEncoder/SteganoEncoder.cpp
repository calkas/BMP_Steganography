#include "SteganoEncoder.hpp"
#include <iostream>
#include <assert.h>
#include <bitset>

SteganoEncoder::SteganoEncoder(std::string &filePath) :
    bmpFileHandler(),
    originalBmpFileStream(filePath.c_str(), std::ios::in | std::ios::binary),
    convBmpFilePath("Converted.bmp"),
    convBmpFileStream()
{
    assert(originalBmpFileStream.is_open() && "[Error] Wrong file");
    assert(bmpFileHandler.IsBmp(originalBmpFileStream) && "[Error] Is not real BMP file");

    auto foundPos = filePath.rfind('.');
    if(foundPos != std::string::npos)
    {
        convBmpFilePath = filePath;
        convBmpFilePath.insert(foundPos, "Converted");
    }
}

SteganoEncoder::~SteganoEncoder()
{
    originalBmpFileStream.close();
    convBmpFileStream.close();
}

bool SteganoEncoder::Encode(std::string &dataToHide)
{
    std::string hideTxtData = dataToHide;
    hideTxtData.push_back(endOfTextSign);

    const unsigned int numberBytesToHide = static_cast<unsigned int>(hideTxtData.size());
    const unsigned int maxBytesToHide = static_cast<unsigned int>(bmpFileHandler.GetImageSize(originalBmpFileStream) / 8U);
    const unsigned int bmpHeaderSize = bmpFileHandler.GetFileSizeInBytes(originalBmpFileStream) -  bmpFileHandler.GetImageSize(originalBmpFileStream);

    if(maxBytesToHide < numberBytesToHide)
    {
        std::cout<<"Error no enough place to hide\n";
        std::cout<<"Max bytes: "<<maxBytesToHide<<"\n";
        std::cout<<"Number of bytes to hide: "<<numberBytesToHide<<"\n";
        return false;
    }

    //-------------------Create BMP File-------------------
    convBmpFileStream.open(convBmpFilePath.c_str(), std::fstream::out |std::fstream::binary);
    if(convBmpFileStream.bad())
    {
        std::cout<<"Something wrong with Converted BMP file creation: "<<convBmpFilePath<<std::endl;
        return false;
    }

    std::cout<<"BMP file "<<convBmpFilePath<<" has been created."<<std::endl;
    std::cout<<"Text Hiding...\n";

    //------------------- Copying BMP Header -------------------

    //returning to the beginning of fstream
    originalBmpFileStream.seekg(0, originalBmpFileStream.beg);
    convBmpFileStream.seekg(0, convBmpFileStream.beg);

    for(auto i = 0; i < bmpHeaderSize; i++)
    {
        convBmpFileStream.put(originalBmpFileStream.get());
    }
    //-------------------  Hide data in BMP  -------------------
    HideDataIntoBmp(hideTxtData);

    convBmpFileStream.close();
    originalBmpFileStream.close();

    return true;
}


void SteganoEncoder::HideDataIntoBmp(std::string &hideTxtData)
{
    const unsigned int numberBytesToHide = static_cast<unsigned int>(hideTxtData.size());

    for(auto byteIndex = 0; byteIndex<numberBytesToHide; byteIndex++)
    {
        char stringChar = hideTxtData[byteIndex];
        std::bitset<8> bsetString(stringChar);

        for(auto bitIndex = 0; bitIndex < 8; bitIndex++)
        {
            char tempChar = originalBmpFileStream.get();
            std::bitset<8> bsetBmp(tempChar);
            bsetBmp.set(0,bsetString[bitIndex]);
            tempChar = (char)bsetBmp.to_ulong();
            convBmpFileStream.put(tempChar);
        }
    }

    const unsigned int bmpFileSizeInBytes = bmpFileHandler.GetFileSizeInBytes(originalBmpFileStream);

    for(int bmpIndex = originalBmpFileStream.tellg(); bmpIndex<bmpFileSizeInBytes; bmpIndex++)
    {
        convBmpFileStream.put(originalBmpFileStream.get());
    }
}
