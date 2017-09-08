#ifndef _H_LGP_REG_INIT_INSTRUCTION_FACTORY_H
#define _H_LGP_REG_INIT_INSTRUCTION_FACTORY_H

#include "LGPRegInitInstruction.h"

class LGPRegInitInstructionFactory
{
public:
	LGPRegInitInstructionFactory(const char* filename);
	virtual ~LGPRegInitInstructionFactory();

public:
	LGPRegInitInstructionFactory(const LGPRegInitInstructionFactory& rhs);
private:
	LGPRegInitInstructionFactory& operator=(const LGPRegInitInstructionFactory& rhs) { return *this; }

public:
	void InitializeRegisters(LGPRegisterSet* reg_set, LGPConstantSet* constant_set, const LGPFitnessCase* fitness_case);
	virtual std::string ToString() const;
	virtual int GetInputInitializedRegisterCount() const;
	virtual double GetDefaultRegValue() const;

public:
	virtual LGPRegInitInstructionFactory* Clone() const;

protected:
	LGPRegInitInstruction* m_reg_initializer;
};

#endif