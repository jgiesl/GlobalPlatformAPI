#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "GP_Command.h"
#include "GP_GetData.h"

namespace GPAPI
{

	GP_GetData::GP_GetData()
	{
		m_pRequestData.CLA = 0x80;
		m_pRequestData.INS = 0xCA;
		m_pRequestData.Le  = 0x00;
	}

	GP_GetData::~GP_GetData()
	{

	}

	void GP_GetData::SetObjectTag(unsigned char nTag1, unsigned char nTag2)
	{
		m_pRequestData.P1  = nTag1;
		m_pRequestData.P2  = nTag2;
	}

}