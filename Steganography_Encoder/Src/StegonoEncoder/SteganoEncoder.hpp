#ifndef STEGANO_ENCODER_HPP
#define STEGANO_ENCODER_HPP

#include <fstream>
#include <string>
#include "BmpFileHandler.hpp"

class SteganoEncoder
{
public:
    SteganoEncoder(const std::string &filePath);
    ~SteganoEncoder();
    bool Encode(std::string &dataToHide);
    unsigned int GetMaxBytesToHide();

private:
    void HideDataIntoBmp(std::string &hideTxtData);

    BmpFileHandler bmpFileHandler;
    std::ifstream originalBmpFileStream;
    std::string convBmpFilePath;
    std::fstream convBmpFileStream;

    const char endOfTextSign {'\x02'};
};

#endif
