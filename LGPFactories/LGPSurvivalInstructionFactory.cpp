#include "stdafx.h"
#include "LGPSurvivalInstructionFactory.h"
#include <sstream>
#include "../LGPConstants/LGPFlags.h"
#include "../LGPUtil/LGPExitSystem.h"
#include "LGPSurvivalInstruction_Probablistic.h"
#include "LGPSurvivalInstruction_Compete.h"

LGPSurvivalInstructionFactory::LGPSurvivalInstructionFactory(const char* filename)
: m_current_instruction(NULL)
{
	TiXmlDocument doc;
	if(! doc.LoadFile(filename))
	{
		std::ostringstream oss;
		oss << "Failed to load " << filename;
		LGPExitSystem("LGPSurvivalInstructionFactory::LGPSurvivalInstructionFactory(const char* filename)", oss.str().c_str());
	}

	TiXmlElement* xml_root=doc.RootElement();
	for(TiXmlElement* xml_level1=xml_root->FirstChildElement(); xml_level1 != NULL; xml_level1=xml_level1->NextSiblingElement())
	{
		if(strcmp(xml_level1->Value(), "strategy")==0)
		{
			if(strcmp(xml_level1->Attribute("name"), xml_root->Attribute("strategy"))==0)
			{
				if(strcmp(xml_level1->Attribute("name"), "probablistic")==0)
				{
					m_current_instruction=new LGPSurvivalInstruction_Probablistic(xml_level1);
				}
				else if(strcmp(xml_level1->Attribute("name"), "compete")==0)
				{
					m_current_instruction=new LGPSurvivalInstruction_Compete(xml_level1);
				}
			}
		}
	}

#ifdef LGP_DEBUG
	if(m_current_instruction == NULL)
	{
		LGPExitSystem("LGPSurvivalInstructionFactory::LGPSurvivalInstructionFactory(const char* filename)", "m_current_instruction == NULL");
	}	
#endif
}

LGPSurvivalInstructionFactory::~LGPSurvivalInstructionFactory()
{
	if(m_current_instruction != NULL)
	{
		delete m_current_instruction;
		m_current_instruction=NULL;
	}
}

LGPProgram* LGPSurvivalInstructionFactory::Compete(LGPPop* lgpPop, LGPProgram* weak_program_in_current_pop, LGPProgram* child_program)
{
#ifdef LGP_DEBUG
	if(m_current_instruction == NULL)
	{
		LGPExitSystem("LGPSurvivalInstructionFactory::Compete(LGPPop* lgpPop, LGPProgram* weak_program_in_current_pop, LGPProgram* child_program)", "m_current_instruction == NULL");
	}
#endif
	return m_current_instruction->Compete(lgpPop, weak_program_in_current_pop, child_program);
}

LGPSurvivalInstructionFactory::LGPSurvivalInstructionFactory(const LGPSurvivalInstructionFactory& rhs)
{
	m_current_instruction=rhs.m_current_instruction->Clone();
}

std::string LGPSurvivalInstructionFactory::ToString() const
{
#ifdef LGP_DEBUG
	if(m_current_instruction == NULL)
	{
		LGPExitSystem("LGPSurvivalInstructionFactory::ToString() const", "m_current_instruction == NULL");
	}
#endif

	return m_current_instruction->ToString();
}

LGPSurvivalInstructionFactory* LGPSurvivalInstructionFactory::Clone() const
{
	return new LGPSurvivalInstructionFactory(*this);
}