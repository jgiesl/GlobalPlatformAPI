#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "GP_Command.h"
#include "GP_GetStatus.h"

namespace GPAPI
{

	GP_GetStatus::GP_GetStatus()
	{
		m_pRequestData.CLA = 0x80;
		m_pRequestData.INS = 0xF2;
		m_pRequestData.Le  = 0x00;
	}

	GP_GetStatus::~GP_GetStatus()
	{

	}

	void GP_GetStatus::SetCardElement(STATUS_ELEMENT nElement)
	{
		m_pRequestData.P1  = nElement;
	}

	void GP_GetStatus::SetResponseType(STATUS_RESPONSE nType)
	{
		m_pRequestData.P2  = nType;
	}

	bool GP_GetStatus::SetSearchCriteria(unsigned char* pValue, unsigned long cValue)
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