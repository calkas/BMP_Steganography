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
    bool OpenBmpFile(const std::string &filePath);
    unsigned int GetMaxBytesToHide();
    bool Encode(std::string_view dataToHide);
private:
    void HideDataIntoBmp(std::string &hideTxtData);
    bool CreateOutputBmpFile();

    BmpFileHandler bmpFileHandler;
    std::string bmpFilePath;
    std::ifstream originalBmpFileStream;
    std::fstream convBmpFileStream;
    
    const char endOfTextSign {'\x02'};
};

#endif
