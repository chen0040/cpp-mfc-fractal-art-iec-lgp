#include "stdafx.h"
#include "LGPOperator_Minus.h"
#include <sstream>

LGPOperator_Minus::LGPOperator_Minus()
: LGPOperator("-")
{
	m_method_name="lgp_minus";
}

LGPOperator_Minus::~LGPOperator_Minus()
{

}

int LGPOperator_Minus::Execute(const LGPRegister* operand1, const LGPRegister* operand2, LGPRegister* destination_register)
{
	double x=operand1->ToDouble();
	double y=operand2->ToDouble();
	destination_register->SetValue(x - y);

	return LGP_EXECUTE_NEXT_INSTRUCTION;
}

std::string LGPOperator_Minus::GetOperatorContent(std::string operand1, std::string operand2, std::string destination_register, std::string line_start, std::string line_end) const
{
	std::ostringstream oss;

	oss << line_start << destination_register << "=" << operand1 << "-" << operand2 << ";" << line_end;

	return oss.str();
}

std::string LGPOperator_Minus::GetOperatorRequiredHeaderFiles() const
{
	return "#include <cmath>\n";
}