#ifndef _H_LGP_MUTATION_INSTRUCTION_H
#define _H_LGP_MUTATION_INSTRUCTION_H
#include "../tinyxml/tinyxml.h"
#include <string>

class LGPPop;
class LGPProgram;

class LGPMutationInstruction
{
public:
	LGPMutationInstruction();
	LGPMutationInstruction(TiXmlElement* xml_level1);
	virtual ~LGPMutationInstruction();

public:
	virtual void Mutate(LGPPop* lgpPop, LGPProgram* child1, LGPProgram* child2);
	virtual void Mutate(LGPPop* lgpPop, LGPProgram* child)=0;
	virtual std::string ToString() const=0;
	virtual LGPMutationInstruction* Clone() const=0;
};
#endif