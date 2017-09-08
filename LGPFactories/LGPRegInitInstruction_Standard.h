#ifndef _H_LGP_REG_INIT_INSTRUCTION_STANDARD_H
#define _H_LGP_REG_INIT_INSTRUCTION_STANDARD_H

#include "LGPRegInitInstruction.h"

class LGPRegInitInstruction_Standard : public LGPRegInitInstruction
{
public:
	LGPRegInitInstruction_Standard();
	LGPRegInitInstruction_Standard(TiXmlElement* xml_level1);
	virtual ~LGPRegInitInstruction_Standard();

public:
	LGPRegInitInstruction_Standard(const LGPRegInitInstruction_Standard& rhs);
private:
	LGPRegInitInstruction_Standard& operator=(const LGPRegInitInstruction_Standard& rhs) { return *this; }

public:
	virtual LGPRegInitInstruction* Clone() const;
	virtual std::string ToString() const;
	virtual void InitializeRegisters(LGPRegisterSet* reg_set, LGPConstantSet* constant_set, const LGPFitnessCase* fitness_case);
	virtual int GetInputInitializedRegisterCount() const { return static_cast<int>(m_input_copy_count); }

protected:
	unsigned int m_input_copy_count;
};
#endif