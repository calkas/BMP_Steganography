#include <iostream>
#include <string>
#include "HideData_BMP_R.h"

using namespace std;

int main(int argc, char** argv) {


    cout <<argc <<endl;
    for (int i = 0; i<argc; i++)
    {
        cout << argv[i] << endl;

    }

    //string originalFilePath = string(argv[1]);



    string originalFilePath = "../R_BMP_Steganography/OriginalBmp.bmp";
    string convfilePath     = "../R_BMP_Steganography/ConvOriginalBmp.bmp";

    // ---------------------- TEXT TO HIDE --------------------------------

    string txtToHide = "Secret code: 0044400033338888DDEFDSEDAC9CC##";
    txtToHide.push_back('\x02');

    // --------------------------------------------------------------------

    HideData_BMP_R hideDataObj2(originalFilePath);
    hideDataObj2.ShowBmpFileParameters();
    hideDataObj2.HideTxtStringIntoBmpFile(txtToHide,convfilePath);

    string hiddenTxt2 = hideDataObj2.ShowHiddenStringFromBmpFile();

    for(auto i : hiddenTxt2)
    {
        cout << i <<endl;
    }
    cout<<hiddenTxt2<<endl;

    return 0;
}
