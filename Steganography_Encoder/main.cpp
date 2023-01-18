#include <iostream>
#include <string>
#include "SteganoEncoder.hpp"

using namespace std;

int main(int argc, char** argv) 
{

    if(argc != 2)
    {
        cout << "[Error] Wrong number of arguments" <<endl;
        return 1;
    }

    string Path(argv[1]);

    SteganoEncoder encoder(Path);

    return 0;
}
