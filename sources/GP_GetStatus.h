#pragma once

#include "GP_Command.h"

namespace GPAPI
{
	/**
	* Enumerator of card elements
	*/
	enum STATUS_ELEMENT {
		STATUS_ELEMENT_ISSUER_SECURITY_DOMAIN = 0x80,			/**< issuer security domain */
		STATUS_ELEMENT_APPLICATIONS = 0x40,						/**< applications */
		STATUS_ELEMENT_LOAD_FILES = 0x20,						/**< load files */
		STATUS_ELEMENT_LOAD_FILES_EXECUTABLE_MODULES = 0x10		/**< load files executable modules */
	};
	/**
	* Enumerator of responses of GET STATUS command
	*/
	enum STATUS_RESPONSE {
		STATUS_RESPONSE_FIRST = 0x00,				/**< get first or all occurences */
		STATUS_RESPONSE_NEXT = 0x01,				/**< get next occurences */
		STATUS_RESPONSE_COMMON_TYPE = 0x00,			/**< common type of response structure */
		STATUS_RESPONSE_TLV_TYPE = 0x02				/**< tag-length-value type of response structure */
	};

	/**
	* Class encapsulates GET STATUS command
	*/
	class GP_GetStatus : public GP_Command
	{
	private:

	public:
		GP_GetStatus();
		~GP_GetStatus();

		/**
		* Set element on the card which status will be gained
		*
		* @param[in] nElement
		*   element specification
		*
		*/
		void SetCardElement(STATUS_ELEMENT nElement);
		/**
		* Set response type after GET STATUS command is send
		*
		* @param[in] nType
		*   type of response
		*
		*/
		void SetResponseType(STATUS_RESPONSE nType);
		/**
		* Set searching criteria most commonly AID
		*
		* @param[in] pValue
		*   pointer to buffer containing search criteria
		* @param[in] cValue
		*   size of buffer
		*
		* @return
		*   TRUE if OK and FALSE if not
		*/
		bool SetSearchCriteria(unsigned char* pValue, unsigned long cValue);
	};

}