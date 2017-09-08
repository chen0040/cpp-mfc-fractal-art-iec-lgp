#ifndef _H_LGP_INSTRUCTION_H
#define _H_LGP_INSTRUCTION_H

#include <string>
#include "../LGPEnvironment/LGPFitnessCase.h"
#include "LGPOperator.h"
#include "LGPRegister.h"

class LGPProgram;

class LGPInstruction
{
public:
	LGPInstruction(LGPProgram* lgp);
	virtual ~LGPInstruction();

public:
	LGPInstruction(const LGPInstruction& rhs);
private:
	LGPInstruction& operator=(const LGPInstruction& rhs) { return *this; }

public:
	virtual void Create();
	virtual void Create(LGPOperator* op, LGPRegister* operand1, LGPRegister* operand2, LGPRegister* destination_register);

public:
	virtual LGPInstruction* Clone() const { return new LGPInstruction(*this); }

public:
	bool IsConditionalConstruct() const { return m_op->IsConditionalConstruct(); }
	void SetOwnership(LGPProgram* lgp);

public:
	unsigned int GetDestinationRegisterIndex() const { return m_destination_register->GetRegisterIndex(); }
	unsigned int GetOperand1RegisterIndex() const { return m_operand1->GetRegisterIndex(); }
	unsigned int GetOperand2RegisterIndex() const { return m_operand2->GetRegisterIndex(); }
	unsigned int GetOperatorRegisterIndex() const { return m_op->GetOperatorIndex(); }
	bool IsOperand1ConstantRegister() const { return m_operand1->IsConstant(); }
	bool IsOperand2ConstantRegister() const { return m_operand2->IsConstant(); }
public:
	void SetDestinationRegister(LGPRegister* lgpRegister) { m_destination_register=lgpRegister; }

public:
	virtual void MutateOperator();
	virtual void MutateRegister(double p_const=0.5);
	virtual void MutateConstant(double standard_deviation=1);
public:
	int GetConstantRegisterIndex() const;

protected:
	bool m_bIsStructuralIntron;
public:
	bool IsStructuralIntron() const { return m_bIsStructuralIntron; }
	void SetStructuralIntronFlag(bool bIntron) { m_bIsStructuralIntron=bIntron; }

public:
	virtual std::string ToString() const;

public:
	virtual int Execute(LGPFitnessCase* lgpFitnessCase) const;
	virtual void UpdateFitnessCase(LGPFitnessCase* lgpFitnessCase) const;

protected:
	LGPProgram* m_lgp;

public:
	LGPOperator* m_op;
	LGPRegister* m_operand1;
	LGPRegister* m_operand2;
	LGPRegister* m_destination_register;
};

#endif