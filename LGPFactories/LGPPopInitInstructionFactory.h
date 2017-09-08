#ifndef _H_LGP_POP_INIT_INSTRUCTION_FACTORY_H
#define _H_LGP_POP_INIT_INSTRUCTION_FACTORY_H

#include "LGPPopInitInstruction.h"

class LGPPopInitInstructionFactory
{
public:
	LGPPopInitInstructionFactory(const char* filename);
	virtual ~LGPPopInitInstructionFactory();

public:
	LGPPopInitInstructionFactory(const LGPPopInitInstructionFactory& rhs);
private:
	LGPPopInitInstructionFactory& operator=(const LGPPopInitInstructionFactory& rhs) { return *this; }

public:
	virtual LGPPopInitInstructionFactory* Clone() const;
	void Initialize(LGPPop* lgpPop);
	virtual std::string ToString() const;

public:
	LGPPopInitInstruction* m_current_instruction;
};
#endif