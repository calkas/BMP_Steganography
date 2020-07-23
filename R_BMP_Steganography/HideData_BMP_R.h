#ifndef HIDEDATA_BMP_R_H
#define HIDEDATA_BMP_R_H

#include <iostream>
#include <fstream>
#include <string>

class HideData_BMP_R
{
	public:
		HideData_BMP_R();
		~HideData_BMP_R();
		bool OpenBmpFile(std::string &filePath);
		bool CloseBmpFile();
		bool ShowBmpFile();
		bool ShowBmpFileParameters();
		
		//STEGANOGRAFIA
		bool BmpHideTxt(std::string &hideTxtData,std::string &m_ConvBmpFilePath);
		std::string ShowHiddenTxt();
		
	protected:
	private:
		bool GetDataQWord(int offset,unsigned int *pOutput);
		bool GetDataWord(int offset,unsigned int *pOutput);
		bool GetDataByte(int offset,unsigned int *pOutput);
		
		bool GetBmpFileParameters();
		
		//STEGANOGRAFIA
		bool CreateConvBmpFile(std::string &convBmpFilePath);
		bool CopyBmpHeader();
		bool HideTxtInImage(std::string &hideTxtData);
		
		
		std::string m_BmpFilePath;
		std::string m_ConvBmpFilePath;
		
		std::fstream m_OryginalBmpFILE;
		std::fstream m_ConvBmpFILE;
		bool m_statusFlag;	
		
		unsigned int m_maxBytesToHide;
		size_t m_nrOfBytesToHide;
		
		
		//BMP 
		// ------------------ Naglowek ------------------
		unsigned int m_bmpiSize; 	   // Oznacza rozmiar calego pliku w bajtach 
		unsigned int m_bmpiWidth;      // Szerokosc obrazu w pikselach 
		unsigned int m_bmpiHeight;     // Wysokosc obrazu w pikselach 	
		unsigned int m_bmpiSizeImage;  // Rozmiar samego rysunku 
		unsigned int m_bmpiHeaderSize; // Rozmiar headera 
		
		
		static const int BMP_SIZE_OFFSET         = 2;
		static const int BMP_IMAGE_WIDTH_OFFSET  = 18;
		static const int BMP_IMAGE_HEIGHT_OFFSET = 22;
		static const int BMP_SIZE_IMAGE_OFFSET   = 34;
};

#endif
