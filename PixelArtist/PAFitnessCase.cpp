#include "stdafx.h"
#include "PAFitnessCase.h"
#include <sstream>
#include <iostream>
#include <cmath>

PAFitnessCase::PAFitnessCase()
: LGPFitnessCase()
{
	
}

PAFitnessCase::~PAFitnessCase()
{

}

std::string PAFitnessCase::ToString() const
{
	std::ostringstream oss;

	return oss.str();
}

void PAFitnessCase::Update(const LGPOperator* op, const LGPRegister* operand1, const LGPRegister* operand2, const LGPRegister* destination_register, const LGPRegisterSet* lgpRegSet)
{

}

void PAFitnessCase::Update(const LGPRegisterSet* lgpRegSet)
{
	m_output[0]=Normalize(lgpRegSet->GetRegister(0)->ToDouble());	
	m_output[1]=Normalize(lgpRegSet->GetRegister(1)->ToDouble());	
	m_output[2]=Normalize(lgpRegSet->GetRegister(2)->ToDouble());	
}

double PAFitnessCase::Normalize(double value)
{
	if(value <= 0 || value > 1)
	{
		return 1.0 / (1.0+ exp(-value)); 
	}
	else
	{
		return value;
	}
}

