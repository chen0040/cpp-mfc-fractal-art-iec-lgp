#include "stdafx.h"
#include "LGPOperator_Multiplication.h"
#include <sstream>

LGPOperator_Multiplication::LGPOperator_Multiplication()
: LGPOperator("*")
{
	m_method_name="lgp_mult";
}

LGPOperator_Multiplication::~LGPOperator_Multiplication()
{

}

int LGPOperator_Multiplication::Execute(const LGPRegister* operand1, const LGPRegister* operand2, LGPRegister* destination_register)
{
	double x1=operand1->ToDouble();
	double x2=operand2->ToDouble();
	destination_register->SetValue(x1*x2);

	return LGP_EXECUTE_NEXT_INSTRUCTION;
}

std::string LGPOperator_Multiplication::GetOperatorContent(std::string operand1, std::string operand2, std::string destination_register, std::string line_start, std::string line_end) const
{
	std::ostringstream oss;

	oss << line_start << destination_register << "=" << operand1 << "*" << operand2 << ";" << line_end;

	return oss.str();
}

std::string LGPOperator_Multiplication::GetOperatorRequiredHeaderFiles() const
{
	return "#include <cmath>\n";
}