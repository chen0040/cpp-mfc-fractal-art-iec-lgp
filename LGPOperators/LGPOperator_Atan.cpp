#include "stdafx.h"
#include "LGPOperator_Atan.h"
#include <cmath>
#include <sstream>

LGPOperator_Atan::LGPOperator_Atan()
: LGPOperator("atan")
{
	m_method_name="lgp_atan";
}

LGPOperator_Atan::~LGPOperator_Atan()
{

}

LGPOperator* LGPOperator_Atan::Clone() const
{
	return new LGPOperator_Atan(*this);
}

int LGPOperator_Atan::Execute(const LGPRegister *operand1, const LGPRegister *operand2, LGPRegister *destination_register)
{
	double x=operand1->ToDouble();
	double y=operand2->ToDouble();
	
	destination_register->SetValue(atan2(y, x));

	return LGP_EXECUTE_NEXT_INSTRUCTION;
}

std::string LGPOperator_Atan::GetOperatorContent(std::string operand1, std::string operand2, std::string destination_register, std::string line_start, std::string line_end) const
{
	std::ostringstream oss;
	oss << line_start << destination_register << "=" << "atan2(" << operand2 << ", " << operand1 << ");" << line_end;

	return oss.str();
}

std::string LGPOperator_Atan::GetOperatorRequiredHeaderFiles() const
{
	return "#include <cmath>\n";
}