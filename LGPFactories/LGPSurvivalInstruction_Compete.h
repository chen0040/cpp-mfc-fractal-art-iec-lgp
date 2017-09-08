#ifndef _H_LGP_SURVIVAL_INSTRUCTION_COMPETE_H
#define _H_LGP_SURVIVAL_INSTRUCTION_COMPETE_H

#include "LGPSurvivalInstruction.h"

class LGPSurvivalInstruction_Compete : public LGPSurvivalInstruction
{
public:
	LGPSurvivalInstruction_Compete();
	LGPSurvivalInstruction_Compete(TiXmlElement* xml_level1);
	virtual ~LGPSurvivalInstruction_Compete();

public:
	LGPSurvivalInstruction_Compete(const LGPSurvivalInstruction_Compete& rhs);
private:
	LGPSurvivalInstruction_Compete& operator=(const LGPSurvivalInstruction_Compete& rhs) { return *this; }

public:
	// Xianshun says:
	// this method return the pointer of the program that is to be deleted (loser in the competition for survival)
	virtual LGPProgram* Compete(LGPPop* lgpPop, LGPProgram* weak_program_in_current_pop, LGPProgram* child_program);
	virtual std::string ToString() const;
	virtual LGPSurvivalInstruction* Clone() const;
};
#endif