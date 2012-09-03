#pragma once

#include "GP_SecurityInfo.h"
#include "GP_Command.h"

namespace GPAPI
{

	/**
	* Class encapsulates INIT UPDATE command
	*/
	class GP_InitUpd : public GP_Command
	{
	private:

	public:
		GP_InitUpd();
		~GP_InitUpd();

		/**
		* Set key information
		*
		* @param[in] nVersion
		*   version of the key which will be used for secure messaging
		* @param[in] nIdentifier
		*   identifier of the key which will be used for secure messaging
		* @param[in,out] pSecurityInfo
		*   pointer to security information
		*
		*/
		void SetKey(unsigned char nVersion, unsigned char nIdentifier, GPAPI::GP_SecurityInfo* pSecurityInfo);
		/**
		* Set challenge for INITIALIZE UPDATE command
		*
		* @param[in] pValue
		*   pointer to buffer containing challenge
		* @param[in] cValue
		*   size of buffer
		*
		* @return
		*   TRUE if OK and FALSE if not
		*/
		bool SetChallenge(unsigned char* pValue, unsigned long cValue);
	};

}