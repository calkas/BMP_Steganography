#ifndef HIDEDATA_BMP_R_H
#define HIDEDATA_BMP_R_H

#include <iostream>
#include <fstream>
#include <string>

class HideData_BMP_R
{
public:
    HideData_BMP_R(std::string &filePath);
    ~HideData_BMP_R();
    void ShowBmpFile();
    void ShowBmpFileParameters();

    bool HideTxtStringIntoBmpFile(std::string &hideTxtData,std::string &m_ConvBmpFilePath);
    std::string ShowHiddenStringFromBmpFile();
    bool ShowHiddenStringFromBmpFile(std::string &rOutputString, std::string &rFilePath);

private:
    void GetDataQWord(int offset,unsigned int &rOutput);
    void GetDataWord(int offset,unsigned int &rOutput);
    void GetDataByte(int offset, unsigned char &rOutput);

    void GetBmpFileParameters();
    bool IsBmpFile();
    bool CreateConvBmpFile(std::string &convBmpFilePath);
    void HideStringIntoBmpImageStructure(std::string &hideTxtData);

    std::string m_ConvBmpFilePath;

    std::fstream m_OriginalBmpFileStream;
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

    static const int BMP_FILE_SIZE_OFFSET    = 2;
    static const int BMP_IMAGE_WIDTH_OFFSET  = 18;
    static const int BMP_IMAGE_HEIGHT_OFFSET = 22;
    static const int BMP_IMAGE_SIZE_OFFSET   = 34;
};

#endif
