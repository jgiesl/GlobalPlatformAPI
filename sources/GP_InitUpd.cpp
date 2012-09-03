#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "GP_SecurityInfo.h"
#include "GP_Command.h"
#include "GP_InitUpd.h"

namespace GPAPI
{

	GP_InitUpd::GP_InitUpd()
	{
		m_pRequestData.CLA = 0x80;
		m_pRequestData.INS = 0x50;
		m_pRequestData.Lc  = 0x08;
		m_pRequestData.Le  = 0x00;
	}

	GP_InitUpd::~GP_InitUpd()
	{

	}

	void GP_InitUpd::SetKey(unsigned char nVersion, unsigned char nIdentifier, GPAPI::GP_SecurityInfo* pSecurityInfo)
	{
		m_pRequestData.P1  = nVersion;
		m_pRequestData.P2  = nIdentifier;

		pSecurityInfo->SetKeyVersion(nVersion);
		pSecurityInfo->SetKeyIdentifier(nIdentifier);
	}

	bool GP_InitUpd::SetChallenge(unsigned char* pValue, unsigned long cValue)
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