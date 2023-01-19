#ifndef STEGANO_ENCODER_HPP
#define STEGANO_ENCODER_HPP

#include <iostream>
#include <fstream>
#include <string>
#include "BmpFileHandler.hpp"

class SteganoEncoder
{
public:
    SteganoEncoder(std::string &filePath);
    ~SteganoEncoder();
    void ShowBmpFile();
    void ShowBmpFileParameters();

    bool Hide(std::string &hideTxtData,std::string &m_ConvBmpFilePath);

private:
    void GetDataQWord(int offset,unsigned int &rOutput);

    void GetBmpFileParameters();
    bool CreateConvBmpFile(std::string &convBmpFilePath);
    void HideStringIntoBmpImageStructure(std::string &hideTxtData);

    BmpFileHandler bmpFileHandler;

    std::string m_ConvBmpFilePath;

    std::ifstream m_OriginalBmpFileStream;
    std::fstream m_ConvBmpFileStream;

    unsigned int m_maxBytesToHide;
    size_t m_nrOfBytesToHide;


    //BMP File
    // ------------------ Header ------------------
    unsigned int m_BmpFileSizeInBytes;        // File size in bytes

    // --------------- Header Info ----------------
    unsigned int m_BmpImageWidth;
    unsigned int m_BmpImageHeight;
    unsigned int m_BmpImageSize;
    unsigned int m_BmpHeaderSize;
};

#endif
