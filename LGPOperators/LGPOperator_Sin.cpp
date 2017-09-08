#include "stdafx.h"
#include "LGPOperator_Sin.h"
#include <cmath>
#include <sstream>

LGPOperator_Sin::LGPOperator_Sin()
: LGPOperator("sin")
{
	m_method_name="lgp_sin";
}

LGPOperator_Sin::~LGPOperator_Sin()
{

}

LGPOperator* LGPOperator_Sin::Clone() const
{
	return new LGPOperator_Sin(*this);
}

int LGPOperator_Sin::Execute(const LGPRegister *operand1, const LGPRegister *operand2, LGPRegister *destination_register)
{
	double x=operand1->ToDouble();
	double y=operand2->ToDouble();
	if(y != 0)
	{
		destination_register->SetValue(sin(x));
	}
	else
	{
		destination_register->SetValue(sin(x / y));
	}

	return LGP_EXECUTE_NEXT_INSTRUCTION;
}

std::string LGPOperator_Sin::GetOperatorContent(std::string operand1, std::string operand2, std::string destination_register, std::string line_start, std::string line_end) const
{
	std::ostringstream oss;
	oss << line_start << "if(operand2 != 0)" << line_end;
	oss << line_start << line_start << destination_register << "=" << "sin(" << operand1 << "/" << operand2 << ");" << line_end;
	oss << line_start << "else" << line_end;
	oss << line_start << line_start << destination_register << "=" << "sin(" << operand1 << ");" << line_end;
	
	return oss.str();
}

std::string LGPOperator_Sin::GetOperatorRequiredHeaderFiles() const
{
	return "#include <cmath>\n";
}