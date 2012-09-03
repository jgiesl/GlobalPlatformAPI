#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "GP_Command.h"
#include "GP_Load.h"

namespace GPAPI
{

	GP_Load::GP_Load()
	{
		m_pRequestData.CLA = 0x80;
		m_pRequestData.INS = 0xE8;
		m_pRequestData.Le  = 0x00;
	}

	GP_Load::~GP_Load()
	{

	}

	void GP_Load::SetLoadInfo(LOAD_INFO nInfo, unsigned char nBlockNumber)
	{
		m_pRequestData.P1  = nInfo;
		m_pRequestData.P2  = nBlockNumber;
	}

	bool GP_Load::SetLoadData(unsigned char* pValue, unsigned long cValue)
	{
		if(m_pRequestData.Data != 0)
			delete[] m_pRequestData.Data;

		m_pRequestData.Data = new unsigned char[cValue];
		if(m_pRequestData.Data == 0)
		{
			sprintf_s(m_pLastError, sizeof(m_pLastError),"Not enough memory (size=0x%.8x)", cValue);
			return false;
		}
		memset(m_pRequestData.Data, 0, cValue);
		memcpy(m_pRequestData.Data, pValue, cValue);

		m_pRequestData.Lc = (unsigned char)cValue;

		return true;
	}

}