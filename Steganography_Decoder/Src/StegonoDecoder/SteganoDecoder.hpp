#ifndef STEGANO_DECODER_HPP
#define STEGANO_DECODER_HPP

#include <string>
#include <string_view>
#include <fstream>
#include "BmpFileHandler.hpp"
class SteganoDecoder
{
public:
    bool Decode(std::string_view bmpPath, std::string &out);
private:
    bool ValidateInputFile(std::ifstream &file);
    BmpFileHandler bmpFileHandler {};
};

#endif
