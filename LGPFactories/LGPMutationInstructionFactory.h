#ifndef _H_LGP_MUTATION_INSTRUCTION_FACTORY_H
#define _H_LGP_MUTATION_INSTRUCTION_FACTORY_H
#include <string>

#include "LGPMutationInstruction.h"

class LGPMutationInstructionFactory 
{
public:
	LGPMutationInstructionFactory(const char* filename);
	virtual ~LGPMutationInstructionFactory();

public:
	virtual LGPMutationInstructionFactory* Clone() const;

public:
	LGPMutationInstructionFactory(const LGPMutationInstructionFactory& rhs);
private:
	LGPMutationInstructionFactory& operator=(const LGPMutationInstructionFactory& rhs) { return *this; }

public:
	void Mutate(LGPPop* pop, LGPProgram* child1, LGPProgram* child2);
	void Mutate(LGPPop* pop, LGPProgram* child);
	virtual std::string ToString() const;

private:
	LGPMutationInstruction* m_current_macro_mutation;
};
#endif