#include "SteganoDecoder.hpp"
#include <bitset>

bool SteganoDecoder::Decode(std::string_view bmpPath, std::string &out)
{
    std::ifstream file(std::string(bmpPath), std::ifstream::in | std::ifstream::binary);

    if(!ValidateInputFile(file))
        return false;
 
    out.clear();
    
    const unsigned int bmpHeaderSize = bmpFileHandler.GetFileSizeInBytes(file) - bmpFileHandler.GetImageSize(file);
    constexpr char endOfTextSign {'\x02'};
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

bool SteganoDecoder::ValidateInputFile(std::ifstream &file)
{
    if(!file.is_open())
        return false;
    
    if(!bmpFileHandler.IsBmp(file))
    {
        file.close();
        return false;
    }
    return true;
}
