#include "stdafx.h"
#include "LGPOperator_Ln.h"
#include "../LGPConstants/LGPProtectedDefinition.h"
#include <cmath>
#include <sstream>

LGPOperator_Ln::LGPOperator_Ln()
: LGPOperator("ln")
{
	m_method_name="lgp_ln";
}

LGPOperator_Ln::~LGPOperator_Ln()
{

}

int LGPOperator_Ln::Execute(const LGPRegister* operand1, const LGPRegister* operand2, LGPRegister* destination_register)
{
	// Xianshun says:
	// The protected definition of Linear Genetic Programming is used here
	double x=operand1->ToDouble();
	
	if(x != 0)
	{
		
		double y=operand2->ToDouble();
		if(y != 0)
		{
			destination_register->SetValue(log(x / y));
		}
		else
		{
			destination_register->SetValue(log(x));
		}
	}
	else
	{
		double y=operand2->ToDouble();
		if(y != 0)
		{
			destination_register->SetValue(log(y));
		}
		else
		{
			destination_register->SetValue(x+LGP_UNDEFINED);
		}
	}

	return LGP_EXECUTE_NEXT_INSTRUCTION;
}

std::string LGPOperator_Ln::GetOperatorContent(std::string operand1, std::string operand2, std::string destination_register, std::string line_start, std::string line_end) const
{
	std::ostringstream oss;
	oss << line_start << "if(" << operand1 << " != 0)" << line_end;
	oss << line_start << "{" << line_end;
	oss << line_start << line_start << "if(" << operand2 << " != 0)" << line_end;
	oss << line_start << line_start << line_start << destination_register << "=log(" << operand1 << "/" << operand2 << "); " << line_end;
	oss << line_start << line_start << "else" << line_end;
	oss << line_start << line_start << line_start << destination_register << "=log(" << operand1 << "); " << line_end;
	oss << line_start << "}" << line_end;
	oss << line_start << "else" << line_end;
	oss << line_start << "{" << line_end;
	oss << line_start << line_start << "if(" << operand2 << " != 0)" << line_end;
	oss << line_start << line_start << line_start << destination_register << "=log(" << operand2 << ");" << line_end;
	oss << line_start << line_start << "else" << line_end;
	oss << line_start << line_start << line_start << destination_register << "=" << operand2 << "+" << LGP_UNDEFINED << ";" << line_end;
	oss << line_start << "}" << line_end;

	return oss.str();
}

std::string LGPOperator_Ln::GetOperatorRequiredHeaderFiles() const
{
	return "#include <cmath>\n";
}