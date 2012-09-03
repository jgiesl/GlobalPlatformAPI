#pragma once

#include "GP_SecurityInfo.h"
#include "GP_Command.h"

namespace GPAPI
{

	/**
	* Class encapsulates EXTERNAL AUTHENTICATE command
	*/
	class GP_ExtAuth : public GP_Command
	{
	private:

	public:
		GP_ExtAuth();
		~GP_ExtAuth();

		/**
		* Set security level and modify security information for future purposes
		*
		* @param[in] nLevel
		*   security level specification
		* @param[in,out] pSecurityInfo
		*   pointer to security information
		*
		*/
		void SetSecurityLevel(SECURITY_LEVEL nLevel, GPAPI::GP_SecurityInfo* pSecurityInfo);
		/**
		* Set cryptogram for EXTERNAL AUTHENTICATION command
		*
		* @param[in] pValue
		*   pointer to buffer containing cryptogram
		* @param[in] cValue
		*   size of buffer
		*
		* @return
		*   TRUE if OK and FALSE if not
		*/
		bool SetCryptogram(unsigned char* pValue, unsigned long cValue);
	};

}