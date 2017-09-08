#ifndef _H_PA_OPERATOR_SET_H
#define _H_PA_OPERATOR_SET_H

#include "../LGPComp/LGPOperatorSet.h"

class PAOperatorSet : public LGPOperatorSet
{
public:
	PAOperatorSet();
	virtual ~PAOperatorSet();

public:
	virtual LGPOperatorSet* Clone() const { return new PAOperatorSet(*this); }
};

#endif
