#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "GP_Command.h"
#include "GP_SetStatus.h"

namespace GPAPI
{

	GP_SetStatus::GP_SetStatus()
	{
		m_pRequestData.CLA = 0x80;
		m_pRequestData.INS = 0xF0;
		m_pRequestData.Le  = 0x00;
	}

	GP_SetStatus::~GP_SetStatus()
	{

	}

	void GP_SetStatus::SetCardElement(STATUS_ELEMENT nElement)
	{
		m_pRequestData.P1  = nElement;
	}

	void GP_SetStatus::SetStatus(STATUS_TYPE nType)
	{
		m_pRequestData.P2  = nType;
	}

	bool GP_SetStatus::SetAID(unsigned char* pValue, unsigned long cValue)
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