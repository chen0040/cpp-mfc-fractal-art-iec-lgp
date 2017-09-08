#include "stdafx.h"
#include "LGPOperator_Division.h"
#include "../LGPConstants/LGPProtectedDefinition.h"
#include <sstream>

LGPOperator_Division::LGPOperator_Division()
: LGPOperator("/")
{
	m_method_name="lgp_div";
}

LGPOperator_Division::~LGPOperator_Division()
{

}

int LGPOperator_Division::Execute(const LGPRegister* operand1, const LGPRegister* operand2, LGPRegister* destination_register)
{
	if(operand2->ToDouble() == 0)
	{
		destination_register->SetValue(operand1->ToDouble() + LGP_UNDEFINED);
	}
	else
	{
		destination_register->SetValue(operand1->ToDouble() / operand2->ToDouble());
	}

	return LGP_EXECUTE_NEXT_INSTRUCTION;
}

std::string LGPOperator_Division::GetOperatorContent(std::string operand1, std::string operand2, std::string destination_register, std::string line_start, std::string line_end) const
{
	std::stringstream oss;
	oss << line_start << "if(" << operand2 << " == 0)" << line_end;
	oss << line_start << line_start << destination_register << "=" << operand1 << "+" << LGP_UNDEFINED << ";" << line_end;
	oss << line_start << "else" << line_end;
	oss << line_start << line_start << destination_register << "=" << operand1 << "/" << operand2 << ";" << line_end;

	return oss.str();
}

std::string LGPOperator_Division::GetOperatorRequiredHeaderFiles() const
{
	return "#include <cmath>\n";
}