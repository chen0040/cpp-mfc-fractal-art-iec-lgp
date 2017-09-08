#include "stdafx.h"
#include "LGPPopInitInstruction_ConstantLength.h"
#include "../LGPComp/LGPPop.h"
#include "../LGPUtil/LGPRandom.h"
#include <sstream>

LGPPopInitInstruction_ConstantLength::LGPPopInitInstruction_ConstantLength()
: LGPPopInitInstruction()
, m_constant_program_length(100)
{

}

LGPPopInitInstruction_ConstantLength::LGPPopInitInstruction_ConstantLength(const LGPPopInitInstruction_ConstantLength& rhs)
{
	this->m_constant_program_length=rhs.m_constant_program_length;
}

LGPPopInitInstruction_ConstantLength::LGPPopInitInstruction_ConstantLength(TiXmlElement* xml_level1)
: LGPPopInitInstruction(xml_level1)
{
	for(TiXmlElement* xml_level2=xml_level1->FirstChildElement(); xml_level2 != NULL; xml_level2=xml_level2->NextSiblingElement())
	{
		if(strcmp(xml_level2->Value(), "param")==0)
		{
			if(strcmp(xml_level2->Attribute("name"), "constant_length")==0)
			{
				int value=0;
				xml_level2->QueryIntAttribute("value", &value);
				m_constant_program_length=value;
			}
		}	
	}
}

LGPPopInitInstruction_ConstantLength::~LGPPopInitInstruction_ConstantLength()
{
}

void LGPPopInitInstruction_ConstantLength::Initialize(LGPPop *lgpPop)
{
	// Xianshun says:
	// specified here is a variable length initialization that selects initial program
	// lengths from a uniform distribution within a specified range of m_iInitialMinProgLength - m_iIinitialMaxProgLength
	// the method is recorded in chapter 7 section 7.6 page 164 of Linear Genetic Programming 2004
	unsigned int iPopulationSize=lgpPop->GetConfig()->GetPopulationSize();

	// Xianshun says:
	// the program generated in this way will have program length as small as 
	// iMinProgLength and as large as iMaxProgLength
	// the program length is distributed uniformly between iMinProgLength and iMaxProgLength
	for(unsigned int i=0; i<iPopulationSize; i++)
	{
		LGPProgram* lgp=lgpPop->CreateProgram(m_constant_program_length, lgpPop->GetEnvironment());
		lgpPop->AddProgram(lgp);
	}

}

std::string LGPPopInitInstruction_ConstantLength::ToString() const
{
	std::ostringstream oss;

	oss << ">> Name: LGPPopInstruction_MaximumInitialization" << std::endl;
	oss << ">> Constant Initial Program Length: " << m_constant_program_length << std::endl;

	return oss.str();
}

LGPPopInitInstruction* LGPPopInitInstruction_ConstantLength::Clone() const
{
	return new LGPPopInitInstruction_ConstantLength(*this);
}