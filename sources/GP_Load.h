#pragma once

#include "GP_Command.h"

namespace GPAPI
{

	/**
	* Enumerator of information of LOAD command
	*/
	enum LOAD_INFO {
		LOAD_INFO_MORE_BLOCKS = 0x00,	 		/**< block is one in a sequence of blocks */
		LOAD_INFO_LAST_BLOCK = 0x80, 			/**< block is last in a sequence of blocks*/
	};

	/**
	* Class encapsulates LOAD command
	*/
	class GP_Load : public GP_Command
	{
	private:

	public:
		GP_Load();
		~GP_Load();

		/**
		* Set information about block to be loaded
		*
		* @param[in] nInfo
		*   information about block to load
		* @param[in] nBlockNumber
		*   number of the block to be loaded
		*
		*/
		void SetLoadInfo(LOAD_INFO nInfo, unsigned char nBlockNumber);
		/**
		* Set APDU data for LOAD command
		*
		* @param[in] pValue
		*   pointer to buffer containing APDU data
		* @param[in] cValue
		*   size of buffer
		*
		* @return
		*   TRUE if OK and FALSE if not
		*/
		bool SetLoadData(unsigned char* pValue, unsigned long cValue);
	};

}