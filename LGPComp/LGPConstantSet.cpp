#include "stdafx.h"
#include "LGPConstantSet.h"
#include "../LGPUtil/LGPRandom.h"
#include "../LGPConstants/LGPFlags.h"
#include "../LGPUtil/LGPExitSystem.h"
#include <sstream>

LGPConstantSet::LGPConstantSet()
: m_dWeightSum(0)
{

}

LGPConstantSet::~LGPConstantSet()
{
	std::vector<std::pair<LGPRegister*, double> >::iterator pos;
	for(pos=m_registers.begin(); pos != m_registers.end(); ++pos)
	{
		delete (pos->first);
	}
	m_registers.clear();
}

LGPConstantSet::LGPConstantSet(const LGPConstantSet& rhs)
{
	m_dWeightSum=rhs.m_dWeightSum;
	m_registers.reserve(rhs.m_registers.size());

	for(size_t i=0; i<rhs.m_registers.size(); i++)
	{
		m_registers.push_back(std::make_pair<LGPRegister*, double>(rhs.m_registers[i].first->Clone(), rhs.m_registers[i].second));
	}
}

LGPRegister* LGPConstantSet::GetRandomRegister(LGPRegister* current_register)
{
	for(unsigned int attempts=0; attempts < 10; attempts++)
	{
		double r=m_dWeightSum * lgpRandom.nextDouble();
		std::vector<std::pair<LGPRegister*, double> >::iterator pos=m_registers.begin();
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
	
void LGPConstantSet::AddRegister(LGPRegister* lgpRegister, double weight)
{
	m_registers.push_back(std::make_pair<LGPRegister*, double>(lgpRegister, weight));
	lgpRegister->m_iRegisterIndex=static_cast<unsigned int>(m_registers.size()) - 1;
	lgpRegister->m_bIsConstant=true;

	m_dWeightSum+=weight;
}

void LGPConstantSet::AddConstant(double value, double weight)
{
	LGPRegister* lgpConstant=new LGPRegister();
	lgpConstant->SetValue(value);

	this->AddRegister(lgpConstant, weight);
}

LGPRegister* LGPConstantSet::GetRegister(unsigned int iRegisterIndex) const
{
#ifdef LGP_DEBUG
	if(iRegisterIndex >= m_registers.size())
	{
		LGPExitSystem("LGPConstantSet::GetRegister(unsigned int iRegisterIndex)", "iRegisterIndex >= m_registers.size()");
	}
	if(iRegisterIndex < 0)
	{
		LGPExitSystem("LGPConstantSet::GetRegister(unsigned int iRegisterIndex)", "iRegisterIndex < 0");
	}
#endif

	return m_registers[iRegisterIndex].first;
}

std::string LGPConstantSet::ToString() const
{
	std::ostringstream oss;

	for(size_t i=0; i<m_registers.size(); i++)
	{
		oss << "registers[" << i << "]: " << m_registers[i].first->ToString() << std::endl;
	}

	return oss.str();
}