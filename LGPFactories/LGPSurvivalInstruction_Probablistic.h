#ifndef _H_LGP_SURVIVAL_INSTRUCTION_PROBABLISTIC_H
#define _H_LGP_SURVIVAL_INSTRUCTION_PROBABLISTIC_H

#include "LGPSurvivalInstruction.h"

class LGPSurvivalInstruction_Probablistic : public LGPSurvivalInstruction
{
public:
	LGPSurvivalInstruction_Probablistic();
	LGPSurvivalInstruction_Probablistic(TiXmlElement* xml_level1);
	virtual ~LGPSurvivalInstruction_Probablistic();

public:
	LGPSurvivalInstruction_Probablistic(const LGPSurvivalInstruction_Probablistic& rhs);
private:
	LGPSurvivalInstruction_Probablistic& operator=(const LGPSurvivalInstruction_Probablistic& rhs) { return *this; }

public:
	// Xianshun says:
	// this method return the pointer of the program that is to be deleted (loser in the competition for survival)
	virtual LGPProgram* Compete(LGPPop* lgpPop, LGPProgram* weak_program_in_current_pop, LGPProgram* child_program);
	virtual LGPSurvivalInstruction* Clone() const;
	virtual std::string ToString() const;

protected:
	double m_reproduction_probability;
};
#endif