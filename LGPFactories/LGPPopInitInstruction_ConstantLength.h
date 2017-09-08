#ifndef _H_LGP_POP_INIT_INSTRUCTION_CONSTANT_LENGTH_H
#define _H_LGP_POP_INIT_INSTRUCTION_CONSTANT_LENGTH_H

#include "LGPPopInitInstruction.h"

class LGPPopInitInstruction_ConstantLength : public LGPPopInitInstruction
{
public:
	LGPPopInitInstruction_ConstantLength();
	LGPPopInitInstruction_ConstantLength(TiXmlElement* xml_level1);
	virtual ~LGPPopInitInstruction_ConstantLength();

public:
	LGPPopInitInstruction_ConstantLength(const LGPPopInitInstruction_ConstantLength& rhs);
private:
	LGPPopInitInstruction_ConstantLength& operator=(const LGPPopInitInstruction_ConstantLength& rhs) { return *this; }

public:
	virtual void Initialize(LGPPop* lgpPop);
	virtual std::string ToString() const;
	virtual LGPPopInitInstruction* Clone() const;

private:
	unsigned int m_constant_program_length; 
};

#endif