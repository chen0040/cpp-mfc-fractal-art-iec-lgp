#include "stdafx.h"
#include "LGPOperatorSet.h"
#include "../LGPUtil/LGPRandom.h"
#include "../LGPConstants/LGPFlags.h"
#include "../LGPUtil/LGPExitSystem.h"
#include "../LGPOperators/LGPOperator_Iflt.h"
#include "../LGPOperators/LGPOperator_Ifgt.h"
#include <sstream>
#include <fstream>
#include <iostream>
#include "../lgp_misc/io_manip.h"

LGPOperatorSet::LGPOperatorSet()
: m_dWeightSum(0)
{

}

LGPOperatorSet::~LGPOperatorSet()
{
	std::vector<std::pair<LGPOperator*, double> >::iterator pos;
	for(pos=m_registers.begin(); pos != m_registers.end(); ++pos)
	{
		delete (pos->first);
	}
	m_registers.clear();
}

LGPOperatorSet::LGPOperatorSet(const LGPOperatorSet& rhs)
{
	m_dWeightSum=rhs.m_dWeightSum;
	m_registers.reserve(rhs.m_registers.size());

	for(size_t i=0; i<rhs.m_registers.size(); i++)
	{
		m_registers.push_back(std::make_pair<LGPOperator*, double>(rhs.m_registers[i].first->Clone(), rhs.m_registers[i].second));
	}
}

LGPOperator* LGPOperatorSet::GetRandomOperator(LGPOperator* current_register)
{
	for(unsigned int attempts=0; attempts < 10; attempts++)
	{
		double r=m_dWeightSum * lgpRandom.nextDouble();
		std::vector<std::pair<LGPOperator*, double> >::iterator pos=m_registers.begin();
		double current_sum=0;
		while(pos != m_registers.end())
		{
			current_sum+=pos->second;
			if(current_sum >= r)
			{
				if(pos->first != current_register)
				{
					return pos->first;
				}
				else 
				{
					break;
				}
			}

			++pos;
		}
	}

	return current_register;
}
	
void LGPOperatorSet::AddOperator(LGPOperator* lgpOperator, double weight)
{
	m_registers.push_back(std::make_pair<LGPOperator*, double>(lgpOperator, weight));
	lgpOperator->m_iOperatorIndex=static_cast<unsigned int>(m_registers.size()) - 1;
	
#ifdef LGP_DEBUG
	if(lgpOperator->m_iOperatorIndex >= m_registers.size())
	{
		LGPExitSystem("LGPOperatorSet::AddOperator(LGPOperator* lgpOperator, double weight)", "lgpOperator->m_iOperatorIndex >= m_registers.size()");
	}
#endif

	m_dWeightSum+=weight;
}

void LGPOperatorSet::AddIfltOperator(double weight)
{
	this->AddOperator(new LGPOperator_Iflt(), weight);
}

void LGPOperatorSet::AddIfgtOperator(double weight)
{
	this->AddOperator(new LGPOperator_Ifgt(), weight);
}

LGPOperator* LGPOperatorSet::GetOperator(unsigned int iRegisterIndex) const
{
#ifdef LGP_DEBUG
	if(iRegisterIndex >= m_registers.size())
	{
		LGPExitSystem("LGPOperatorSet::GetOperator(unsigned int iRegisterIndex)", "iRegisterIndex >= m_registers.size()");
	}
	if(iRegisterIndex < 0)
	{
		LGPExitSystem("LGPOperatorSet::GetOperator(unsigned int iRegisterIndex)", "iRegisterIndex < 0");
	}
#endif

	return m_registers[iRegisterIndex].first;
}

std::string LGPOperatorSet::ToString() const
{
	std::ostringstream oss;

	for(size_t i=0; i<m_registers.size(); ++i)
	{
		oss << "operators[" << i << "]: " << m_registers[i].first->ToString() << std::endl;
	}
	return oss.str();
}

void LGPOperatorSet::WriteHeaderFiles(std::string directory_name, std::string operators_header_file)
{
	make_dir_if_not_exists(directory_name);

	std::ostringstream oss_operators_header_file;
	oss_operators_header_file << directory_name << "\\" << operators_header_file;

	std::ofstream operators_header_file_stream(oss_operators_header_file.str().c_str());
	operators_header_file_stream << "#ifndef _H_LGP_OPERATORS_HEADER_FILE_H\n";
	operators_header_file_stream << "#define _H_LGP_OPERATORS_HEADER_FILE_H\n";

	for(size_t i=0; i<m_registers.size(); ++i)
	{
		std::ostringstream oss_header_file;
		std::string operator_method_name=m_registers[i].first->GetMethodName();
		oss_header_file << directory_name << "\\" << operator_method_name << ".h";
		m_registers[i].first->WriteHeaderFile(oss_header_file.str());

		if(operator_method_name.compare("") != 0)
		{
			operators_header_file_stream << "#include \"" << operator_method_name << ".h\"\n";
		}
	}

	operators_header_file_stream << "#endif\n";
	operators_header_file_stream.close();	
}

void LGPOperatorSet::WriteSourceFiles(std::string directory_name, std::string operators_source_file, std::string operators_header_file)
{
	make_dir_if_not_exists(directory_name);

	std::ostringstream oss_operators_source_file;
	oss_operators_source_file << directory_name << "\\" << operators_source_file;
	std::ofstream operators_source_file_stream(oss_operators_source_file.str().c_str());
	operators_source_file_stream << "#include \"" << operators_header_file << "\"\n";
	operators_source_file_stream.close();

	for(size_t i=0; i<m_registers.size(); ++i)
	{
		std::ostringstream oss_header_file;
		oss_header_file << m_registers[i].first->GetMethodName() << ".h";

		std::ostringstream oss_source_file;
		oss_source_file << directory_name << "\\" << m_registers[i].first->GetMethodName() << ".cpp";

		m_registers[i].first->WriteSourceFile(oss_source_file.str(), oss_header_file.str());
	}
}