#include "stdafx.h"
#include "LGPOperator_Sinh.h"
#include <cmath>
#include <sstream>

LGPOperator_Sinh::LGPOperator_Sinh()
: LGPOperator("sinh")
{
	m_method_name="lgp_sinh";
}

LGPOperator_Sinh::~LGPOperator_Sinh()
{

}

LGPOperator* LGPOperator_Sinh::Clone() const
{
	return new LGPOperator_Sinh(*this);
}

int LGPOperator_Sinh::Execute(const LGPRegister *operand1, const LGPRegister *operand2, LGPRegister *destination_register)
{
	double x=operand1->ToDouble();
	
	double result=(exp(x) - exp(-x)) / 2.0;
	destination_register->SetValue(result);

	return LGP_EXECUTE_NEXT_INSTRUCTION;
}

std::string LGPOperator_Sinh::GetOperatorContent(std::string operand1, std::string operand2, std::string destination_register, std::string line_start, std::string line_end) const
{
	std::ostringstream oss;

	oss << line_start << destination_register << "=(exp(" << operand1 << ") - exp(-" << operand2 << ")) / 2.0;" << line_end;

	return oss.str();
}
	
std::string LGPOperator_Sinh::GetOperatorRequiredHeaderFiles() const
{
	return "#include <cmath>\n";
}