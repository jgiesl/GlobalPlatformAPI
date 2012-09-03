#pragma once

namespace GPAPI
{
	/**
	* Enumerator of information of security level
	*/
	enum SECURITY_LEVEL {
		SECURITY_LEVEL_NO = 0x00,					/**< no security level */
		SECURITY_LEVEL_CMAC = 0x01,					/**< data in APDU request will be C-MACed */
		SECURITY_LEVEL_CMAC_CDECRYPTION = 0x03,		/**< data in APDU request will be C-MACed and response needs to be C-DECRYPTed */
		SECURITY_LEVEL_RMAC = 0x10					/**< data in APDU response will be R-MACed */
	};

	/**
	* Class for handling security information
	*/
	class GP_SecurityInfo
	{
	private:
		unsigned char m_nSecurityLevel;
		unsigned char m_nKeyVersion;
		unsigned char m_nKeyIdentifier;
		unsigned char m_pLastCMAC[8];

		char m_pLastError[256];

	public:
		GP_SecurityInfo();
		~GP_SecurityInfo();

		/**
		* Set security level of secure messaging
		*
		* @param[in] nSecurityLevel
		*   security level
		*
		*/
		void SetSecurityLevel(unsigned char nSecurityLevel);
		/**
		* Set version of key used for secure messaging
		*
		* @param[in] nKeyVersion
		*   version of used key
		*
		*/
		void SetKeyVersion(unsigned char nKeyVersion);
		/**
		* Set identifier of key used for secure messaging
		*
		* @param[in] nKeyIdentifier
		*   identifier of used key
		*
		*/
		void SetKeyIdentifier(unsigned char nKeyIdentifier);
		/**
		* Set last C-MAC from APDU response
		*
		* @param[in] pValue
		*   pointer to buffer containing C-MAC
		* @param[in] cValue
		*   size of buffer
		*
		* @return
		*   TRUE if OK and FALSE if not
		*/
		bool SetLastCMAC(unsigned char* pValue, unsigned long cValue);

		/**
		* Get security level property
		*
		* @return char
		*   security level
		*/
		unsigned char GetSecurityLevel();
		/**
		* Get version of used key
		*
		* @return
		*   version of used key
		*/
		unsigned char GetKeyVersion();
		/**
		* Get identifier of used key
		*
		* @return
		*   identifier of used key
		*/
		unsigned char GetKeyIdentifier();
		/**
		* Get last C-MAC
		*
		* @param[in,out] pValue
		*   pointer to buffer where last C-MAC will be stored
		*
		* @return
		*   real size of last C-MAC
		*/
		unsigned long GetLastCMAC(unsigned char* pValue);
		/**
		* Get last error when any operation was not successfull
		*
		* @return
		*   description of error
		*/
		char* GetLastError();

	};

}