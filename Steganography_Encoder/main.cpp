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

    SteganoEncoder encoder;
    
    if(!encoder.OpenBmpFile(Path))
    {
        cout << "[Error] Problem with input file\n";
        return 1;
    }

    string dataToHide(argv[2]);

    if(!(encoder.GetMaxBytesToHide() < dataToHide.length()))
    {
        cout<<"[Error] No enough place to hide\n";
        cout<<" - Max bytes: "<< encoder.GetMaxBytesToHide() <<"\n";
        cout<<" - Number of bytes to hide: "<<dataToHide.length()<<"\n";
        return 1;
    }

    if(!encoder.Encode(dataToHide))
    {
        cout << "[Error] Encoding process fails\n";
        return 1;
    }

    cout << "Done" <<endl;

    return 0;
}
