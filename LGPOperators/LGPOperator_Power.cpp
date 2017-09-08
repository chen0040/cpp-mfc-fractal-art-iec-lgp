#include "stdafx.h"
#include "LGPOperator_Power.h"
#include "../LGPConstants/LGPProtectedDefinition.h"
#include <cmath>
#include <sstream>

LGPOperator_Power::LGPOperator_Power()
: LGPOperator("^")
{
	m_method_name="lgp_power";
}

LGPOperator_Power::~LGPOperator_Power()
{

}

int LGPOperator_Power::Execute(const LGPRegister* operand1, const LGPRegister* operand2, LGPRegister* destination_register)
{
	double x=operand1->ToDouble();
	double y=operand2->ToDouble();

	// Xianshun says:
	// This operator use the protected definition defined in Linear Genetic Programming
	
	if(fabs(x) <= 10)
	{
		destination_register->SetValue(pow(fabs(x), y));
	}
	else
	{
		destination_register->SetValue(x+y+LGP_UNDEFINED);
	}

	return LGP_EXECUTE_NEXT_INSTRUCTION;
}

std::string LGPOperator_Power::GetOperatorContent(std::string operand1, std::string operand2, std::string destination_register, std::string line_start, std::string line_end) const
{
	std::ostringstream oss;

	oss << line_start << "if(fabs(" << operand1 << ") <= 10)" << line_end;
	oss << line_start << line_start << destination_register << "=pow(fabs(" << operand1 << "), " << operand2 << ");" << line_end;
	oss << line_start << "else" << line_end;
	oss << line_start << line_start << destination_register << "=" << operand1 << "+" << operand2 << "+" << LGP_UNDEFINED << ";" << line_end;

	return oss.str();
}

std::string LGPOperator_Power::GetOperatorRequiredHeaderFiles() const
{
	return "#include <cmath>\n";
}