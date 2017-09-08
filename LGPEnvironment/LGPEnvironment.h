#ifndef _H_LGP_ENVIRONMENT_H
#define _H_LGP_ENVIRONMENT_H

#include "../LGPConfig/LGPConfig.h"
#include "LGPFitnessCase.h"

class LGPRegisterSet;
class LGPOperatorSet;
class LGPConstantSet;

class LGPEnvironment
{
public:
	LGPEnvironment(LGPConfig* lgpConfig);
	virtual ~LGPEnvironment();

private:
	LGPEnvironment(const LGPEnvironment& rhs) { }
	LGPEnvironment& operator=(const LGPEnvironment& rhs) { return *this; }

public:
	virtual LGPFitnessCase* CreateFitnessCase(unsigned int iFitnessCase)=0;
	virtual unsigned int GetFitnessCaseCount() const=0;

protected:
	LGPConfig* m_lgpConfig;

public:
	LGPConfig* GetConfig() const { return m_lgpConfig; }
};

#endif