#include "stdafx.h"
#include "LGPInstruction.h"
#include <sstream>
#include "../LGPUtil/LGPRandom.h"
#include "LGPProgram.h"
#include "LGPRegisterSet.h"
#include "LGPConstantSet.h"
#include "LGPOperatorSet.h"
#include "../LGPConstants/LGPFlags.h"
#include "../LGPUtil/LGPExitSystem.h"

LGPInstruction::LGPInstruction(LGPProgram* lgp)
: m_lgp(lgp)
, m_op(NULL)
, m_destination_register(NULL)
, m_operand1(NULL)
, m_operand2(NULL)
, m_bIsStructuralIntron(false)
{

}

LGPInstruction::~LGPInstruction()
{
	if(m_op != NULL)
	{
		m_op=NULL;
	}
	if(m_operand1 != NULL)
	{
		m_operand1=NULL;
	}
	if(m_operand2 != NULL)
	{
		m_operand2=NULL;
	}
	if(m_destination_register != NULL)
	{
		m_destination_register=NULL;
	}
}

LGPInstruction::LGPInstruction(const LGPInstruction& rhs)
{
	m_lgp=rhs.m_lgp;
	m_bIsStructuralIntron=rhs.m_bIsStructuralIntron;
	m_op=rhs.m_op;
	m_operand1=rhs.m_operand1;
	m_operand2=rhs.m_operand2;
	m_destination_register=rhs.m_destination_register;
}

void LGPInstruction::SetOwnership(LGPProgram* lgp)
{
#ifdef LGP_DEBUG
	if(this->GetOperatorRegisterIndex() >= this->m_lgp->GetOperatorSet()->GetOperatorCount())
	{
		LGPExitSystem("LGPInstruction::SetOwnership(LGPProgram* lgp)", "this->GetOperatorRegisterIndex() >= this->m_lgp->GetOperatorSet()->GetOperatorCount()");
	}
#endif
	m_op=lgp->GetOperatorSet()->GetOperator(this->GetOperatorRegisterIndex());

	if(this->IsOperand1ConstantRegister())
	{
		m_operand1=lgp->GetConstantSet()->GetRegister(this->GetOperand1RegisterIndex());
	}
	else
	{
		m_operand1=lgp->GetRegisterSet()->GetRegister(this->GetOperand1RegisterIndex());
	}

	if(this->IsOperand2ConstantRegister())
	{
		m_operand2=lgp->GetConstantSet()->GetRegister(this->GetOperand2RegisterIndex());
	}
	else
	{
		m_operand2=lgp->GetRegisterSet()->GetRegister(this->GetOperand2RegisterIndex());
	}

	m_destination_register=lgp->GetRegisterSet()->GetRegister(this->GetDestinationRegisterIndex());

	m_lgp=lgp;
}

int LGPInstruction::Execute(LGPFitnessCase* lgpFitnessCase) const
{
	return m_op->Execute(m_operand1, m_operand2, m_destination_register);
}

void LGPInstruction::UpdateFitnessCase(LGPFitnessCase* lgpFitnessCase) const
{
	lgpFitnessCase->Update(m_op, m_operand1, m_operand2, m_destination_register, m_lgp->GetRegisterSet());
}

void LGPInstruction::Create(LGPOperator* op, LGPRegister* operand1, LGPRegister* operand2, LGPRegister* destination_register)
{
	m_op=op;
	m_operand1=operand1;
	m_operand2=operand2;
	m_destination_register=destination_register;
}

void LGPInstruction::Create()
{
	m_op=m_lgp->GetOperatorSet()->GetRandomOperator();

	double p_const=0.5;
	double r=lgpRandom.nextDouble();
	if(r < p_const)
	{
		m_operand1=m_lgp->GetConstantSet()->GetRandomRegister();
	}
	else
	{
		m_operand1=m_lgp->GetRegisterSet()->GetRandomRegister();
	}
	if(m_operand1->IsConstant())
	{
		m_operand2=m_lgp->GetRegisterSet()->GetRandomRegister();
	}
	else
	{
		r=lgpRandom.nextDouble();
		if(r < p_const)
		{
			m_operand2=m_lgp->GetConstantSet()->GetRandomRegister();
		}
		else
		{
			m_operand2=m_lgp->GetRegisterSet()->GetRandomRegister();
		}
	}

	m_destination_register=m_lgp->GetRegisterSet()->GetRandomRegister();
}

void LGPInstruction::MutateConstant(double standard_deviation)
{
	if(m_operand1->IsConstant())
	{
		m_operand1->Mutate(standard_deviation);
	}
#ifdef LGP_DEBUG
	else if(!m_operand2->IsConstant())
	{
		LGPExitSystem("LGPInstruction::MutateConstant()", "both m_operand1 and m_operand2 are not constant registers");
	}
#endif
	else
	{
		m_operand2->Mutate(standard_deviation);
	}
}

void LGPInstruction::MutateRegister(double p_const)
{
	double r=lgpRandom.nextDouble();
	if(r < 0.5)
	{
		m_destination_register=m_lgp->GetRegisterSet()->GetRandomRegister(m_destination_register);
	}
	else
	{
		r=lgpRandom.nextDouble();

		LGPRegister *arg1, *arg2;
		if(r < 0.5)
		{
			arg1=m_operand1;
			arg2=m_operand2;
		}
		else
		{
			arg1=m_operand2;
			arg2=m_operand1;
		}

		if(arg2->IsConstant())
		{
			arg1=m_lgp->GetRegisterSet()->GetRandomRegister(arg1);
		}
		else
		{
			r=lgpRandom.nextDouble();
			if(r < p_const)
			{
				arg1=m_lgp->GetConstantSet()->GetRandomRegister();
			}
			else
			{
				arg1=m_lgp->GetRegisterSet()->GetRandomRegister(arg1);
			}
		}
	}
}

void LGPInstruction::MutateOperator()
{
	m_op=m_lgp->GetOperatorSet()->GetRandomOperator(m_op);
}

int LGPInstruction::GetConstantRegisterIndex() const 
{
	if(m_operand1->IsConstant())
	{
		return 1;
	}
	else if(m_operand2->IsConstant())
	{
		return 2;
	}

	return -1;
}

std::string LGPInstruction::ToString() const
{
	std::ostringstream oss;

	oss << "<" << m_op->ToString() << "\t" << m_operand1->ToString(true) << "\t" << m_operand2->ToString(true) << "\t" << m_destination_register->ToString(true) << ">";
	
	if(this->m_bIsStructuralIntron)
	{
		oss << "(intron)";
	}

	return oss.str();
}