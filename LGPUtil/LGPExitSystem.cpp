#include "stdafx.h"
#include "LGPExitSystem.h"
#include <cstdlib>
#include <iostream>
#include "LGPLogger.h"
#include "../LGPConstants/LGPFlags.h"
#include <cassert>
#include <sstream>

void LGPExitSystem(const char* fname, const char* ename)
{
	std::ostringstream oss;
	oss << "An error has occurred in the LGP System..." << std::endl;
	oss << "Source: " << fname << std::endl;
	oss << "Error: " << ename << std::endl;

	AfxMessageBox(CA2CT(oss.str().c_str()), MB_OK);

	lgpLogger << "An error has occurred in the LGP System..." << std::endl;
	lgpLogger << "Source: " << fname << std::endl;
	lgpLogger << "Error: " << ename << std::endl;

#ifdef LGP_BUILD_DEBUG
	assert(false);
#else
	std::exit(0);
#endif
}