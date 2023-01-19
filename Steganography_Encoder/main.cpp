#include <iostream>
#include <string>
#include "SteganoEncoder.hpp"

using namespace std;

int main(int argc, char** argv) 
{

//    if(argc != 2)
//    {
//        cout << "[Error] Wrong number of arguments" <<endl;
//        return 1;
//    }

//    string Path(argv[1]);

    string Path("/home/prybka/Project/bmp/BMP_Steganography/R_BMP_Steganography/OriginalBmp.bmp");

    SteganoEncoder encoder(Path);
    encoder.ShowBmpFileParameters();
    encoder.ShowBmpFile();

    return 0;
}
