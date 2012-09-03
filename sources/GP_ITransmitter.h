#pragma once

#include "GP_SecurityInfo.h"

namespace GPAPI
{

	/**
	* Interface for APDU transmitter. Transmitter is used not only for transmitting APDU request and getting APDU response but also for securing those messages.
	*/
	class GP_ITransmitter
	{
	public:
		GP_ITransmitter() {};
		virtual ~GP_ITransmitter() {};

		/**
		* Secure APDU request using specified key
		*
		* @param[in] pSecurityInfo
		*   pointer to security information (used key, last MAC, etc.)
		* @param[in] pSend
		*   pointer to APDU request data which should be secured
		* @param[in] cSend
		*   size of APDU request data
		* @param[in,out] pRecv
		*   pointer to secured APDU request data
		* @param[in,out] cRecv
		*   size of secured APDU request data
		*
		* @return
		*   TRUE if OK and FALSE if not
		*/
		virtual bool Secure(GPAPI::GP_SecurityInfo* pSecurityInfo, const unsigned char* pSend, const unsigned long cSend, unsigned char* pRecv, unsigned long* cRecv) = 0;
		/**
		* Send APDU request and get APDU response from smart-card
		*
		* @param[in] pSend
		*   pointer to APDU request data which should be sent
		* @param[in] cSend
		*   size of APDU request data
		* @param[in,out] pRecv
		*   pointer to APDU response data returned by smart-card
		* @param[in,out] cRecv
		*   size of APDU response data
		*
		* @return
		*   TRUE if OK and FALSE if not
		*/
		virtual bool Exchange(const unsigned char* pSend, const unsigned long cSend, unsigned char* pRecv, unsigned long* cRecv) = 0;
	};

}