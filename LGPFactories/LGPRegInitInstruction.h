#ifndef _H_LGP_REG_INIT_INSTRUCTION_H
#define _H_LGP_REG_INIT_INSTRUCTION_H

#include "../tinyxml/tinyxml.h"
#include "../LGPComp/LGPRegisterSet.h"
#include "../LGPComp/LGPConstantSet.h"
#include "../LGPEnvironment/LGPFitnessCase.h"

class LGPRegInitInstruction 
{
public:
	LGPRegInitInstruction();
	LGPRegInitInstruction(TiXmlElement* xml_level1);
	virtual ~LGPRegInitInstruction();

public:
	virtual LGPRegInitInstruction* Clone() const=0;
	virtual std::string ToString() const=0;
	virtual void InitializeRegisters(LGPRegisterSet* reg_set, LGPConstantSet* constant_set, const LGPFitnessCase* fitness_case)=0;
	virtual int GetInputInitializedRegisterCount() const=0;

public:
	double GetDefaultRegValue() const { return m_default_register_value; }

protected:
	double m_default_register_value;
};
#endif