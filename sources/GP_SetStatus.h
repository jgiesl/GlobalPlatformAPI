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
	};
	/**
	* Enumerator of card and application states
	*/
	enum STATUS_TYPE {
		STATUS_TYPE_CARD_OP_READY = 0x01,						/**< card in OP_READY state */
		STATUS_TYPE_CARD_INITIALIZED = 0x07,					/**< card in INITIALIZE state */
		STATUS_TYPE_CARD_SECURED = 0x0F,						/**< card in SECURED state */
		STATUS_TYPE_CARD_CARD_LOCKED = 0x7F,					/**< card in CARD_LOCKED state */
		STATUS_TYPE_CARD_TERMINATED = 0xFF,						/**< card in TERMINATED state */

		STATUS_TYPE_APPLICATION_LOADED = 0x01,					/**< application in LOADED state */
		STATUS_TYPE_APPLICATION_INSTALLED = 0x03,				/**< application in INSTALLED state */
		STATUS_TYPE_APPLICATION_SELECTABLE = 0x07,				/**< application in SELECTABLE state */
		STATUS_TYPE_APPLICATION_PERSONALIZED = 0x0F,			/**< application in PERSONALIZED state */
		STATUS_TYPE_APPLICATION_LOCKED = 0x83					/**< application in LOCKED state */
	};

	/**
	* Class encapsulates SET STATUS command
	*/
	class GP_SetStatus : public GP_Command
	{
	private:

	public:
		GP_SetStatus();
		~GP_SetStatus();

		/**
		* Set element on the card which status will be set
		*
		* @param[in] nElement
		*   element specification
		*
		*/
		void SetCardElement(STATUS_ELEMENT nElement);
		/**
		* Set element on the card which status will be gained
		*
		* @param[in] nType
		*   type of state to which element will be set
		*
		*/
		void SetStatus(STATUS_TYPE nType);
		/**
		* Set AID of element which will be changed
		*
		* @param[in] pValue
		*   pointer to buffer containing AID
		* @param[in] cValue
		*   size of buffer
		*
		* @return
		*   TRUE if OK and FALSE if not
		*/
		bool SetAID(unsigned char* pValue, unsigned long cValue);
	};

}