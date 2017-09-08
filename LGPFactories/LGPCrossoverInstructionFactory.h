#ifndef _H_LGP_CROSSOVER_INSTRUCTION_FACTORY_H
#define _H_LGP_CROSSOVER_INSTRUCTION_FACTORY_H

#include "LGPCrossoverInstruction.h"

class LGPCrossoverInstructionFactory
{
public:
	LGPCrossoverInstructionFactory(const char* filename);
	virtual ~LGPCrossoverInstructionFactory();

public:
	LGPCrossoverInstructionFactory(const LGPCrossoverInstructionFactory& rhs);
private:
	LGPCrossoverInstructionFactory& operator=(const LGPCrossoverInstructionFactory& rhs) { return *this; }

public:
	void Crossover(LGPPop* lgpPop, LGPProgram* child1, LGPProgram* child2);

public:
	virtual LGPCrossoverInstructionFactory* Clone() const;
	virtual std::string ToString() const;

protected:
	LGPCrossoverInstruction* m_current_crossover;
};

#endif
