#ifndef STEGANO_DECODER_HPP
#define STEGANO_DECODER_HPP

#include <string>

class SteganoDecoder
{
public:
    bool Decode(const std::string &bmpPath, std::string &out);
private:
    const char endOfTextSign {'\x02'};
};

#endif
