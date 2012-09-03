#pragma once

#include "GP_Command.h"

namespace GPAPI
{
	/**
	* Enumerator of information of more commands of PUT KEY
	*/
	enum PUTKEY_INFO {
		PUTKEY_INFO_MORE_COMMANDS = 0x00,	/**< more commands of PUT KEY will be followed */
		PUTKEY_INFO_LAST_COMMAND = 0x80,	/**< specify last PUT KEY command */
	};
	/**
	* Enumerator of information number of the keys to put
	*/
	enum PUTKEY_KEYNUM {
		PUTKEY_KEYNUM_SINGLE_KEY = 0x00,		/**< single key will be put */
		PUTKEY_KEYNUM_MULTIPLE_KEYS = 0x80,		/**< multiple keys will be put */
	};

	/**
	* Class encapsulates PUT KEY command
	*/
	class GP_PutKey : public GP_Command
	{
	private:

	public:
		GP_PutKey();
		~GP_PutKey();

		/**
		* Set information about keys
		*
		* @param[in] nInfo
		*   information about number of the PUT KEY commands
		* @param[in] nVersionNumber
		*   version number of the keys to put
		* @param[in] nKeyNumber
		*   specify if more keys will be put
		* @param[in] nKeyIdentifier
		*   key identifier of the keys to put
		*
		*/
		void SetKeyInfo(PUTKEY_INFO nInfo, unsigned char nVersionNumber, PUTKEY_KEYNUM nKeyNumber, unsigned char nKeyIdentifier);
		/**
		* Set APDU data for PUT KEY command
		*
		* @param[in] pValue
		*   pointer to buffer containing APDU data
		* @param[in] cValue
		*   size of buffer
		*
		* @return
		*   TRUE if OK and FALSE if not
		*/
		bool SetKeyData(unsigned char* pValue, unsigned long cValue);
	};

}