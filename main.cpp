#include <iostream>
#include <string>
#include "HideData_BMP_R.h"

using namespace std;

int main(int argc, char** argv) {


    string originalFilePath = "\\OriginalBmp.bmp";
    string convfilePath     = "\\ConvOriginalBmp.bmp";

    // ---------------------- TEXT TO HIDE --------------------------------

    string txtToHide = "Secret code: 0044400033338888DDEFDSEDAC9CC##";

    // --------------------------------------------------------------------

    HideData_BMP_R hideDataObj2(originalFilePath);
    hideDataObj2.ShowBmpFileParameters();
    hideDataObj2.HideTxtStringIntoBmpFile(txtToHide,convfilePath);

    string hiddenTxt2 = hideDataObj2.ShowHiddenStringFromBmpFile();
    cout<<hiddenTxt2<<endl;

    return 0;
}
