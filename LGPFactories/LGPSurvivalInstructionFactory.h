#ifndef _H_LGP_SURVIVAL_INSTRUCTION_FACTORY_H
#define _H_LGP_SURVIVAL_INSTRUCTION_FACTORY_H

#include "LGPSurvivalInstruction.h"

class LGPSurvivalInstructionFactory
{
public:
	LGPSurvivalInstructionFactory(const char* filename);
	virtual ~LGPSurvivalInstructionFactory();

public:
	LGPSurvivalInstructionFactory(const LGPSurvivalInstructionFactory& rhs);
private:
	LGPSurvivalInstructionFactory& operator=(const LGPSurvivalInstructionFactory& rhs) { return *this; }

public:
	// Xianshun says:
	// this method return the pointer of the program that is to be deleted (loser in the competition for survival)
	LGPProgram* Compete(LGPPop* lgpPop, LGPProgram* weak_program_in_current_pop, LGPProgram* child_program);
	virtual LGPSurvivalInstructionFactory* Clone() const;
	virtual std::string ToString() const;

protected:
	LGPSurvivalInstruction* m_current_instruction;
};
#endif