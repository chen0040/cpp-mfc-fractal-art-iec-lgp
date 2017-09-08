#ifndef _H_LGP_CROSSOVER_INSTRUCTION_H
#define _H_LGP_CROSSOVER_INSTRUCTION_H
#include "../tinyxml/tinyxml.h"
#include <string>

class LGPPop;
class LGPProgram;

class LGPCrossoverInstruction
{
public:
	LGPCrossoverInstruction();
	LGPCrossoverInstruction(TiXmlElement* xml_level1);
	virtual ~LGPCrossoverInstruction();

public:
	virtual void Crossover(LGPPop* lgpPop, LGPProgram* child1, LGPProgram* child2)=0;
	virtual std::string ToString() const=0;
	virtual LGPCrossoverInstruction* Clone() const=0;
};
#endif