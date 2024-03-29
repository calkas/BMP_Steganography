#include "SteganoEncoder.hpp"
#include <bitset>

SteganoEncoder::~SteganoEncoder()
{
    originalBmpFileStream.close();
    convBmpFileStream.close();
}

bool SteganoEncoder::OpenBmpFile(std::string filePath)
{
    originalBmpFileStream.open(filePath, std::ios::in | std::ios::binary);
    if(!originalBmpFileStream.is_open())
        return false;

    if(!bmpFileHandler.IsBmp(originalBmpFileStream))
        return false;

    bmpFilePath = filePath;
    return true;
}

unsigned int SteganoEncoder::GetMaxBytesToHide()
{
    return static_cast<unsigned int>(bmpFileHandler.GetImageSize(originalBmpFileStream) / 8) - 1;
}

bool SteganoEncoder::Encode(std::string hideTxtData)
{
    const char endOfTextSign {'\x02'};
    hideTxtData.push_back(endOfTextSign);

    const unsigned int maxBytesToHide = static_cast<unsigned int>(bmpFileHandler.GetImageSize(originalBmpFileStream) / 8);

    if(maxBytesToHide < hideTxtData.length())
        return false;

    if(!CreateOutputBmpFile())
        return false;

    CopyBmpHeader();
    HideDataIntoBmp(hideTxtData);

    convBmpFileStream.close();
    originalBmpFileStream.close();

    return true;
}

void SteganoEncoder::CopyBmpHeader() 
{
    originalBmpFileStream.seekg(0, originalBmpFileStream.beg);
    convBmpFileStream.seekg(0, convBmpFileStream.beg);

    const unsigned int bmpHeaderSize = bmpFileHandler.GetFileSizeInBytes(originalBmpFileStream) -  bmpFileHandler.GetImageSize(originalBmpFileStream);
    for(auto i = 0; i < bmpHeaderSize; i++)
    {
        convBmpFileStream.put(originalBmpFileStream.get());
    }
}

void SteganoEncoder::HideDataIntoBmp(std::string_view hideTxtData)
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

bool SteganoEncoder::CreateOutputBmpFile()
{
    auto foundPos = bmpFilePath.rfind('.');
    if(foundPos == std::string::npos)
        return false;

    std::string convBmpFilePath {bmpFilePath};
    convBmpFilePath.insert(foundPos, "Converted");
    convBmpFileStream.open(convBmpFilePath, std::fstream::out |std::fstream::binary);
    if(!convBmpFileStream.is_open())
        return false;

    return true;
}