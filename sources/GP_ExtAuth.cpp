#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "GP_SecurityInfo.h"
#include "GP_Command.h"
#include "GP_ExtAuth.h"

namespace GPAPI
{

	GP_ExtAuth::GP_ExtAuth()
	{
		m_pRequestData.CLA = 0x84;
		m_pRequestData.INS = 0x82;
		m_pRequestData.P2  = 0x00;
		m_pRequestData.Lc  = 0x08;
		m_pRequestData.Le  = 0x00;
	}

	GP_ExtAuth::~GP_ExtAuth()
	{

	}

	void GP_ExtAuth::SetSecurityLevel(SECURITY_LEVEL nLevel, GPAPI::GP_SecurityInfo* pSecurityInfo)
	{
		m_pRequestData.P1  = nLevel;
		pSecurityInfo->SetSecurityLevel(nLevel);
	}

	bool GP_ExtAuth::SetCryptogram(unsigned char* pValue, unsigned long cValue)
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