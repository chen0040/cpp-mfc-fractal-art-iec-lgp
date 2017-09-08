#include "stdafx.h"
#include "LGPRegister.h"
#include <sstream>
#include "../LGPUtil/LGPRandom.h"
#include "../LGPConstants/LGPProtectedDefinition.h"

LGPRegister::LGPRegister()
: m_bIsConstant(false)
, m_value(1)
{

}

LGPRegister::LGPRegister(const LGPRegister& rhs)
{
	m_iRegisterIndex=rhs.m_iRegisterIndex;
	m_bIsConstant=rhs.m_bIsConstant;
	m_value=rhs.m_value; 
}

LGPRegister::~LGPRegister()
{

}

void LGPRegister::Mutate(double standard_deviation)
{
	m_value+=lgpRandom.normal(0, standard_deviation);
}

void LGPRegister::SetValue(double value)
{
	if(value > LGP_REG_POSITIVE_INF)
	{
		m_value=LGP_REG_POSITIVE_INF;
	}
	else
	{
		m_value=value; 
	}
}

std::string LGPRegister::ToString(bool bShowIndex) const
{
	std::ostringstream oss;

	if(bShowIndex)
	{
		if(this->IsConstant())
		{
			oss << "c[" << this->m_iRegisterIndex << "]"; 
		}
		else
		{
			oss << "r[" << this->m_iRegisterIndex << "]";
		}
	}
	else
	{	
		oss << m_value;
	}

	return oss.str();
}