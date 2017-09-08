#include "stdafx.h"
#include "PAPop.h"
#include "PixelArtist.h"

PAPop::PAPop()
: LGPPop()
{

}

PAPop::PAPop(LGPConfig* config)
: LGPPop(config)
{

}

PAPop::~PAPop()
{

}


LGPEnvironment* PAPop::CreateEnvironment(LGPConfig* lgpConfig)
{
	//environment is not required
	return NULL;
}



LGPProgram* PAPop::CreateProgram(unsigned int size, LGPEnvironment* env)
{
	PixelArtist* lgp=new PixelArtist(this->GetConfig());
	lgp->Create(size);

	return lgp;
}