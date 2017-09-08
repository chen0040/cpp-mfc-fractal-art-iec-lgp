#ifndef _H_LGP_POP_INIT_INSTRUCTION_VARIABLE_LENGTH_H
#define _H_LGP_POP_INIT_INSTRUCTION_VARIABLE_LENGTH_H

#include "LGPPopInitInstruction.h"

class LGPPopInitInstruction_VariableLength : public LGPPopInitInstruction
{
public:
	LGPPopInitInstruction_VariableLength();
	LGPPopInitInstruction_VariableLength(TiXmlElement* xml_level1);
	virtual ~LGPPopInitInstruction_VariableLength();

public:
	LGPPopInitInstruction_VariableLength(const LGPPopInitInstruction_VariableLength& rhs);
private:
	LGPPopInitInstruction_VariableLength& operator=(const LGPPopInitInstruction_VariableLength& rhs) { return *this; }

public:
	virtual void Initialize(LGPPop* lgpPop);
	virtual std::string ToString() const;
	virtual LGPPopInitInstruction* Clone() const;

private:
	unsigned int m_iInitialMinProgLength;
public:
	unsigned int GetInitialMinProgLength() const { return m_iInitialMinProgLength; }

private:
	unsigned int m_iInitialMaxProgLength; 
public:
	unsigned int GetInitialMaxProgLength() const { return m_iInitialMaxProgLength; }
};

#endif