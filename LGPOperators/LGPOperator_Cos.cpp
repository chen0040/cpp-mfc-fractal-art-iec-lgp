#include "stdafx.h"
#include "LGPOperator_Cos.h"
#include <cmath>
#include <sstream>

LGPOperator_Cos::LGPOperator_Cos()
: LGPOperator("cos")
{
	m_method_name="lgp_cos";
}

LGPOperator_Cos::~LGPOperator_Cos()
{

}

LGPOperator* LGPOperator_Cos::Clone() const
{
	return new LGPOperator_Cos(*this);
}

int LGPOperator_Cos::Execute(const LGPRegister *operand1, const LGPRegister *operand2, LGPRegister *destination_register)
{
	double x=operand1->ToDouble();
	double y=operand2->ToDouble();
	if(y != 0)
	{
		destination_register->SetValue(cos(x / y));
	}
	else
	{
		destination_register->SetValue(cos(x));
	}
	return LGP_EXECUTE_NEXT_INSTRUCTION;
}

std::string LGPOperator_Cos::GetOperatorContent(std::string operand1, std::string operand2, std::string destination_register, std::string line_start, std::string line_end) const
{
	std::ostringstream oss;
	oss << line_start << "if(operand2 != 0)" << line_end;
	oss << line_start << line_start << destination_register << "=" << "cos(" << operand1 << "/" << operand2 << ");" << line_end;
	oss << line_start << "else" << line_end;
	oss << line_start << line_start << destination_register << "=" << "cos(" << operand1 << ");" << line_end;

	return oss.str();
}

std::string LGPOperator_Cos::GetOperatorRequiredHeaderFiles() const
{
	return "#include <cmath>\n";
}