#ifndef _H_LGP_REG_INIT_INSTRUCTION_COMPLETE_INPUT_INIT_REG_H
#define _H_LGP_REG_INIT_INSTRUCTION_COMPLETE_INPUT_INIT_REG_H

#include "LGPRegInitInstruction.h"

class LGPRegInitInstruction_CompleteInputInitReg : public LGPRegInitInstruction
{
public:
	LGPRegInitInstruction_CompleteInputInitReg();
	LGPRegInitInstruction_CompleteInputInitReg(TiXmlElement* xml_level1);
	virtual ~LGPRegInitInstruction_CompleteInputInitReg();

public:
	LGPRegInitInstruction_CompleteInputInitReg(const LGPRegInitInstruction_CompleteInputInitReg& rhs);
private:
	LGPRegInitInstruction_CompleteInputInitReg& operator=(const LGPRegInitInstruction_CompleteInputInitReg& rhs) { return *this; }

public:
	virtual LGPRegInitInstruction* Clone() const;
	virtual std::string ToString() const;
	virtual void InitializeRegisters(LGPRegisterSet* reg_set, LGPConstantSet* constant_set, const LGPFitnessCase* fitness_case);
	virtual int GetInputInitializedRegisterCount() const;
};
#endif