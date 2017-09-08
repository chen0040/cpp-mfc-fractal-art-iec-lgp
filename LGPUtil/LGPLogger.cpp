#include "stdafx.h"
#include "LGPLogger.h"

LGPLogger::LGPLogger()
{
	debug.open("lgp_debug.txt");
}

LGPLogger::~LGPLogger()
{
	debug.close();
}

LGPLogger* LGPLogger::Instance()
{
	static LGPLogger theInstance;
	return &theInstance;
}