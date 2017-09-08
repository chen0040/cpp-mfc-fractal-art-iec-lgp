#ifndef _H_LGP_POP_INIT_INSTRUCTION_H
#define _H_LGP_POP_INIT_INSTRUCTION_H
#include "../tinyxml/tinyxml.h"
#include <string>

class LGPPop;

class LGPPopInitInstruction
{
public:
	LGPPopInitInstruction();
	LGPPopInitInstruction(TiXmlElement* xml_element);
	virtual ~LGPPopInitInstruction();

public:
	virtual void Initialize(LGPPop* lgpPop)=0;
	virtual std::string ToString() const=0;
	virtual LGPPopInitInstruction* Clone() const=0;
};

#endif