#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <winscard.h>
#include "CSmartCard.h"

CSmartCard::CSmartCard()
{

}

CSmartCard::~CSmartCard()
{
	Uninit();
}

bool CSmartCard::Init()
{
	bool ret = false;
	LONG result;

	LPTSTR pReaders, pReader;

	// context
	result = SCardEstablishContext(SCARD_SCOPE_USER,  NULL, NULL, &m_hContext);
	if(result != SCARD_S_SUCCESS)
	{
		fprintf(stderr,"error: SCardEstablishContext\n");
		goto FINISH;
	}

	// get readers
	m_dwReaders = SCARD_AUTOALLOCATE;
	result = SCardListReaders(m_hContext, NULL, (LPTSTR)&pReaders, &m_dwReaders);
	if(result != SCARD_S_SUCCESS)
	{
		fprintf(stderr,"error: SCardListReaders\n");
		goto FINISH;
	}

	pReader = pReaders;
	while(*pReader != '\0')
	{
		std::wstring tmp = (wchar_t*)pReaders;
		m_pReadersList.push_back(tmp);
		pReader = pReader + wcslen((wchar_t *)pReader) + 1;
	}

	// free the memory
	result = SCardFreeMemory(m_hContext, pReaders);
	if(result != SCARD_S_SUCCESS)
	{
		fprintf(stderr,"error: SCardFreeMemory\n");
		goto FINISH;
	}

	ret = true;

FINISH:
	return ret;
}

void CSmartCard::Uninit()
{
	m_pReadersList.clear();
	SCardReleaseContext(m_hContext);
}

std::vector<std::wstring> CSmartCard::GetReaders()
{
	return m_pReadersList;
}

bool CSmartCard::Connect(std::wstring szReader)
{
	if(SCardConnect(m_hContext, (LPCTSTR)szReader.c_str(), SCARD_SHARE_SHARED, SCARD_PROTOCOL_T0 | SCARD_PROTOCOL_T1, &m_hCard, &m_dwProtocol) != SCARD_S_SUCCESS)
		return false;

	return true;
}

void CSmartCard::Disconnect()
{
	SCardDisconnect(m_hCard, SCARD_LEAVE_CARD);
}

// implementation of GP_ITransmitter virtual method for securing APDU request
bool CSmartCard::Secure(GPAPI::GP_SecurityInfo* pSecurityInfo, const unsigned char* pInput, const unsigned long cInput, unsigned char* pOutput, unsigned long* cOutput)
{
	fprintf(stderr,"SECURITY LEVEL: %d\r\n", pSecurityInfo->GetSecurityLevel());
	fprintf(stderr,"KEY VERSION: %d\r\n", pSecurityInfo->GetKeyVersion());
	fprintf(stderr,"KEY IDENTIFIER: %d\r\n", pSecurityInfo->GetKeyIdentifier());

	// simulates C-MAC computation (will not work for real application)
	unsigned char CMAC[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

	// add C-MAC
	*cOutput = cInput+sizeof(CMAC);
	memcpy(pOutput+cInput, CMAC, sizeof(CMAC));
	memcpy(pOutput, pInput, cInput);

	// modify Lc
	pOutput[4] = (char)(*cOutput-5);

	return true;
}

// implementation of GP_ITransmitter virtual method for exchanging APDU messages
bool CSmartCard::Exchange(const unsigned char* pInput, const unsigned long cInput, unsigned char* pOutput, unsigned long* cOutput)
{
	// print request
	fprintf(stderr, ">> ");
	for(int i=0; i<(int)cInput; i++)
		fprintf(stderr,"%.2x ", pInput[i]);
	fprintf(stderr,"\r\n");

	// send request to smart-card and get its response
	if(SCardTransmit(m_hCard, SCARD_PCI_T1, pInput, cInput, NULL, pOutput, cOutput) != SCARD_S_SUCCESS)
		return false;

	// print response
	fprintf(stderr, "<< ");
	for(int i=0; i<(int)cOutput; i++)
		fprintf(stderr,"%.2x ", pOutput[i]);
	fprintf(stderr,"\r\n");

	return true;
}
