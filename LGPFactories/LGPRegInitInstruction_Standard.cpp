#include "stdafx.h"
#include "LGPRegInitInstruction_Standard.h"
#include <sstream>
#include "../LGPConstants/LGPFlags.h"
#include "../LGPUtil/LGPExitSystem.h"
#include <iostream>

LGPRegInitInstruction_Standard::LGPRegInitInstruction_Standard()
: LGPRegInitInstruction()
, m_input_copy_count(1)
{
	
}

LGPRegInitInstruction_Standard::LGPRegInitInstruction_Standard(TiXmlElement *xml_level1)
: LGPRegInitInstruction(xml_level1)
{
	for(TiXmlElement* xml_level2=xml_level1->FirstChildElement(); xml_level2 != NULL; xml_level2=xml_level2->NextSiblingElement())
	{
		if(strcmp(xml_level2->Value(), "param")==0)
		{
			if(strcmp(xml_level2->Attribute("name"), "input_copy_count")==0)
			{
				int value;
				xml_level2->QueryIntAttribute("value", &value);
				m_input_copy_count=value;
			}
			else if(strcmp(xml_level2->Attribute("name"), "default_register_value")==0)
			{
				xml_level2->QueryDoubleAttribute("value", &m_default_register_value);
			}
		}
	}
}

LGPRegInitInstruction_Standard::LGPRegInitInstruction_Standard(const LGPRegInitInstruction_Standard& rhs)
{

}

LGPRegInitInstruction_Standard::~LGPRegInitInstruction_Standard()
{

}

LGPRegInitInstruction* LGPRegInitInstruction_Standard::Clone() const
{
	return new LGPRegInitInstruction_Standard(*this);
}

void LGPRegInitInstruction_Standard::InitializeRegisters(LGPRegisterSet *reg_set, LGPConstantSet* constant_set, const LGPFitnessCase *fitness_case)
{
	unsigned int iRegisterCount=reg_set->GetRegisterCount();
	unsigned int iInputCount=fitness_case->GetInputCount();

#ifdef LGP_DEBUG
	if(iInputCount > iRegisterCount)
	{
		LGPExitSystem("LGPRegInitInstruction_Standard::InitializeRegisters(LGPProgram *lgp, const LGPFitnessCase *fitness_case)", "iInputCount > iRegisterCount");
	}
#endif

	unsigned int iRegisterIndex=0;
	for(unsigned int i=0; i<m_input_copy_count; ++i)
	{
		for(unsigned int j=0; j<iInputCount; ++j, ++iRegisterIndex)
		{
			if(iRegisterIndex >= iRegisterCount)
			{
				break;
			}

			double value;
			fitness_case->QueryInput(j, &value);
			reg_set->GetRegister(iRegisterIndex)->SetValue(value);
		}

		if(iRegisterIndex >= iRegisterCount)
		{
			break;
		}
	}

	while(iRegisterIndex < iRegisterCount)
	{
		reg_set->GetRegister(iRegisterIndex)->SetValue(m_default_register_value);
		iRegisterIndex++;
	}

}

std::string LGPRegInitInstruction_Standard::ToString() const
{
	std::ostringstream oss;

	oss << ">> Name: LGPRegInitInstruction_Standard" << std::endl;
	oss << ">> input copy count: " << m_input_copy_count << std::endl;
	oss << ">> default register value: " << m_default_register_value;
	return oss.str();
}