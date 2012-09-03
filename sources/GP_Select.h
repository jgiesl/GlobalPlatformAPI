#pragma once

#include "GP_Command.h"

namespace GPAPI
{

	/**
	* Class encapsulates SELECT command
	*/
	class GP_Select : public GP_Command
	{
	private:

	public:
		GP_Select();
		~GP_Select();

		/**
		* Set if next occurence should be returned
		*
		* @param[in] bNext
		*   next occurence will be returned if set to TRUE, first occurence will be returned if set to FALSE
		*
		*/
		void SetNextOccurence(bool bNext);
		/**
		* Set AID of element which will be selected
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