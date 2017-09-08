#ifndef _H_PA_POP_H
#define _H_PA_POP_H

#include "../LGPComp/LGPPop.h"

class PixelArtist;

class PAPop : public LGPPop
{
public:
	PAPop();
	PAPop(LGPConfig* lgpConfig);
	virtual ~PAPop();

public:
	virtual LGPEnvironment* CreateEnvironment(LGPConfig* lgpConfig);
	virtual LGPProgram* CreateProgram(unsigned int size, LGPEnvironment* env);
	virtual PixelArtist* GetPixelArtist(unsigned int i) { return (PixelArtist*)(GetProgram(i)); }
};

#endif