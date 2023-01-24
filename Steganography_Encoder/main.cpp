#include <iostream>
#include <string>
#include "SteganoEncoder.hpp"

using namespace std;

int main(int argc, char** argv) 
{

    if(argc != 3)
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

    SteganoEncoder encoder(Path);

    string dataToHide(argv[2]);

    if(encoder.Encode(dataToHide))
    {
        cout << "Done" <<endl;
    }

    return 0;
}
