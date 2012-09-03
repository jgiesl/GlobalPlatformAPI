#pragma once

#include "GP_Command.h"

namespace GPAPI
{

	/**
	* Class encapsulates GET DATA command
	*/
	class GP_GetData : public GP_Command
	{
	private:

	public:
		GP_GetData();
		~GP_GetData();

		/**
		* Specify object to be read
		*
		* @param[in] nTag1
		*   high order tag value of the object
		* @param[in] nTag2
		*   low order tag value of the object
		*
		*/
		void SetObjectTag(unsigned char nTag1, unsigned char nTag2);
	};

}