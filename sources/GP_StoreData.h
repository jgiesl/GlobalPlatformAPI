#pragma once

#include "GP_Command.h"

namespace GPAPI
{

	/**
	* Enumerator of information of STORE DATA command
	*/
	enum BLOCK_INFO {
		BLOCK_INFO_MORE_BLOCKS = 0x00, 	 		/**< block is one in a sequence of blocks */
		BLOCK_INFO_LAST_BLOCK = 0x80,	 		/**< block is one in a sequence of blocks */
	};

	/**
	* Class encapsulates STORE DATA command
	*/
	class GP_StoreData : public GP_Command
	{
	private:

	public:
		GP_StoreData();
		~GP_StoreData();

		/**
		* Set information about block to be stored
		*
		* @param[in] nInfo
		*   information about block to load
		* @param[in] nBlockNumber
		*   number of the block to be loaded
		*
		*/
		void SetBlockInfo(BLOCK_INFO nInfo, unsigned char nBlockNumber);
		/**
		* Set APDU data for STORE DATA command
		*
		* @param[in] pValue
		*   pointer to buffer containing APDU data
		* @param[in] cValue
		*   size of buffer
		*
		* @return
		*   TRUE if OK and FALSE if not
		*/
		bool SetDataForStore(unsigned char* pValue, unsigned long cValue);
	};

}