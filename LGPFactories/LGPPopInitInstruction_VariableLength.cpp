#include "stdafx.h"
#include "LGPPopInitInstruction_VariableLength.h"
#include "../LGPComp/LGPPop.h"
#include "../LGPUtil/LGPRandom.h"
#include <sstream>

LGPPopInitInstruction_VariableLength::LGPPopInitInstruction_VariableLength()
: LGPPopInitInstruction()
, m_iInitialMaxProgLength(100)
, m_iInitialMinProgLength(20)
{

}

LGPPopInitInstruction_VariableLength::LGPPopInitInstruction_VariableLength(const LGPPopInitInstruction_VariableLength& rhs)
{
	this->m_iInitialMaxProgLength=rhs.m_iInitialMaxProgLength;
	this->m_iInitialMinProgLength=rhs.m_iInitialMinProgLength;
}

LGPPopInitInstruction_VariableLength::LGPPopInitInstruction_VariableLength(TiXmlElement* xml_level1)
: LGPPopInitInstruction(xml_level1)
{
	for(TiXmlElement* xml_level2=xml_level1->FirstChildElement(); xml_level2 != NULL; xml_level2=xml_level2->NextSiblingElement())
	{
		if(strcmp(xml_level2->Value(), "param")==0)
		{
			if(strcmp(xml_level2->Attribute("name"), "InitialMinProgLength")==0)
			{
				int value=0;
				xml_level2->QueryIntAttribute("value", &value);
				m_iInitialMinProgLength=value;
			}
			else if(strcmp(xml_level2->Attribute("name"), "InitialMaxProgLength")==0)
			{
				int value=0;
				xml_level2->QueryIntAttribute("value", &value);
				m_iInitialMaxProgLength=value;
			}
		}	
	}
}

LGPPopInitInstruction_VariableLength::~LGPPopInitInstruction_VariableLength()
{
}

void LGPPopInitInstruction_VariableLength::Initialize(LGPPop *lgpPop)
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
		unsigned int iProgLength=m_iInitialMinProgLength + lgpRandom.nextInt(m_iInitialMaxProgLength - m_iInitialMinProgLength + 1);
		LGPProgram* lgp=lgpPop->CreateProgram(iProgLength, lgpPop->GetEnvironment());
		lgpPop->AddProgram(lgp);
	}

}

std::string LGPPopInitInstruction_VariableLength::ToString() const
{
	std::ostringstream oss;

	oss << ">> Name: LGPPopInstruction_VariableLength" << std::endl;
	oss << ">> InitialMinProgLength: " << m_iInitialMinProgLength << std::endl;
	oss << ">> InitialMaxProgLength: " << m_iInitialMaxProgLength << std::endl;

	return oss.str();
}

LGPPopInitInstruction* LGPPopInitInstruction_VariableLength::Clone() const
{
	return new LGPPopInitInstruction_VariableLength(*this);
}