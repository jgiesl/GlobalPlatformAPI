#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "GP_SecurityInfo.h"

namespace GPAPI
{

	GP_SecurityInfo::GP_SecurityInfo()
	{
		m_nSecurityLevel = SECURITY_LEVEL_NO;
		m_nKeyVersion = 0;
		m_nKeyIdentifier = 0;
		memset(m_pLastCMAC, 0, sizeof(m_pLastCMAC));
	}

	GP_SecurityInfo::~GP_SecurityInfo()
	{

	}

	void GP_SecurityInfo::SetSecurityLevel(unsigned char nSecurityLevel)
	{
		m_nSecurityLevel = nSecurityLevel;
	}

	void GP_SecurityInfo::SetKeyVersion(unsigned char nKeyVersion)
	{
		m_nKeyVersion = nKeyVersion;
	}

	void GP_SecurityInfo::SetKeyIdentifier(unsigned char nKeyIdentifier)
	{
		m_nKeyIdentifier = nKeyIdentifier;
	}

	bool GP_SecurityInfo::SetLastCMAC(unsigned char* pValue, unsigned long cValue)
	{
		if(cValue != sizeof(m_pLastCMAC))
		{
			sprintf_s(m_pLastError, sizeof(m_pLastError),"Size of value does not correspond!");
			return false;
		}

		memcpy(m_pLastCMAC, pValue, cValue);

		return true;
	}

	unsigned char GP_SecurityInfo::GetSecurityLevel()
	{
		return m_nSecurityLevel;
	}

	unsigned char GP_SecurityInfo::GetKeyVersion()
	{
		return m_nKeyVersion;
	}

	unsigned char GP_SecurityInfo::GetKeyIdentifier()
	{
		return m_nKeyIdentifier;
	}

	unsigned long GP_SecurityInfo::GetLastCMAC(unsigned char* pLastCMAC)
	{
		memcpy(pLastCMAC, m_pLastCMAC, sizeof(m_pLastCMAC));

		return sizeof(m_pLastCMAC);
	}

	char* GP_SecurityInfo::GetLastError()
	{
		return m_pLastError;
	}

}