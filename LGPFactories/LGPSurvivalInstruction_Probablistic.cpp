#include "stdafx.h"
#include "LGPSurvivalInstruction_Probablistic.h"
#include "../LGPComp/LGPPop.h"
#include "../LGPComp/LGPProgram.h"
#include "../LGPUtil/LGPExitSystem.h"
#include "../LGPConstants/LGPFlags.h"
#include "../LGPUtil/LGPRandom.h"
#include <sstream>

LGPSurvivalInstruction_Probablistic::LGPSurvivalInstruction_Probablistic()
: LGPSurvivalInstruction()
, m_reproduction_probability(1)
{

}

LGPSurvivalInstruction_Probablistic::LGPSurvivalInstruction_Probablistic(TiXmlElement* xml_level1)
: LGPSurvivalInstruction(xml_level1)
{
	for(TiXmlElement* xml_level2=xml_level1->FirstChildElement(); xml_level2 != NULL; xml_level2=xml_level2->NextSiblingElement())
	{
		if(strcmp(xml_level2->Value(), "param")==0)
		{
			if(strcmp(xml_level2->Attribute("name"), "reproduction_probability")==0)
			{
				xml_level2->QueryDoubleAttribute("value", &m_reproduction_probability);
			}
		}
	}
}

LGPSurvivalInstruction_Probablistic::~LGPSurvivalInstruction_Probablistic()
{

}

LGPSurvivalInstruction* LGPSurvivalInstruction_Probablistic::Clone() const
{
	return new LGPSurvivalInstruction_Probablistic(*this);
}

LGPSurvivalInstruction_Probablistic::LGPSurvivalInstruction_Probablistic(const LGPSurvivalInstruction_Probablistic& rhs)
{
	m_reproduction_probability=rhs.m_reproduction_probability;
}

std::string LGPSurvivalInstruction_Probablistic::ToString() const
{
	std::ostringstream oss;

	oss << ">> Name: LGPSurvivalInstruction_Probablistic" << std::endl;
	oss << ">> Reproduction Probability: " << this->m_reproduction_probability;

	return oss.str();
}

LGPProgram* LGPSurvivalInstruction_Probablistic::Compete(LGPPop *lgpPop, LGPProgram *weak_program_in_current_pop, LGPProgram *child_program)
{
	double r=lgpRandom.nextDouble();

	if(r < m_reproduction_probability || child_program->IsBetterThan(weak_program_in_current_pop))
	{
		lgpPop->Replace(weak_program_in_current_pop, child_program);
		return weak_program_in_current_pop;
	}

	return child_program;
}