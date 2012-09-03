#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "GP_Command.h"
#include "GP_StoreData.h"

namespace GPAPI
{

	GP_StoreData::GP_StoreData()
	{
		m_pRequestData.CLA = 0x80;
		m_pRequestData.INS = 0xE2;
		m_pRequestData.Le  = 0x00;
	}

	GP_StoreData::~GP_StoreData()
	{

	}

	void GP_StoreData::SetBlockInfo(BLOCK_INFO nInfo, unsigned char nBlockNumber)
	{
		m_pRequestData.P1  = nInfo;
		m_pRequestData.P2  = nBlockNumber;
	}

	bool GP_StoreData::SetDataForStore(unsigned char* pValue, unsigned long cValue)
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

		return true;
	}

}