#include <iostream>
#include <string>
#include <bitset>

#include "HideData_BMP_R.h"
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
using namespace std;



void fun()
{
	cout<<"------------------\n";
	int byteTab[4] = {1,6,14,30};
	
	bitset<8> bset1;
	
//	bset1.set(4);
//	cout<<bset1<<endl;
	
	for(int i =0; i<4; i++)
	{
		
		bitset<8> bset1(byteTab[i]);
		bset1.set(0,0);
		char znak = (char)bset1.to_ulong();
		cout<<znak<<endl;
		cout<<byteTab[i]<<" - "<<bset1<<" - "<<bset1.to_ulong()<<endl;
	}
	
}


int main(int argc, char** argv) {
	

	string originalFilePath = "OriginalBmp.bmp";
	string convfilePath     = "ConvOriginalBmp.bmp";
	
	// ---------------------- TEXT TO HIDE --------------------------------
	
	string txtToHide = "Tajny kod: 0044400033338888DDEFDSEDAC9CC##";
	
	// --------------------------------------------------------------------
	
	HideData_BMP_R hideDataObj;
	hideDataObj.OpenBmpFile(originalFilePath);
	//hideDataObj.ShowBmpFile();
	hideDataObj.ShowBmpFileParameters();
	hideDataObj.BmpHideTxt(txtToHide,convfilePath);
	
	
	string hiddenTxt = hideDataObj.ShowHiddenTxt();
	
	
	cout<<hiddenTxt<<endl;
	
	return 0;
}
