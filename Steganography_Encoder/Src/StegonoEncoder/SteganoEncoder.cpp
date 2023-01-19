#include "SteganoEncoder.hpp"
#include <assert.h>
#include <bitset>
#include <ios>

SteganoEncoder::SteganoEncoder(std::string &filePath)
{
    assert(!filePath.empty() && "[Error] File Path is empty");
    m_OriginalBmpFileStream.open(filePath.c_str(),std::ios::in | std::ios::binary );
    assert(m_OriginalBmpFileStream.is_open() && "[Error] Wrong file");
    assert(bmpFileHandler.IsBmp(m_OriginalBmpFileStream) && "[Error] Is not real BMP file");

    GetBmpFileParameters();
    m_maxBytesToHide = static_cast<unsigned int>(m_BmpImageSize / 8U);
    m_BmpHeaderSize = m_BmpFileSizeInBytes - m_BmpImageSize;

}

SteganoEncoder::~SteganoEncoder()
{
    m_OriginalBmpFileStream.close();
    m_ConvBmpFileStream.close();
}

void SteganoEncoder::GetBmpFileParameters()
{
    m_BmpFileSizeInBytes = bmpFileHandler.GetFileSizeInBytes(m_OriginalBmpFileStream);

    auto bmpWH = bmpFileHandler.GetImageWidthAndHeight(m_OriginalBmpFileStream);


    m_BmpImageWidth = bmpWH.first;
    m_BmpImageHeight = bmpWH.second;
    m_BmpImageSize = bmpFileHandler.GetImageSize(m_OriginalBmpFileStream);
}

void SteganoEncoder::ShowBmpFile()
{
    //returning to the beginning of fstream
    m_OriginalBmpFileStream.clear();
    m_OriginalBmpFileStream.seekg(0,std::ios_base::beg );

    std::cout<<"\n-------------------------------------    BMP    ------------------------------------------------\n";
    while( !m_OriginalBmpFileStream.eof() )
    {
        std::cout << m_OriginalBmpFileStream.get()<< " ";
    }
    std::cout<<"\n-------------------------------------   End of BMP   ------------------------------------------------\n";
    
    //returning to the beginning of fstream
    m_OriginalBmpFileStream.clear();
    m_OriginalBmpFileStream.seekg(0,std::ios_base::beg );
}

void SteganoEncoder::ShowBmpFileParameters()
{
    std::cout<<"\n------------------------------\nBMP file parameters:"<<std::endl;

    std::cout<<" - BMP Width: "<<m_BmpImageWidth<<" pix"<<std::endl;
    std::cout<<" - BMP Height: "<<m_BmpImageHeight<<" pix"<<std::endl;
    std::cout<<" - BMP File Size in Bytes: "<<m_BmpFileSizeInBytes<<std::endl;
    std::cout<<" - BMP Header Size in Bytes: "<< m_BmpHeaderSize<<std::endl;
    std::cout<<" - BMP Image Size in Bytes: "<<m_BmpImageSize<<std::endl;

    std::cout<<" - Nr of Bytes To Hide: "<<m_maxBytesToHide<<std::endl;
    std::cout<<"------------------------------\n"<<std::endl;
}

bool SteganoEncoder::Hide(std::string &hideTxtData, std::string &convBmpFilePath)
{
    m_nrOfBytesToHide = hideTxtData.size();

    if(m_maxBytesToHide < m_nrOfBytesToHide)
    {
        std::cout<<"Error no enough place to hide"<<std::endl;
        std::cout<<"Nr of Bytes To Hide: "<<m_maxBytesToHide<<std::endl;
        std::cout<<"String Byte size: "<<m_nrOfBytesToHide<<std::endl;
        return false;
    }

    //-------------------Create BMP File-------------------

    if(!CreateConvBmpFile(convBmpFilePath))
    {
        std::cout<<"Something wrong with Converted BMP file creation: "<<convBmpFilePath<<std::endl;
        return false;
    }
    std::cout<<"BMP file "<<convBmpFilePath<<" has been created."<<std::endl;

    std::cout<<"Text Hiding..."<<std::endl;

    //------------------- Copying BMP Header -------------------

    //returning to the beginning of fstream
    m_OriginalBmpFileStream.clear();
    m_OriginalBmpFileStream.seekg(0,std::ios_base::beg );

    m_ConvBmpFileStream.clear();
    m_ConvBmpFileStream.seekg(0,std::ios_base::beg );

    char znak;

    for(unsigned int i = 0U; i < m_BmpHeaderSize; i++)
    {
        znak = m_OriginalBmpFileStream.get();
        m_ConvBmpFileStream.put(znak);
    }

    //-------------------  Hide data in BMP  -------------------
    HideStringIntoBmpImageStructure(hideTxtData);

    std::cout<<"Done !"<<std::endl;

    m_ConvBmpFileStream.close();
    m_OriginalBmpFileStream.close();

    return true;
}

bool SteganoEncoder::CreateConvBmpFile(std::string &convBmpFilePath)
{
    if(convBmpFilePath.empty())
    {
        return false;
    }

    m_ConvBmpFilePath = convBmpFilePath;

    m_ConvBmpFileStream.open(m_ConvBmpFilePath.c_str(), std::ios::out|std::ios::binary);

    if(m_ConvBmpFileStream.bad())
    {
        return false;
    }

    return true;
}

void SteganoEncoder::HideStringIntoBmpImageStructure(std::string &hideTxtData)
{
    char stringChar;
    char tempChar;

    for(unsigned int byteIndex = 0U; byteIndex < hideTxtData.size(); byteIndex++)
    {
        stringChar = hideTxtData[byteIndex];
        std::bitset<8> bsetString(stringChar);

        for(unsigned int bitIndex = 0U; bitIndex < 8U; bitIndex++ )
        {
            tempChar = m_OriginalBmpFileStream.get();
            std::bitset<8> bsetBmp(tempChar);
            bsetBmp.set(0,bsetString[bitIndex]);
            tempChar = (char)bsetBmp.to_ulong();
            m_ConvBmpFileStream.put(tempChar);
        }
    }

    for(int bmpIndex = m_OriginalBmpFileStream.tellg(); bmpIndex < m_BmpFileSizeInBytes; bmpIndex++)
    {
        tempChar = m_OriginalBmpFileStream.get();
        m_ConvBmpFileStream.put(tempChar);
    }
}

void SteganoEncoder::GetDataQWord(int offset,unsigned int &rOutput)
{
    unsigned char byteArray[4U];

    //returning to the beginning of fstream
    m_OriginalBmpFileStream.clear();
    m_OriginalBmpFileStream.seekg(offset,std::ios_base::beg );

    for (unsigned int i = 0U; i < 4U; i++)
    {
        byteArray[i] = static_cast<unsigned char>(m_OriginalBmpFileStream.get());
    }
    rOutput = static_cast<unsigned int>( (byteArray[3U] << 24U) | (byteArray[2U] << 16U) | (byteArray[1U] << 8U) | (byteArray[0U] << 0U) );
}
