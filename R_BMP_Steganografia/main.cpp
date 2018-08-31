#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <bitset>

#include "HideData_BMP_R.h"
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
using namespace std;



void fun()
{
	cout<<"------------------\n";
	int byteTab[4] = {2,6,14,30};
	
	bitset<8> bset1;
	
//	bset1.set(4);
//	cout<<bset1<<endl;
	
	for(int i =0; i<4; i++)
	{
		
		bitset<8> bset1(byteTab[i]);
		bset1.set(0,0);
		cout<<byteTab[i]<<" - "<<bset1<<" - "<<bset1.to_ulong()<<endl;
	}
	
}


int main(int argc, char** argv) {
	
	//Plik tylko do odczytu
//	ifstream plikBMP("OriginalBmp.bmp");

	string filePath = "OriginalBmp.bmp";
	string convfilePath = "ConvOriginalBmp.bmp";
	
	string nazwa = "HELLO";
	
	HideData_BMP_R hideDataObj;
	hideDataObj.OpenBmpFile(filePath);
	hideDataObj.ShowBmpFile();
	hideDataObj.ShowBmpFileParameters();
	hideDataObj.BmpHideTxt(nazwa,convfilePath);
	
	
	
	std::string binary = bitset<8>(4).to_string();
	cout<<binary<<endl;
	
	std::bitset<8> bset1(binary);
	cout<<bset1.to_ulong()<<endl;
	
	//fun();
	
	unsigned int a = 69;
	
	cout<<"string wielkosc: "<<nazwa.size()<<endl;
	cout<<"string literka: "<<nazwa[0]<<endl;
	
	
	
	
	
	
	
	
	
	return 0;
}
