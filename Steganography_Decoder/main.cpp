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
    decoder.Decode(Path, out);
    cout <<"Decoded secret code: "<<out<<endl;
    return 0;
}
