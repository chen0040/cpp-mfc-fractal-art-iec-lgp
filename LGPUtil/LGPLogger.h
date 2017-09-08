#ifndef _H_LGP_LOGGER_H
#define _H_LGP_LOGGER_H

#include <fstream>
#include <iostream>

class LGPLogger
{
public:
	virtual ~LGPLogger();
	static LGPLogger* Instance();

private:
	LGPLogger();
	LGPLogger(const LGPLogger& rhs) { }
	LGPLogger& operator=(const LGPLogger& rhs) { return *this; }

public:
	std::ofstream debug;
};

#define lgpLogger (LGPLogger::Instance()->debug)
#endif