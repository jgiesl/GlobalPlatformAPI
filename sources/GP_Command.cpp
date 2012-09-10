#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "GP_Command.h"
#include "GP_SecurityInfo.h"
#include "GP_ITransmitter.h"

namespace GPAPI
{

	GP_Command::GP_Command()
	{
		memset(&m_pRequestData, 0, sizeof(REQUEST));
		memset(&m_pResponseData, 0, sizeof(RESPONSE));

		memset(m_pLastError, 0, sizeof(m_pLastError));
	}

	GP_Command::~GP_Command()
	{
		// clear data
		if(m_pRequestData.Data != 0)
		{
			delete[] m_pRequestData.Data;
			m_pRequestData.Data = 0;
		}
		if(m_pResponseData.Data != 0)
		{
			delete[] m_pResponseData.Data;
			m_pResponseData.Data = 0;
		}
	}

	unsigned long GP_Command::SerializeRequestData(unsigned char* pOutput)
	{
		unsigned long ncounter = 0;

		// CLA
		if(pOutput != 0)
			memcpy(pOutput+ncounter, &m_pRequestData.CLA, sizeof(m_pRequestData.CLA));
		ncounter += sizeof(m_pRequestData.CLA);

		// INS
		if(pOutput != 0)
			memcpy(pOutput+ncounter, &m_pRequestData.INS, sizeof(m_pRequestData.INS));
		ncounter += sizeof(m_pRequestData.INS);

		// P1
		if(pOutput != 0)
			memcpy(pOutput+ncounter, &m_pRequestData.P1, sizeof(m_pRequestData.P1));
		ncounter += sizeof(m_pRequestData.P1);

		// P2
		if(pOutput != 0)
			memcpy(pOutput+ncounter, &m_pRequestData.P2, sizeof(m_pRequestData.P2));
		ncounter += sizeof(m_pRequestData.P2);

		// Lc
		if(pOutput != 0)
			memcpy(pOutput+ncounter, &m_pRequestData.Lc, sizeof(m_pRequestData.Lc));
		ncounter += sizeof(m_pRequestData.Lc);

		// Data
		if(pOutput != 0)
			memcpy(pOutput+ncounter, m_pRequestData.Data, m_pRequestData.Lc);
		ncounter += m_pRequestData.Lc;

		// Le
		if(pOutput != 0)
			memcpy(pOutput+ncounter, &m_pRequestData.Le, sizeof(m_pRequestData.Le));
		ncounter += sizeof(m_pRequestData.Le);

		return ncounter;
	}

	unsigned long GP_Command::SerializeResponseData(unsigned char* pOutput)
	{
		unsigned long ncounter = 0;

		// Data
		if(pOutput != 0)
			memcpy(pOutput+ncounter, m_pResponseData.Data, m_pResponseData.Size);
		ncounter += m_pResponseData.Size;

		// SW1
		if(pOutput != 0)
			memcpy(pOutput+ncounter, &m_pResponseData.SW1, sizeof(m_pResponseData.SW1));
		ncounter += sizeof(m_pResponseData.SW1);

		// SW2
		if(pOutput != 0)
			memcpy(pOutput+ncounter, &m_pResponseData.SW2, sizeof(m_pResponseData.SW2));
		ncounter += sizeof(m_pResponseData.SW2);

		return ncounter;
	}

	bool GP_Command::SetRequest(REQUEST* pRequest)
	{
		m_pRequestData.CLA = pRequest->CLA;
		m_pRequestData.INS = pRequest->INS;
		m_pRequestData.P1  = pRequest->P1;
		m_pRequestData.P2  = pRequest->P2;
		m_pRequestData.Lc  = pRequest->Lc;

		if(m_pRequestData.Data != 0)
			delete[] m_pRequestData.Data;

		m_pRequestData.Data = new unsigned char[m_pRequestData.Lc];
		if(m_pRequestData.Data == 0)
		{
			sprintf_s(m_pLastError, sizeof(m_pLastError),"Not enough memory (size=0x%.8x)", m_pRequestData.Lc);
			return false;
		}
		memcpy(m_pRequestData.Data, pRequest->Data, m_pRequestData.Lc);

		m_pRequestData.Le  = pRequest->Le;

		return true;
	}

	bool GP_Command::SetResponse(unsigned char* pResponse, unsigned long cResponse)
	{
		// set Data
		m_pResponseData.Size = (unsigned char)cResponse-sizeof(m_pResponseData.SW1)-sizeof(m_pResponseData.SW2);
		m_pResponseData.Data = new unsigned char[m_pResponseData.Size];
		if(m_pResponseData.Data == 0)
		{
			sprintf_s(m_pLastError, sizeof(m_pLastError),"Not enough memory (size=0x%.8x)", m_pResponseData.Size);
			return false;
		}
		memcpy(m_pResponseData.Data, pResponse, m_pResponseData.Size);

		// set SW1, SW2
		m_pResponseData.SW1 = pResponse[m_pResponseData.Size];
		m_pResponseData.SW2 = pResponse[m_pResponseData.Size+sizeof(m_pResponseData.SW1)];

		return true;
	}

	bool GP_Command::Transmit(GPAPI::GP_ITransmitter* pTransmitter, GP_SecurityInfo* pSecurityInfo /* = 0 */)
	{
		unsigned char preq[270] = {0};
		unsigned long creq = 0;
		unsigned char pres[270] = {0};
		unsigned long cres = sizeof(pres);

		// modify CLA if secure messaging is required
		if(pSecurityInfo != 0)
			m_pRequestData.CLA |= 0x04;

		// get APDU request data
		creq = SerializeRequestData(preq);

		if(pSecurityInfo != 0)
		{
			unsigned char ptmp[270] = {0};
			unsigned long ctmp;

			// interface method for securing request data (ie. MACing, ENCrypting)
			if(!pTransmitter->Secure(pSecurityInfo, preq, creq-1, ptmp, &ctmp))
			{
				sprintf_s(m_pLastError, sizeof(m_pLastError),"ITransmitter::Secure failed!");
				return false;
			}

			// store last CMAC
			if((pSecurityInfo->GetSecurityLevel() & SECURITY_LEVEL_CMAC) == SECURITY_LEVEL_CMAC)
				pSecurityInfo->SetLastCMAC(ptmp+ctmp-8, 8);

			creq = ctmp+1;
			memcpy(preq, ptmp, creq-1);
			preq[creq-1] = m_pRequestData.Le;
		}

		// interface method for send APDU data to smart-card
		if(!pTransmitter->Exchange(preq, creq, pres, &cres))
		{
			sprintf_s(m_pLastError, sizeof(m_pLastError),"ITransmitter::Exchange failed!");
			return false;
		}

		// set APDU response data
		SetResponse(pres,cres);

		return true;
	}

	bool GP_Command::CheckSW_9000()
	{
		if(m_pResponseData.SW1 == 0x90 && m_pResponseData.SW2 == 0x00)
			return true;

		return false;
	}
	
	REQUEST* GP_Command::GetRequest()
	{
		return &m_pRequestData;
	}

	RESPONSE* GP_Command::GetResponse()
	{
		return &m_pResponseData;
	}

	char* GP_Command::GetLastError()
	{
		return m_pLastError;
	}

}