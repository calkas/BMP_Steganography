#include <iostream>
#include <string>
#include "SteganoDecoder.hpp"

using namespace std;

int main(int argc, char** argv) {

    if(argc != 2)
    {
        cout << "[Error] Wrong number of arguments" <<endl;
        return 1;
    }

    string Path(argv[1]);

    if(Path.empty())
    {
        cout << "[Error] Empty path file\n";
        return 1;
    }

    SteganoDecoder decoder;
    string out;
    if(!decoder.Decode(Path, out))
    {
        cout << "[Error] Decoding problem\n";
        return 1;
    }
    cout <<"Decoded secret code: "<<out<<"\n";
    return 0;
}
