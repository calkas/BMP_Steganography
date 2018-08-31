#include "HideData_BMP_R.h"
#include <conio.h>
#include <bitset>
#include <ios>
#include <stdio.h>      /* printf */
#include <time.h>       /* clock_t, clock, CLOCKS_PER_SEC */

////////////////////////////////////////////////////////////////////////////
/// METHOD NAME: HideData_BMP_R::HideData_BMP_R
/// 
/// @par Full Description
/// 
/// 
/// @return Return description
/// @retval
/// 
/// 
////////////////////////////////////////////////////////////////////////////
HideData_BMP_R::HideData_BMP_R()
{
	m_statusFlag = false;
	m_bmpiWidth  = 0;
	m_bmpiHeight = 0;
}

////////////////////////////////////////////////////////////////////////////
/// METHOD NAME: HideData_BMP_R::~HideData_BMP_R
/// 
/// @par Full Description
/// 
/// 
/// @return Return description
/// @retval
/// 
/// 
////////////////////////////////////////////////////////////////////////////
HideData_BMP_R::~HideData_BMP_R()
{
	(void)CloseBmpFile();
}

////////////////////////////////////////////////////////////////////////////
/// METHOD NAME: HideData_BMP_R::OpenBmpFile
/// 
/// @par Full Description
/// 
/// @param [in] filePath Description for filePath
/// 
/// @return
/// @retval
/// 
/// 
////////////////////////////////////////////////////////////////////////////
bool HideData_BMP_R::OpenBmpFile(std::string &filePath)
{
	bool fileStatus = false;
	if(!filePath.empty())
	{
		
		m_OryginalBmpFILE.open(filePath.c_str(),std::ios::in | std::ios::binary );
		if(m_OryginalBmpFILE.is_open())
		{
			m_BmpFilePath = filePath;
			
			unsigned int data = 0;
			unsigned int data1 = 0;
			fileStatus = GetDataByte(0,&data);
			fileStatus = GetDataByte(1,&data1);
			
			if(fileStatus == false )
			{
				std::cout<<"Something wrong with BMP file: "<<m_BmpFilePath<<std::endl;
				return false;
			}
			
			if((data == 66) && (data1 == 77))
			{
				std::cout<<"Open BMP file: "<<m_BmpFilePath<<std::endl;
				fileStatus = GetBmpFileParameters();
				
				if(fileStatus == false )
				{
					std::cout<<"Something wrong with BMP file: "<<m_BmpFilePath<<std::endl;
					return false;
				}
				
				m_maxBytesToHide = static_cast<unsigned int>(m_bmpiSizeImage / 8);
				m_bmpiHeaderSize = m_bmpiSize - m_bmpiSizeImage;
				
			}
			else
			{
				std::cout<<"Error It's not a BMP file: "<<m_BmpFilePath<<std::endl;
				return false;
			}
		}
		
	}
	
	m_statusFlag = fileStatus;
	return fileStatus;
}

////////////////////////////////////////////////////////////////////////////
/// METHOD NAME: HideData_BMP_R::GetBmpFileParameters
/// 
/// @par Full Description
/// 
/// 
/// @return Return description
/// @retval
/// 
/// 
////////////////////////////////////////////////////////////////////////////
bool HideData_BMP_R::GetBmpFileParameters()
{
	bool fileStatus = true;
	fileStatus &= GetDataQWord(BMP_SIZE_OFFSET,&m_bmpiSize);
	fileStatus &= GetDataQWord(BMP_IMAGE_WIDTH_OFFSET,&m_bmpiWidth);
	fileStatus &= GetDataQWord(BMP_IMAGE_HEIGHT_OFFSET,&m_bmpiHeight);
	fileStatus &= GetDataQWord(BMP_SIZE_IMAGE_OFFSET,&m_bmpiSizeImage);
	
	return fileStatus;
}

////////////////////////////////////////////////////////////////////////////
/// METHOD NAME: HideData_BMP_R::CloseBmpFile
/// 
/// @par Full Description
/// 
/// 
/// @return Return description
/// @retval
/// 
/// 
////////////////////////////////////////////////////////////////////////////
bool HideData_BMP_R::CloseBmpFile()
{
	if(m_BmpFilePath.empty())
	{
		std::cout<<"Error No BMP file loaded"<<std::endl;
		return false;
	}
	
	m_OryginalBmpFILE.close();
	return true;
}

////////////////////////////////////////////////////////////////////////////
/// METHOD NAME: HideData_BMP_R::ShowBmpFile
/// 
/// @par Full Description
/// 
/// 
/// @return Return description
/// @retval
/// 
/// 
////////////////////////////////////////////////////////////////////////////
bool HideData_BMP_R::ShowBmpFile()
{
	if(m_BmpFilePath.empty())
	{
		std::cout<<"Error No BMP file loaded"<<std::endl;
		return false;
	}

    //returning to the beginning of fstream
    m_OryginalBmpFILE.clear();
	m_OryginalBmpFILE.seekg(0,std::ios_base::beg );
	
	std::cout<<"\n-------------------------------------    BMP    ------------------------------------------------\n";
    while( !m_OryginalBmpFILE.eof() )
    {
        std::cout << m_OryginalBmpFILE.get()<< " ";  
    }
    std::cout<<"\n-------------------------------------   End of BMP   ------------------------------------------------\n";
    
    //returning to the beginning of fstream
    m_OryginalBmpFILE.clear();
	m_OryginalBmpFILE.seekg(0,std::ios_base::beg );
	
	return true;
}

////////////////////////////////////////////////////////////////////////////
/// METHOD NAME: HideData_BMP_R::ShowBmpFileParameters
/// 
/// @par Full Description
/// 
/// 
/// @return Return description
/// @retval
/// 
/// 
////////////////////////////////////////////////////////////////////////////
bool HideData_BMP_R::ShowBmpFileParameters()
{
	if(m_BmpFilePath.empty())
	{
		std::cout<<"Error No BMP file loaded"<<std::endl;
		return false;
	}
	
	std::cout<<"\n------------------------------\nBMP file parameters:"<<std::endl;
	
	std::cout<<" - BMP Width: "<<m_bmpiWidth<<" pix"<<std::endl;
	std::cout<<" - BMP Height: "<<m_bmpiHeight<<" pix"<<std::endl;
	std::cout<<" - BMP File Size: "<<m_bmpiSize<<std::endl;
	std::cout<<" - BMP Header Size: "<< m_bmpiHeaderSize<<std::endl;
	std::cout<<" - BMP Image Size: "<<m_bmpiSizeImage<<std::endl;
	
	std::cout<<" - Nr of Bytes To Hide: "<<m_maxBytesToHide<<std::endl;
	std::cout<<"------------------------------\n"<<std::endl;
	
	return true;	
}


////////////////////////////////////////////////////////////////////////////
/// METHOD NAME: HideData_BMP_R::BmpHideTxt
/// 
/// @par Full Description
/// 
/// 
/// @return Return description
/// @retval
/// 
/// 
////////////////////////////////////////////////////////////////////////////
bool HideData_BMP_R::BmpHideTxt(std::string &hideTxtData, std::string &convBmpFilePath)
{
	if(m_BmpFilePath.empty())
	{
		std::cout<<"Error No BMP file loaded"<<std::endl;
		return false;
	}
	
	
	m_nrOfBytesToHide = hideTxtData.size();
	
	if(m_maxBytesToHide < m_nrOfBytesToHide)
	{
		std::cout<<"Error no place to hide"<<std::endl;
		std::cout<<"Nr of Bytes To Hide: "<<m_maxBytesToHide<<std::endl;
		std::cout<<"String Byte size: "<<m_nrOfBytesToHide<<std::endl;
		return false;
	}
	

	//-------------------Create BMP File-------------------
	
	if(!CreateConvBmpFile(convBmpFilePath))
	{
		std::cout<<"Something wrong with created Conv BMP file: "<<convBmpFilePath<<std::endl;
		return false;	
	}
	std::cout<<"BMP file "<<convBmpFilePath<<" has been created."<<std::endl;
	
	std::cout<<"Text Hiding..."<<std::endl;
	
	clock_t t;
	t = clock();

	//------------------- Copying BMP Header -------------------
	
	//returning to the beginning of fstream
    m_OryginalBmpFILE.clear();
	m_OryginalBmpFILE.seekg(0,std::ios_base::beg );
	
	m_ConvBmpFILE.clear();
	m_ConvBmpFILE.seekg(0,std::ios_base::beg );
	
	CopyBmpHeader();
	
	//-------------------  Hide data in BMP  -------------------
	HideTxtInImage(hideTxtData);
	
	t = clock() - t;
	
	printf ("It took me %d clicks (%f seconds).\n",t,((float)t)/CLOCKS_PER_SEC);
	
//	char znak;
//
//	while( !m_OryginalBmpFILE.eof() )
//    {
//        znak = m_OryginalBmpFILE.get();
//        m_ConvBmpFILE.put(znak);
//    }
	std::cout<<"Done !"<<std::endl;
	std::cout<<"\nClose BMP file: "<<m_ConvBmpFilePath<<std::endl;
	
	m_ConvBmpFILE.close();
	std::cout<<"Close BMP file: "<<m_BmpFilePath<<"\n"<<std::endl;
	m_OryginalBmpFILE.close();

	return true;
}

////////////////////////////////////////////////////////////////////////////
/// METHOD NAME: HideData_BMP_R::CreateConvBmpFile
/// 
/// @par Full Description
/// 
/// @param [in] convBmpFilePath Description for convBmpFilePath
/// 
/// @return Return description
/// @retval
/// 
/// 
////////////////////////////////////////////////////////////////////////////
bool HideData_BMP_R::CreateConvBmpFile(std::string &convBmpFilePath)
{
	if(convBmpFilePath.empty())
	{
		return false;
	}
	
	m_ConvBmpFilePath = convBmpFilePath;

	m_ConvBmpFILE.open(m_ConvBmpFilePath.c_str(), std::ios::out|std::ios::binary);
	
	if(m_ConvBmpFILE.bad())
	{
		return false;
	}
	
	return true;
}

////////////////////////////////////////////////////////////////////////////
/// METHOD NAME: HideData_BMP_R::CopyBmpHeader
/// 
/// @par Full Description
/// 
/// 
/// @return Return description
/// @retval
/// 
/// 
////////////////////////////////////////////////////////////////////////////
bool HideData_BMP_R::CopyBmpHeader()
{
	if(m_ConvBmpFilePath.empty())
	{
		return false;
	}
	
	if(m_BmpFilePath.empty())
	{
		
		return false;
	}
	
	char znak;
	
	for(int i = 0; i < m_bmpiHeaderSize; i++)
	{
		znak = m_OryginalBmpFILE.get();
		m_ConvBmpFILE.put(znak);
	}
	
	return true;
}

////////////////////////////////////////////////////////////////////////////
/// METHOD NAME: HideData_BMP_R::HideTxtInImage
/// 
/// @par Full Description
/// 
/// @param [in] hideTxtData Description for hideTxtData
/// 
/// @return Return description
/// @retval
/// 
/// 
////////////////////////////////////////////////////////////////////////////
bool HideData_BMP_R::HideTxtInImage(std::string &hideTxtData)
{

	if(m_ConvBmpFilePath.empty())
	{
		return false;
	}
	
	if(m_BmpFilePath.empty())
	{
		
		return false;
	}
	
	//Bez Konca linii
	
	size_t hideTxtDataSize = hideTxtData.size();
	char stringChar;
	char znak;
	
	for( int byteIndex = 0; byteIndex < hideTxtDataSize; byteIndex++ )
	{
		stringChar = hideTxtData[byteIndex];
		//std::cout<<stringChar<<std::endl;
		std::bitset<8> bsetString(stringChar);
		//std::cout<<bsetString.to_string()<<"\n----------------"<<std::endl;
		
		for( int bitIndex = 0; bitIndex < 8U; bitIndex++ )
		{
			znak = m_OryginalBmpFILE.get();
			std::bitset<8> bsetBmp(znak);
			//std::cout<<"znak = "<<bsetBmp.to_string()<<std::endl;
			bsetBmp.set(0,bsetString[bitIndex]);
			znak = (char)bsetBmp.to_ulong();
			//std::cout<<bsetBmp.to_string()<<std::endl;
			m_ConvBmpFILE.put(znak);
		}
	}
	
	
	for(int bmpIndex = m_OryginalBmpFILE.tellg(); bmpIndex < m_bmpiSize; bmpIndex++)
	{
		znak = m_OryginalBmpFILE.get();
		m_ConvBmpFILE.put(znak);	
	}
	
	return true;
}

////////////////////////////////////////////////////////////////////////////
/// METHOD NAME: HideData_BMP_R::ShowHiddenTxt
/// 
/// @par Full Description
/// 
/// 
/// @return Return description
/// @retval
/// 
/// 
////////////////////////////////////////////////////////////////////////////
std::string HideData_BMP_R::ShowHiddenTxt()
{
	std::string txtData;
	char stringChar;
	char znak;
	
	m_ConvBmpFILE.open(m_ConvBmpFilePath.c_str(), std::ios::in|std::ios::binary);
	if(m_ConvBmpFILE.is_open())
	{
	    m_ConvBmpFILE.clear();
		m_ConvBmpFILE.seekg(m_bmpiHeaderSize,std::ios_base::beg );
		std::cout<<"\n========================  Hidden Text  ========================"<<std::endl;
		
		for( int byteIndex = 0; byteIndex < m_nrOfBytesToHide; byteIndex++ )
		{
			std::bitset<8> bsetString(stringChar);

			for( int bitIndex = 0; bitIndex < 8U; bitIndex++ )
			{
				znak = m_ConvBmpFILE.get();
				std::bitset<8> bsetBmp(znak);
				
				bsetString.set(bitIndex,bsetBmp[0]);
				
			}
			
			stringChar = (char)bsetString.to_ulong();
			
			txtData += stringChar;
		}
		
		m_ConvBmpFILE.close();
	}
	else
	{
		std::cout<<"Error No BMP file loaded"<<std::endl;
	}
	
	return txtData;
}

////////////////////////////////////////////////////////////////////////////
/// METHOD NAME: HideData_BMP_R::GetDataQWord
/// 
/// @par Full Description
/// 
/// @param [in] offset Description for offset
/// @param [in] pOutput Description for pOutput
/// 
/// @return Return description
/// @retval
/// 
/// 
////////////////////////////////////////////////////////////////////////////
bool HideData_BMP_R::GetDataQWord(int offset,unsigned int *pOutput)
{
	if( ( m_BmpFilePath.empty() ) || ( pOutput == NULL ) )
	{
		return false;
	}
	
	unsigned char byteTab[4];
	
	//returning to the beginning of fstream
    m_OryginalBmpFILE.clear();
	m_OryginalBmpFILE.seekg(offset,std::ios_base::beg );
	
	for (int i = 0 ; i<4; i++)
	{
		byteTab[i] = static_cast<unsigned char>(m_OryginalBmpFILE.get());
	}
	//ConvertToQWord
	*pOutput = static_cast<unsigned int>( (byteTab[3] << 24U) | (byteTab[2] << 16U) | (byteTab[1] << 8U) | (byteTab[0] << 0U) );
	
	return true;	
}

////////////////////////////////////////////////////////////////////////////
/// METHOD NAME: HideData_BMP_R::GetDataWord
/// 
/// @par Full Description
/// 
/// @param [in] offset Description for offset
/// @param [in] pOutput Description for pOutput
/// 
/// @return Return description
/// @retval
/// 
/// 
////////////////////////////////////////////////////////////////////////////
bool HideData_BMP_R::GetDataWord(int offset,unsigned int *pOutput)
{
	if( ( m_BmpFilePath.empty() ) || ( pOutput == NULL ) )
	{
		return false;
	}
	
	unsigned char byteTab[2];
	
	//returning to the beginning of fstream
    m_OryginalBmpFILE.clear();
	m_OryginalBmpFILE.seekg(offset,std::ios_base::beg );
	
	for (int i = 0 ; i<2; i++)
	{
		byteTab[i] = static_cast<unsigned char>(m_OryginalBmpFILE.get());
	}
	//Convert to word
	*pOutput = static_cast<unsigned int>( (byteTab[1] << 8U) | (byteTab[0] << 0U ) );

	return true;	
}

////////////////////////////////////////////////////////////////////////////
/// METHOD NAME: HideData_BMP_R::GetDataByte
/// 
/// @par Full Description
/// 
/// @param [in] offset Description for offset
/// @param [in] pOutput Description for pOutput
/// 
/// @return Return description
/// @retval
/// 
/// 
////////////////////////////////////////////////////////////////////////////
bool HideData_BMP_R::GetDataByte(int offset,unsigned int *pOutput)
{
	if( ( m_BmpFilePath.empty() ) || ( pOutput == NULL ) )
	{
		return false;
	}
	
	unsigned char byte;
	
	//returning to the beginning of fstream
    m_OryginalBmpFILE.clear();
	m_OryginalBmpFILE.seekg(offset,std::ios_base::beg );
	
	byte = static_cast<unsigned char>(m_OryginalBmpFILE.get());

	//Convert to word
	*pOutput = static_cast<unsigned int>(byte);
	
	return true;	
}







