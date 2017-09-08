#include "stdafx.h"
#include "LGPPopInitInstructionFactory.h"
#include "../LGPComp/LGPPop.h"
#include "../tinyxml/tinyxml.h"
#include "../LGPUtil/LGPExitSystem.h"
#include "../LGPConstants/LGPFlags.h"
#include "LGPPopInitInstruction_VariableLength.h"
#include "LGPPopInitInstruction_ConstantLength.h"
#include <sstream>

LGPPopInitInstructionFactory::LGPPopInitInstructionFactory(const char* filename)
: m_current_instruction(NULL)
{
	TiXmlDocument doc;
	if(!doc.LoadFile(filename))
	{
		std::ostringstream oss;
		oss << "Failed to load " << filename;
		LGPExitSystem("LGPPopInitInstructionFactory::LGPPopInitInstructionFactory()", oss.str().c_str());
	}

	TiXmlElement* xml_root=doc.RootElement();

	for(TiXmlElement* xml_level1=xml_root->FirstChildElement(); xml_level1 != NULL; xml_level1=xml_level1->NextSiblingElement())
	{
		if(strcmp(xml_level1->Value(), "strategy")==0)
		{
			if(strcmp(xml_level1->Attribute("name"), xml_root->Attribute("strategy"))==0)
			{
				if(strcmp(xml_level1->Attribute("name"), "variable_length")==0)
				{
					m_current_instruction=new LGPPopInitInstruction_VariableLength(xml_level1);
				}
				else if(strcmp(xml_level1->Attribute("name"), "constant_length")==0)
				{
					m_current_instruction=new LGPPopInitInstruction_ConstantLength(xml_level1);
				}
			}
		}
	}

#ifdef LGP_DEBUG
	if(m_current_instruction == NULL)
	{
		LGPExitSystem("LGPPopInitInstructionFactory::LGPPopInitInstructionFactory()", "m_current_instruction == NULL");
	}
#endif
	
}

LGPPopInitInstructionFactory::~LGPPopInitInstructionFactory()
{
	if(m_current_instruction != NULL)
	{
		delete m_current_instruction;
		m_current_instruction=NULL;
	}
}

LGPPopInitInstructionFactory::LGPPopInitInstructionFactory(const LGPPopInitInstructionFactory &rhs)
{
	m_current_instruction=rhs.m_current_instruction->Clone();
}

LGPPopInitInstructionFactory* LGPPopInitInstructionFactory::Clone() const
{
	return new LGPPopInitInstructionFactory(*this);
}

void LGPPopInitInstructionFactory::Initialize(LGPPop* lgpPop)
{
#ifdef LGP_DEBUG
	if(m_current_instruction == NULL)
	{
		LGPExitSystem("LGPPopInitInstructionFactory::Execute(LGPPop* lgpPop)", "m_current_instruction == NULL");
	}
#endif
	m_current_instruction->Initialize(lgpPop);
}

std::string LGPPopInitInstructionFactory::ToString() const
{
#ifdef LGP_DEBUG
	if(m_current_instruction == NULL)
	{
		LGPExitSystem("LGPPopInitInstructionFactory::ToString() const", "m_current_instruction == NULL");
	}
#endif

	std::ostringstream oss;
	oss << m_current_instruction->ToString();

	return oss.str();
}
