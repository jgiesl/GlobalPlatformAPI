#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "GP_Command.h"
#include "GP_Select.h"

namespace GPAPI
{

	GP_Select::GP_Select()
	{
		m_pRequestData.CLA = 0x00;
		m_pRequestData.INS = 0xA4;
		m_pRequestData.P1  = 0x04;
		m_pRequestData.P2  = 0x00;
		m_pRequestData.Le  = 0x00;
	}

	GP_Select::~GP_Select()
	{

	}

	void GP_Select::SetNextOccurence(bool bNext)
	{
		if(bNext)
			m_pRequestData.P2 = 0x02;
		else
			m_pRequestData.P2 = 0x00;
	}

	bool GP_Select::SetAID(unsigned char* pValue, unsigned long cValue)
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