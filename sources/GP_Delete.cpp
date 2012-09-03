#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "GP_Command.h"
#include "GP_Delete.h"

namespace GPAPI
{

	GP_Delete::GP_Delete()
	{
		m_pRequestData.CLA = 0x80;
		m_pRequestData.INS = 0xE4;
		m_pRequestData.P1  = 0x00;
		m_pRequestData.Le  = 0x00;
	}

	GP_Delete::~GP_Delete()
	{

	}

	void GP_Delete::SetDeleteInfo(DELETE_INFO nInfo)
	{
		m_pRequestData.P2 = nInfo;
	}

	bool GP_Delete::SetDeleteData(unsigned char* pValue, unsigned long cValue)
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