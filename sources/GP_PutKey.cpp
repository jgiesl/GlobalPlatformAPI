#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "GP_Command.h"
#include "GP_PutKey.h"

namespace GPAPI
{

	GP_PutKey::GP_PutKey()
	{
		m_pRequestData.CLA = 0x80;
		m_pRequestData.INS = 0xD8;
		m_pRequestData.Le  = 0x00;
	}

	GP_PutKey::~GP_PutKey()
	{

	}

	void GP_PutKey::SetKeyInfo(PUTKEY_INFO nInfo, unsigned char nVersionNumber, PUTKEY_KEYNUM nKeyNumber, unsigned char nKeyIdentifier)
	{
		m_pRequestData.P1  = nInfo|nVersionNumber;
		m_pRequestData.P2  = nKeyNumber|nKeyIdentifier;
	}

	bool GP_PutKey::SetKeyData(unsigned char* pValue, unsigned long cValue)
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