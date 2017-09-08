#ifndef _H_LGP_SURVIVAL_INSTRUCTION_H
#define _H_LGP_SURVIVAL_INSTRUCTION_H

#include "../tinyxml/tinyxml.h"
#include <string>

class LGPPop;
class LGPProgram;

class LGPSurvivalInstruction
{
public:
	LGPSurvivalInstruction();
	LGPSurvivalInstruction(TiXmlElement* xml_level1);

	virtual ~LGPSurvivalInstruction();

public:
	// Xianshun says:
	// this method return the pointer of the program that is to be deleted (loser in the competition for survival)
	virtual LGPProgram* Compete(LGPPop* lgpPop, LGPProgram* weak_program_in_current_pop, LGPProgram* child_program)=0; 
	virtual LGPSurvivalInstruction* Clone() const=0;
	virtual std::string ToString() const=0;
};
#endif