#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "GP_Command.h"
#include "GP_Install.h"

namespace GPAPI
{

	GP_Install::GP_Install()
	{
		m_pRequestData.CLA = 0x80;
		m_pRequestData.INS = 0xE6;
		m_pRequestData.P2  = 0x00;
		m_pRequestData.Le  = 0x00;
	}

	GP_Install::~GP_Install()
	{

	}

	bool GP_Install::SetInstallDataForLoad(unsigned char* pLoadFileAID, unsigned long cLoadFileAID, 
		unsigned char* pSecurityDomainAID, unsigned long cSecurityDomainAID, 
		unsigned char* pLoadFileHash, unsigned long cLoadFileHash, 
		unsigned char* pParameters, unsigned long cParameters, 
		unsigned char* pToken, unsigned long cToken)
	{
		int counter = 0;

		// check mandatory items
		if(pLoadFileAID == 0)
		{
			sprintf_s(m_pLastError, sizeof(m_pLastError),"Mandatory items are not set!");
			return false;
		}

		// set P1
		m_pRequestData.P1 = INSTALL_TYPE_FOR_LOAD;

		if(m_pRequestData.Data != 0)
			delete[] m_pRequestData.Data;

		// data size computation
		counter++;
		counter += cLoadFileAID;

		counter++;
		if(pSecurityDomainAID != 0 && cSecurityDomainAID != 0)
			counter += cSecurityDomainAID;

		counter++;
		if(pLoadFileHash != 0 && cLoadFileHash != 0)
			counter += cLoadFileHash;

		counter++;
		if(pParameters != 0 && cParameters != 0)
			counter += cParameters;

		counter++;
		if(pToken != 0 && cToken != 0)
			counter += cToken;

		// memory allocation
		m_pRequestData.Data = new unsigned char[counter];
		if(m_pRequestData.Data == 0)
		{
			sprintf_s(m_pLastError, sizeof(m_pLastError),"Not enough memory (size=0x%.8x)", counter);
			return false;
		}
		memset(m_pRequestData.Data, 0, counter);

		// null size
		counter = 0;

		// copy data into APDU data buffer
		memcpy(m_pRequestData.Data+counter, &cLoadFileAID, 1);
		counter++;
		memcpy(m_pRequestData.Data+counter, pLoadFileAID, cLoadFileAID);
		counter += cLoadFileAID;

		memcpy(m_pRequestData.Data+counter, &cSecurityDomainAID, 1);
		counter++;
		if(pSecurityDomainAID != 0 && cSecurityDomainAID != 0)
		{
			memcpy(m_pRequestData.Data+counter, pSecurityDomainAID, cSecurityDomainAID);
			counter += cSecurityDomainAID;
		}

		memcpy(m_pRequestData.Data+counter, &cLoadFileHash, 1);
		counter++;
		if(pLoadFileHash != 0 && cLoadFileHash != 0)
		{
			memcpy(m_pRequestData.Data+counter, pLoadFileHash, cLoadFileHash);
			counter += cLoadFileHash;
		}

		memcpy(m_pRequestData.Data+counter, &cParameters, 1);
		counter++;
		if(pParameters != 0 && cParameters != 0)
		{
			memcpy(m_pRequestData.Data+counter, pParameters, cParameters);
			counter += cParameters;
		}

		memcpy(m_pRequestData.Data+counter, &cToken, 1);
		counter++;
		if(pToken != 0 && cToken != 0)
		{
			memcpy(m_pRequestData.Data+counter, pToken, cToken);
			counter += cToken;
		}

		// set APDU Lc to size of data
		m_pRequestData.Lc = (unsigned char)counter;

		return true;
	}

	bool GP_Install::SetInstallDataForInstall(unsigned char* pLoadFileAID, unsigned long cLoadFileAID, 
		unsigned char* pModuleAID, unsigned long cModuleAID, 
		unsigned char* pApplicationAID, unsigned long cApplicationAID, 
		INSTALL_PRIVILEGES nPrivileges,
		unsigned char* pParameters, unsigned long cParameters, 
		unsigned char* pToken, unsigned long cToken)
	{
		int counter = 0;

		// check mandatory items
		if(pLoadFileAID == 0 || pModuleAID == 0 || pApplicationAID == 0 || pParameters == 0)
		{
			sprintf_s(m_pLastError, sizeof(m_pLastError),"Mandatory items are not set!");
			return false;
		}

		// set P1
		m_pRequestData.P1 = INSTALL_TYPE_FOR_INSTALL;

		if(m_pRequestData.Data != 0)
			delete[] m_pRequestData.Data;

		// data size computation
		counter++;
		counter += cLoadFileAID;
		counter++;
		counter += cModuleAID;
		counter++;
		counter += cApplicationAID;
		counter++;
		counter++;
		counter++;
		counter += cParameters;

		counter++;
		if(pToken != 0 && cToken != 0)
			counter += cToken;

		// memory allocation
		m_pRequestData.Data = new unsigned char[counter];
		if(m_pRequestData.Data == 0)
		{
			sprintf_s(m_pLastError, sizeof(m_pLastError),"Not enough memory (size=0x%.8x)", counter);
			return false;
		}
		memset(m_pRequestData.Data, 0, counter);

		// null size
		counter = 0;

		// copy data into APDU data buffer
		memcpy(m_pRequestData.Data+counter, &cLoadFileAID, 1);
		counter++;
		memcpy(m_pRequestData.Data+counter, pLoadFileAID, cLoadFileAID);
		counter += cLoadFileAID;

		memcpy(m_pRequestData.Data+counter, &cModuleAID, 1);
		counter++;
		memcpy(m_pRequestData.Data+counter, pModuleAID, cModuleAID);
		counter += cModuleAID;

		memcpy(m_pRequestData.Data+counter, &cApplicationAID, 1);
		counter++;
		memcpy(m_pRequestData.Data+counter, pApplicationAID, cApplicationAID);
		counter += cApplicationAID;

		memset(m_pRequestData.Data+counter, 1, 1);
		counter++;
		memset(m_pRequestData.Data+counter, nPrivileges, 1);
		counter++;

		memcpy(m_pRequestData.Data+counter, &cParameters, 1);
		counter++;
		memcpy(m_pRequestData.Data+counter, pParameters, cParameters);
		counter += cParameters;

		memcpy(m_pRequestData.Data+counter, &cToken, 1);
		counter++;
		if(pToken != 0 && cToken != 0)
		{
			memcpy(m_pRequestData.Data+counter, pToken, cToken);
			counter += cToken;
		}

		// set APDU Lc to size of data
		m_pRequestData.Lc = (unsigned char)counter;

		return true;
	}

	bool GP_Install::SetInstallDataForInstallAndMakeSelectable(unsigned char* pLoadFileAID, unsigned long cLoadFileAID, 
		unsigned char* pModuleAID, unsigned long cModuleAID, 
		unsigned char* pApplicationAID, unsigned long cApplicationAID, 
		INSTALL_PRIVILEGES nPrivileges,
		unsigned char* pParameters, unsigned long cParameters, 
		unsigned char* pToken, unsigned long cToken)
	{
		bool ret = SetInstallDataForInstall(pLoadFileAID, cLoadFileAID, 
			pModuleAID, cModuleAID, 
			pApplicationAID, cApplicationAID, 
			nPrivileges,
			pParameters, cParameters,
			pToken, cToken);

		// set APDU Lc to size of data
		m_pRequestData.P1 |= INSTALL_TYPE_FOR_MAKE_SELECTABLE;

		return ret;
	}

	bool GP_Install::SetInstallDataForMakeSelectable(unsigned char* pApplicationAID, unsigned long cApplicationAID, 
		INSTALL_PRIVILEGES nPrivileges,
		unsigned char* pToken, unsigned long cToken)
	{
		int counter = 0;

		// check mandatory items
		if(pApplicationAID == 0)
		{
			sprintf_s(m_pLastError, sizeof(m_pLastError),"Mandatory items are not set!");
			return false;
		}

		// set P1
		m_pRequestData.P1 = INSTALL_TYPE_FOR_MAKE_SELECTABLE;

		if(m_pRequestData.Data != 0)
			delete[] m_pRequestData.Data;

		// data size computation
		counter++;
		counter++;
		counter++;
		counter += cApplicationAID;
		counter++;
		counter++;
		counter++;

		counter++;
		if(pToken != 0 && cToken != 0)
			counter += cToken;

		// memory allocation
		m_pRequestData.Data = new unsigned char[counter];
		if(m_pRequestData.Data == 0)
		{
			sprintf_s(m_pLastError, sizeof(m_pLastError),"Not enough memory (size=0x%.8x)", counter);
			return false;
		}
		memset(m_pRequestData.Data, 0, counter);

		// null size
		counter = 0;

		// copy data into APDU data buffer
		memset(m_pRequestData.Data+counter, 0x00, 1);
		counter++;
		memset(m_pRequestData.Data+counter, 0x00, 1);
		counter++;
		memcpy(m_pRequestData.Data+counter, &cApplicationAID, 1);
		counter++;
		memcpy(m_pRequestData.Data+counter, pApplicationAID, cApplicationAID);
		counter += cApplicationAID;

		memset(m_pRequestData.Data+counter, 1, 1);
		counter++;
		memset(m_pRequestData.Data+counter, nPrivileges, 1);
		counter++;

		memset(m_pRequestData.Data+counter, 0x00, 1);
		counter++;

		memcpy(m_pRequestData.Data+counter, &cToken, 1);
		counter++;
		if(pToken != 0 && cToken != 0)
		{
			memcpy(m_pRequestData.Data+counter, pToken, cToken);
			counter += cToken;
		}

		// set APDU Lc to size of data
		m_pRequestData.Lc = (unsigned char)counter;

		return true;
	}

	bool GP_Install::SetInstallDataForExtradition(unsigned char* pSecurityDomainAID, unsigned long cSecurityDomainAID,
		unsigned char* pApplicationAID, unsigned long cApplicationAID, 
		unsigned char* pToken, unsigned long cToken)
	{
		int counter = 0;

		// check mandatory items
		if(pSecurityDomainAID == 0 || pApplicationAID == 0)
		{
			sprintf_s(m_pLastError, sizeof(m_pLastError),"Mandatory items are not set!");
			return false;
		}

		// set P1
		m_pRequestData.P1 = INSTALL_TYPE_FOR_EXTRADITION;

		if(m_pRequestData.Data != 0)
			delete[] m_pRequestData.Data;

		// data size computation
		counter++;
		counter += cSecurityDomainAID;
		counter++;
		counter++;
		counter += cApplicationAID;
		counter++;
		counter++;

		counter++;
		if(pToken != 0 && cToken != 0)
			counter += cToken;

		// memory allocation
		m_pRequestData.Data = new unsigned char[counter];
		if(m_pRequestData.Data == 0)
		{
			sprintf_s(m_pLastError, sizeof(m_pLastError),"Not enough memory (size=0x%.8x)", counter);
			return false;
		}
		memset(m_pRequestData.Data, 0, counter);

		// null size
		counter = 0;

		// copy data into APDU data buffer
		memcpy(m_pRequestData.Data+counter, &cSecurityDomainAID, 1);
		counter++;
		memcpy(m_pRequestData.Data+counter, pSecurityDomainAID, cSecurityDomainAID);
		counter += cSecurityDomainAID;

		memset(m_pRequestData.Data+counter, 0x00, 1);
		counter++;

		memcpy(m_pRequestData.Data+counter, &cApplicationAID, 1);
		counter++;
		memcpy(m_pRequestData.Data+counter, pApplicationAID, cApplicationAID);
		counter += cApplicationAID;

		memset(m_pRequestData.Data+counter, 0x00, 1);
		counter++;
		memset(m_pRequestData.Data+counter, 0x00, 1);
		counter++;

		memcpy(m_pRequestData.Data+counter, &cToken, 1);
		counter++;
		if(pToken != 0 && cToken != 0)
		{
			memcpy(m_pRequestData.Data+counter, pToken, cToken);
			counter += cToken;
		}

		// set APDU Lc to size of data
		m_pRequestData.Lc = (unsigned char)counter;

		return true;
	}

	bool GP_Install::SetInstallDataForPersonalization(unsigned char* pApplicationAID, unsigned long cApplicationAID)
	{
		int counter = 0;

		// check mandatory items
		if(pApplicationAID == 0)
		{
			sprintf_s(m_pLastError, sizeof(m_pLastError),"Mandatory items are not set!");
			return false;
		}

		// set P1
		m_pRequestData.P1 = INSTALL_TYPE_FOR_EXTRADITION;

		if(m_pRequestData.Data != 0)
			delete[] m_pRequestData.Data;

		// data size computation
		counter++;
		counter++;
		counter++;
		counter += cApplicationAID;
		counter++;
		counter++;
		counter++;

		// memory allocation
		m_pRequestData.Data = new unsigned char[counter];
		if(m_pRequestData.Data == 0)
		{
			sprintf_s(m_pLastError, sizeof(m_pLastError),"Not enough memory (size=0x%.8x)", counter);
			return false;
		}
		memset(m_pRequestData.Data, 0, counter);

		// null size
		counter = 0;

		// copy data into APDU data buffer
		memset(m_pRequestData.Data+counter, 0x00, 1);
		counter++;
		memset(m_pRequestData.Data+counter, 0x00, 1);
		counter++;

		memcpy(m_pRequestData.Data+counter, &cApplicationAID, 1);
		counter++;
		memcpy(m_pRequestData.Data+counter, pApplicationAID, cApplicationAID);
		counter += cApplicationAID;

		memset(m_pRequestData.Data+counter, 0x00, 1);
		counter++;
		memset(m_pRequestData.Data+counter, 0x00, 1);
		counter++;
		memset(m_pRequestData.Data+counter, 0x00, 1);
		counter++;

		// set APDU Lc to size of data
		m_pRequestData.Lc = (unsigned char)counter;

		return true;
	}

}
