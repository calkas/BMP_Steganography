#ifndef BMP_FILE_HANDLER_HPP
#define BMP_FILE_HANDLER_HPP
#include <string>
#include <utility>

class BmpFileHandler
{
public:
    bool IsBmp(std::ifstream &file);
    unsigned GetFileSizeInBytes(std::ifstream &file);
    std::pair<unsigned, unsigned> GetImageWidthAndHeight(std::ifstream &file);
    unsigned GetImageSize(std::ifstream &file);

private:
    unsigned int GetDataFromFile(const int offset, std::ifstream &file);

    static const int BMP_FILE_SIZE_OFFSET     {2};
    static const int BMP_IMAGE_WIDTH_OFFSET  {18};
    static const int BMP_IMAGE_HEIGHT_OFFSET {22};
    static const int BMP_IMAGE_SIZE_OFFSET   {34};
};

#endif
