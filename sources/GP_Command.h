#pragma once

#include "GP_SecurityInfo.h"
#include "GP_ITransmitter.h"

namespace GPAPI
{
	/**
	* Structure containing header and data for APDU request
	*/
	typedef struct
	{
		unsigned char CLA;		/**< class */
		unsigned char INS;		/**< instruction */
		unsigned char P1;		/**< first parameter */
		unsigned char P2;		/**< second parameter */
		unsigned char Lc;		/**< size of data */
		unsigned char* Data;	/**< data buffer */
		unsigned char Le;		/**< maximal size of response data */
	} REQUEST;

	/**
	* Structure containing data and status words as an APDU response
	*/
	typedef struct
	{
		unsigned char Size;		/**< size of Data buffer */
		unsigned char* Data;	/**< APDU response data without status words */
		unsigned char SW1;		/**< first status word */
		unsigned char SW2;		/**< second status word */
	} RESPONSE;

	/**
	* Base class encapsulates APDU commands
	*/
	class GP_Command
	{
	private:
		unsigned long SerializeRequestData(unsigned char* pOutput);
		unsigned long SerializeResponseData(unsigned char* pOutput);
		bool SetResponse(unsigned char* pResponse, unsigned long cResponse);

	protected:
		/**
		* Structure containing request data
		*/
		REQUEST  m_pRequestData;
		/**
		* Structure containing response data
		*/
		RESPONSE m_pResponseData;
		/**
		* Buffer containing last error message
		*/
		char m_pLastError[256];

	public:
		GP_Command();
		~GP_Command();

		/**
		* Set APDU request
		*
		* @param[in] pRequest
		*   pointer to structure containing all necessary items of APDU request
		*
		* @return
		*   TRUE if OK and FALSE if not
		*/
		bool SetRequest(REQUEST* pRequest);
		/**
		* Transmitting APDU request
		*
		* @param[in] pTransmitter
		*   custom implementation of transmitter
		* @param[in] pSecurityInfo
		*   instance containing security information. Secure messaging will not be used if parameter is set to null
		*
		* @return
		*   TRUE if OK and FALSE if not
		*/
		bool Transmit(GPAPI::GP_ITransmitter* pTransmitter, GPAPI::GP_SecurityInfo* pSecurityInfo = 0);
		/**
		* Check status words SW1=0x90 and SW2=0x00 after getting APDU response from transmitter
		*
		* @return
		*   TRUE if OK and FALSE if not
		*/
		bool CheckSW_9000();
		/**
		* Get pointer to REQUEST structure containing APDU request
		*
		* @return
		*   structure contains all necessary items of APDU request
		*/
		REQUEST* GetRequest();
		/**
		* Get pointer to RESPONSE structure after transmitting APDU request
		*
		* @return
		*   structure contains returned data and status words
		*/
		RESPONSE* GetResponse();
		/**
		* Get last error when any operation was not successfull
		*
		* @return
		*   description of error
		*/
		char* GetLastError();
	};

}