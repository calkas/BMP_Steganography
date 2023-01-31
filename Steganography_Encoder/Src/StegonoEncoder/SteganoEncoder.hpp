#ifndef STEGANO_ENCODER_HPP
#define STEGANO_ENCODER_HPP

#include <fstream>
#include <string>
#include <string_view>
#include "BmpFileHandler.hpp"

class SteganoEncoder
{
public:
    SteganoEncoder();
    ~SteganoEncoder();
    bool OpenBmpFile(std::string filePath);
    unsigned int GetMaxBytesToHide();
    bool Encode(std::string hideTxtData);
private:
    void CopyBmpHeader();
    void HideDataIntoBmp(std::string_view hideTxtData);
    bool CreateOutputBmpFile();

    BmpFileHandler bmpFileHandler;
    std::string bmpFilePath;
    std::ifstream originalBmpFileStream;
    std::fstream convBmpFileStream;
};

#endif
