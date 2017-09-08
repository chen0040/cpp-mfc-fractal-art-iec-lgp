#include "stdafx.h"
#include "LGPOperator_Exp.h"
#include "../LGPConstants/LGPProtectedDefinition.h"
#include <cmath>
#include <sstream>

LGPOperator_Exp::LGPOperator_Exp()
: LGPOperator("exp")
{
	m_method_name="lgp_exp";
}

LGPOperator_Exp::~LGPOperator_Exp()
{

}

int LGPOperator_Exp::Execute(const LGPRegister *operand1, const LGPRegister *operand2, LGPRegister *destination_register)
{
	// Xianshun says:
	// the protected definition in Linear Genetic Programming is used
	double x=operand1->ToDouble();
	double y=operand2->ToDouble();
	if(fabs(x) < 32)
	{
		if(y != 0)
		{
			destination_register->SetValue(exp(x / y));
		}
		else
		{
			destination_register->SetValue(exp(x));
		}
	}
	else
	{
		destination_register->SetValue(x+LGP_UNDEFINED);
	}

	return LGP_EXECUTE_NEXT_INSTRUCTION;
}

std::string LGPOperator_Exp::GetOperatorContent(std::string operand1, std::string operand2, std::string destination_register, std::string line_start, std::string line_end) const
{
	std::ostringstream oss;
	oss << line_start << "if(fabs(" << operand1 << ") < 32)" << line_end;
	oss << line_start << "{" << line_end;
	oss << line_start << line_start << "if(" << operand2 << " != 0)" << line_end;
	oss << line_start << line_start << line_start << destination_register << "=exp(" << operand1 << "/" << operand2 << ");" << line_end;
	oss << line_start << line_start << "else" << line_end;
	oss << line_start << line_start << line_start << destination_register << "=exp(" << operand1 << ");" << line_end;
	oss << line_start << "}" << line_end;
	oss << line_start << "else" << line_end;
	oss << line_start << "{" << line_end;
	oss << line_start << line_start << destination_register << "=" << operand1 << "+" << LGP_UNDEFINED << ";" << line_end;
	oss << line_start << "}" << line_end;
	return oss.str();
}

std::string LGPOperator_Exp::GetOperatorRequiredHeaderFiles() const
{
	return "#include <cmath>\n";
}