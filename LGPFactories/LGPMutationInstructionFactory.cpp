#include "stdafx.h"
#include "LGPMutationInstructionFactory.h"
#include "../LGPComp/LGPPop.h"
#include "LGPMutationInstruction_Macro.h"
#include "../tinyxml/tinyxml.h"
#include "../LGPUtil/LGPExitSystem.h"
#include "../LGPConstants/LGPFlags.h"
#include <sstream>

LGPMutationInstructionFactory::LGPMutationInstructionFactory(const char* filename)
: m_current_macro_mutation(NULL)
{
	TiXmlDocument doc;
	if(!doc.LoadFile(filename))
	{
		std::ostringstream oss;
		oss << "Failed to load " << filename;
		LGPExitSystem("LGPMutationInstructionFactory::LGPMutationInstructionFactory()", oss.str().c_str());
	}

	TiXmlElement* xml_root=doc.RootElement();
	for(TiXmlElement* xml_level1=xml_root->FirstChildElement(); xml_level1 != NULL; xml_level1=xml_level1->NextSiblingElement())
	{
		if(strcmp(xml_level1->Value(), "strategy")==0)
		{
			if(strcmp(xml_level1->Attribute("name"), xml_root->Attribute("strategy"))==0)
			{
				if(strcmp(xml_level1->Attribute("name"), "macro_mutation")==0)
				{
					m_current_macro_mutation=new LGPMutationInstruction_Macro(xml_level1);
				}
			}
		}
	}

#ifdef LGP_DEBUG
	if(m_current_macro_mutation == NULL)
	{
		LGPExitSystem("LGPMutationInstructionFactory::LGPMutationInstructionFactory()", "m_current_macro_mutation == NULL");
	}
#endif
}

LGPMutationInstructionFactory::~LGPMutationInstructionFactory()
{
	if(m_current_macro_mutation != NULL)
	{
		delete m_current_macro_mutation;
		m_current_macro_mutation=NULL;
	}
}

LGPMutationInstructionFactory::LGPMutationInstructionFactory(const LGPMutationInstructionFactory &rhs)
{
#ifdef LGP_DEBUG
	if(m_current_macro_mutation == NULL)
	{
		LGPExitSystem("LGPMutationInstructionFactory::LGPMutationInstructionFactory(const LGPMutationInstructionFactory &rhs)", "m_current_macro_mutation == NULL");
	}
#endif
	m_current_macro_mutation=rhs.m_current_macro_mutation->Clone();
}

void LGPMutationInstructionFactory::Mutate(LGPPop* lgpPop, LGPProgram* child1, LGPProgram* child2)
{
#ifdef LGP_DEBUG
	if(m_current_macro_mutation == NULL)
	{
		LGPExitSystem("LGPMutationInstructionFactory::Execute(LGPPop* lgpPop, LGPProgram* child1, LGPProgram* child2)", "m_current_macro_mutation == NULL");
	}
#endif
	m_current_macro_mutation->Mutate(lgpPop, child1, child2);

}

void LGPMutationInstructionFactory::Mutate(LGPPop* lgpPop, LGPProgram* child)
{
#ifdef LGP_DEBUG
	if(m_current_macro_mutation == NULL)
	{
		LGPExitSystem("LGPMutationInstructionFactory::Execute(LGPPop* lgpPop, LGPProgram* child)", "m_current_macro_mutation == NULL");
	}
#endif
	m_current_macro_mutation->Mutate(lgpPop, child);

}


LGPMutationInstructionFactory* LGPMutationInstructionFactory::Clone() const
{
	return new LGPMutationInstructionFactory(*this);
}

std::string LGPMutationInstructionFactory::ToString() const
{
	std::ostringstream oss;
	oss << m_current_macro_mutation->ToString();

	return oss.str();
}