#include "stdafx.h"
#include "LGPOperator.h"
//#include "../LGPUtil/LGPExitSystem.h"
#include "../lgp_misc/io_manip.h"
#include <fstream>
#include <iostream>
#include <sstream>

LGPOperator::LGPOperator(const char* symbol)
: m_bIsConditionalConstruct(false)
, m_symbol(symbol)
{

}

LGPOperator::LGPOperator(const LGPOperator& rhs)
{
	m_iOperatorIndex=rhs.m_iOperatorIndex;
	m_bIsConditionalConstruct=rhs.m_bIsConditionalConstruct;
	m_symbol=rhs.m_symbol;
	m_method_name=rhs.m_method_name;
}

LGPOperator::~LGPOperator()
{

}

std::string LGPOperator::ToString() const
{
	return m_symbol;
}

std::string LGPOperator::GetMethodName() const
{
	return m_method_name;
}

void LGPOperator::WriteHeaderFile(std::string filename) const
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
	headerfile << "double " << m_method_name << "(double, double);\n";
	headerfile << "#endif\n";

	headerfile.close();
}

void LGPOperator::WriteSourceFile(std::string filename, std::string header_file) const
{
	if(m_method_name.compare("")==0)
	{
		return;
	}

	std::ofstream sourcefile(filename.c_str());

	sourcefile << "#include \"" << header_file << "\"\n";
	sourcefile << GetOperatorRequiredHeaderFiles();
	sourcefile << "\n";

	sourcefile << "double " << m_method_name << "(double operand1, double operand2)\n";
	sourcefile << "{\n";
	sourcefile << "\tdouble destination_register=0;\n";
	sourcefile << GetOperatorContent("operand1", "operand2", "destination_register");
	sourcefile << "\treturn destination_register;\n";
	sourcefile << "}\n";

	sourcefile.close();
}