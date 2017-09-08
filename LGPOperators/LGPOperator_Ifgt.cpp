#include "stdafx.h"
#include "LGPOperator_Ifgt.h"
#include <io.h>
#include <fstream>
#include <iostream>

LGPOperator_Ifgt::LGPOperator_Ifgt()
: LGPOperator("If>")
{
	m_method_name="if_greater_than";
	m_bIsConditionalConstruct=true;
}

LGPOperator_Ifgt::~LGPOperator_Ifgt()
{

}

int LGPOperator_Ifgt::Execute(const LGPRegister* operand1, const LGPRegister* operand2, LGPRegister* destination_register)
{
	if(operand1->ToDouble() > operand2->ToDouble())
	{
		return LGP_EXECUTE_NEXT_INSTRUCTION;
	}
	else
	{
		return LGP_SKIP_NEXT_INSTRUCTION;
	}
}

LGPOperator* LGPOperator_Ifgt::Clone() const
{
	return new LGPOperator_Ifgt(*this);
}


void LGPOperator_Ifgt::WriteHeaderFile(std::string filename) const
{
	if(m_method_name.compare("")==0)
	{
		return;
	}

	std::ofstream headerfile(filename.c_str());

	std::string header_method_name=m_method_name;
	for(size_t i=0; i<header_method_name.length(); ++i)
	{
		header_method_name[i]=toupper(header_method_name[i]);
	}

	headerfile << "#ifndef _H_LGAP_OP_" << header_method_name << "_H\n";
	headerfile << "#define _H_LGAP_OP_" << header_method_name << "_H\n";
	headerfile << "#define " << m_method_name << "(x, y) if(x > y)\n";
	headerfile << "#endif\n";

	headerfile.close();
}

void LGPOperator_Ifgt::WriteSourceFile(std::string filename, std::string header_file) const
{
	
}