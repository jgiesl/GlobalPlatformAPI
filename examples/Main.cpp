/*
 * This sample code will not work for real application! This is only example of how to use
 * GlobalPlatformAPI for implementation of specific task (in this case mutual authentication
 * and getting data from smart-card).
 */

#include "GP_SecurityInfo.h"
#include "GP_Command.h"
#include "GP_Select.h"
#include "GP_InitUpd.h"
#include "GP_ExtAuth.h"
#include "GP_GetData.h"

#include "CSmartCard.h"

int main(int argc, char* argv[])
{
	// implementation of GP_ITransmitter interface
	CSmartCard sc;
	// initialization of connection of transmitter
	if(!sc.Init())
		return -1;
	if(!sc.Connect(sc.GetReaders().at(0)))
		return -1;

	// create instance of GP_SecurityInfo for information abou secure messaging
	GPAPI::GP_SecurityInfo securityInfo;

	// SELECT command
	unsigned char AID[] = {0xA0, 0x00, 0x00, 0x00};
	GPAPI::GP_Select sel;
	// set domain AID
	sel.SetAID(AID, sizeof(AID));
	// transmit command using transmitter
	if(sel.Transmit(&sc))
	{
		// check OK state
		if(sel.CheckSW_9000())
		{
			// print response
			GPAPI::RESPONSE* resp = sel.GetResponse();

			for(int i=0; i<resp->Size; i++)
				fprintf(stderr,"%.2x ", resp->Data[i]);
			fprintf(stderr,"%.2x %.2x\r\n",resp->SW1, resp->SW2);
		}
		else
		{
			// print status words
			GPAPI::RESPONSE* resp = sel.GetResponse();
			fprintf(stderr,"%.2x %.2x\r\n", resp->SW1, resp->SW2);
			return -1;
		}
	}
	else
	{
		// print error
		fprintf(stderr,"Error: %s\r\n", sel.GetLastError());
		return -1;
	}

	// INITIALIZE UPDATE command
	unsigned char challenge[] = {0x56, 0x68, 0xA6, 0x32, 0xF6, 0xB9, 0x98, 0x05};
	GPAPI::GP_InitUpd ini;
	// set key which will be used for mutual authentication (GP_SecurityInfo is also needed)
	ini.SetKey(0, 0x00, &securityInfo);
	// set challenge
	ini.SetChallenge(challenge, sizeof(challenge));
	// transmit command using transmitter
	if(ini.Transmit(&sc))
	{
		// check OK state
		if(ini.CheckSW_9000())
		{
			// print response
			GPAPI::RESPONSE* resp = ini.GetResponse();

			for(int i=0; i<resp->Size; i++)
				fprintf(stderr,"%.2x ", resp->Data[i]);
			fprintf(stderr,"%.2x %.2x\r\n",resp->SW1, resp->SW2);
		}
		else
		{
			// print status words
			GPAPI::RESPONSE* resp = ini.GetResponse();
			fprintf(stderr,"%.2x %.2x\r\n", resp->SW1, resp->SW2);
			return -1;
		}
	}
	else
	{
		// print error
		fprintf(stderr,"Error: %s\r\n", ini.GetLastError());
		return -1;
	}

	
	// EXTERNAL AUTHENTICATION command
	unsigned char cryptogram[] = {0x48, 0xF3, 0x98, 0x04, 0x23, 0xCA, 0x84, 0x64};
	GPAPI::GP_ExtAuth auth;
	// set security level (GP_SecurityInfo is also needed)
	auth.SetSecurityLevel(GPAPI::SECURITY_LEVEL_CMAC, &securityInfo);
	// set cryptogram
	auth.SetCryptogram(cryptogram, sizeof(cryptogram));
	// secure and trasmit command using transmitter (GP_SecurityInfo is used for secure messaging)
	if(auth.Transmit(&sc, &securityInfo))
	{
		// check OK state
		if(auth.CheckSW_9000())
		{
			// print response
			GPAPI::RESPONSE* resp = auth.GetResponse();

			for(int i=0; i<resp->Size; i++)
				fprintf(stderr,"%.2x ", resp->Data[i]);
			fprintf(stderr,"%.2x %.2x\r\n",resp->SW1, resp->SW2);
		}
		else
		{
			// print status words
			GPAPI::RESPONSE* resp = auth.GetResponse();
			fprintf(stderr,"%.2x %.2x\r\n", resp->SW1, resp->SW2);
		}
	}
	else
	{
		// print error
		fprintf(stderr,"Error: %s\r\n", auth.GetLastError());
		return -1;
	}

	// GET DATA command
	GPAPI::GP_GetData get;
	// set tag of object we would like to get
	get.SetObjectTag(0x01, 0x02);
	// secure and trasmit command using transmitter
	if(get.Transmit(&sc, &securityInfo))
	{
		// check OK state
		if(get.CheckSW_9000())
		{
			// print response
			GPAPI::RESPONSE* resp = get.GetResponse();

			for(int i=0; i<resp->Size; i++)
				fprintf(stderr,"%.2x ", resp->Data[i]);
			fprintf(stderr,"%.2x %.2x\r\n",resp->SW1, resp->SW2);
		}
		else
		{
			// print status words
			GPAPI::RESPONSE* resp = get.GetResponse();
			fprintf(stderr,"%.2x %.2x\r\n", resp->SW1, resp->SW2);
		}
	}
	else
	{
		// print error
		fprintf(stderr,"Error: %s\r\n", auth.GetLastError());
		return -1;
	}

	// disconnect transmitter
	sc.Disconnect();
	sc.Uninit();

	return 0;
}

