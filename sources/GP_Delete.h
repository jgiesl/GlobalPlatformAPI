#pragma once

#include "GP_Command.h"

namespace GPAPI
{

	/**
	* Enumerator of information of DELETE command
	*/
	enum DELETE_INFO {
		DELETE_INFO_DELETE_OBJECT = 0x00, 				/**< specified object will be deleted */
		DELETE_INFO_DELETE_OBJECT_AND_RELATED = 0x80,	/**< specified object and its related objects will be deleted */
	};

	/**
	* Class encapsulates DELETE command
	*/
	class GP_Delete : public GP_Command
	{
	private:

	public:
		GP_Delete();
		~GP_Delete();

		/**
		* Set information if related object will be deleted
		*
		* @param[in] nInfo
		*   information about deletion
		*
		*/
		void SetDeleteInfo(DELETE_INFO nInfo);
		/**
		* Set APDU data for DELETE command
		*
		* @param[in] pValue
		*   pointer to buffer containing APDU data
		* @param[in] cValue
		*   size of buffer
		*
		* @return
		*   TRUE if OK and FALSE if not
		*/
		bool SetDeleteData(unsigned char* pValue, unsigned long cValue);
	};

}