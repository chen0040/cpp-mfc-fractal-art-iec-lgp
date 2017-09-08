#include "stdafx.h"
#include "LGPCrossoverInstructionFactory.h"
#include "../LGPConstants/LGPFlags.h"
#include "../LGPUtil/LGPExitSystem.h"
#include "../tinyxml/tinyxml.h"
#include "LGPCrossoverInstruction_Linear.h"
#include "LGPCrossoverInstruction_OnePoint.h"
#include "LGPCrossoverInstruction_OneSeg.h"
#include <sstream>
#include <iostream>

LGPCrossoverInstructionFactory::LGPCrossoverInstructionFactory(const char* filename)
: m_current_crossover(NULL)
{
	TiXmlDocument doc;
	if(! doc.LoadFile(filename))
	{
		std::ostringstream oss;
		oss << "Failed to load " << filename;
		LGPExitSystem("LGPCrossoverInstructionFactory::LGPCrossoverInstructionFactory()", oss.str().c_str());
	}

	TiXmlElement* xml_root=doc.RootElement();

	for(TiXmlElement* xml_level1=xml_root->FirstChildElement(); xml_level1 != NULL; xml_level1=xml_level1->NextSiblingElement())
	{
		if(strcmp(xml_level1->Value(), "strategy")==0)
		{
			if(strcmp(xml_level1->Attribute("name"), xml_root->Attribute("strategy"))==0)
			{
				if(strcmp(xml_level1->Attribute("name"), "linear")==0)
				{
					m_current_crossover=new LGPCrossoverInstruction_Linear(xml_level1);
				}
				else if(strcmp(xml_level1->Attribute("name"), "one_point")==0)
				{
					m_current_crossover=new LGPCrossoverInstruction_OnePoint(xml_level1);
				}
				else if(strcmp(xml_level1->Attribute("name"), "one_seg")==0)
				{
					m_current_crossover=new LGPCrossoverInstruction_OneSeg(xml_level1);
				}
			}
		}
	}

#ifdef LGP_DEBUG
	if(m_current_crossover == NULL)
	{
		LGPExitSystem("LGPCrossoverInstructionFactory::LGPCrossoverInstructionFactory()", "m_current_crossover == NULL");
	}
#endif

}

LGPCrossoverInstructionFactory::~LGPCrossoverInstructionFactory()
{
	if(m_current_crossover != NULL)
	{
		delete m_current_crossover;
		m_current_crossover=NULL;
	}
}

LGPCrossoverInstructionFactory* LGPCrossoverInstructionFactory::Clone() const
{
	return new LGPCrossoverInstructionFactory(*this);
}

LGPCrossoverInstructionFactory::LGPCrossoverInstructionFactory(const LGPCrossoverInstructionFactory& rhs)
{
	m_current_crossover=rhs.m_current_crossover->Clone();	
}

void LGPCrossoverInstructionFactory::Crossover(LGPPop* lgpPop, LGPProgram* child1, LGPProgram* child2)
{
#ifdef LGP_DEBUG
	if(m_current_crossover == NULL)
	{
		LGPExitSystem("LGPCrossoverInstructionFactory::Execute(LGPPop* lgpPop, LGPProgram* child1, LGPProgram* child2)", "m_current_crossover == NULL");
	}
#endif
	m_current_crossover->Crossover(lgpPop, child1, child2);
}

std::string LGPCrossoverInstructionFactory::ToString() const
{
	std::ostringstream oss;
	oss << m_current_crossover->ToString();

	return oss.str();
}