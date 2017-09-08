#include "stdafx.h"
#include "LGPOperator_Sqrt.h"
#include "../LGPConstants/LGPProtectedDefinition.h"
#include <cmath>
#include <sstream>

LGPOperator_Sqrt::LGPOperator_Sqrt()
: LGPOperator("sqrt")
{
	m_method_name="lgp_sqrt";
}

LGPOperator_Sqrt::~LGPOperator_Sqrt()
{

}

int LGPOperator_Sqrt::Execute(const LGPRegister *operand1, const LGPRegister *operand2, LGPRegister *destination_register)
{
	// Xianshun says:
	// the protected definition in Linear Genetic Programming
	// is used here
	double x=operand1->ToDouble();
	destination_register->SetValue(sqrt(fabs(x)));

	return LGP_EXECUTE_NEXT_INSTRUCTION;
}

std::string LGPOperator_Sqrt::GetOperatorContent(std::string operand1, std::string operand2, std::string destination_register, std::string line_start, std::string line_end) const
{
	std::ostringstream oss;

	oss << line_start << destination_register << "=sqrt(fabs(" << operand1 << "));" << line_end;

	return oss.str();
}
	
std::string LGPOperator_Sqrt::GetOperatorRequiredHeaderFiles() const
{
	return "#include <cmath>\n";
}