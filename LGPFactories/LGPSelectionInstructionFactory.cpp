#include "stdafx.h"
#include "LGPSelectionInstructionFactory.h"
#include "../LGPConstants/LGPFlags.h"
#include "../LGPUtil/LGPExitSystem.h"
#include <sstream>
#include "LGPSelectionInstruction_Tournament.h"

LGPSelectionInstructionFactory::LGPSelectionInstructionFactory(const char* filename)
: m_current_selector(NULL)
{
	TiXmlDocument doc;
	if(!doc.LoadFile(filename))
	{
		std::ostringstream oss;
		oss << "Failed to load " << filename;
		LGPExitSystem("LGPSelectionInstructionFactory::LGPSelectionInstructionFactory(const char* filename)", oss.str().c_str());
	}

	TiXmlElement* xml_root=doc.RootElement();
	for(TiXmlElement* xml_level1=xml_root->FirstChildElement(); xml_level1 != NULL; xml_level1 = xml_level1->NextSiblingElement())
	{
		if(strcmp(xml_level1->Attribute("name"), xml_root->Attribute("strategy"))==0)
		{
			if(strcmp(xml_level1->Attribute("name"), "tournament")==0)
			{
				m_current_selector=new LGPSelectionInstruction_Tournament(xml_level1);
			}
		}
	}
#ifdef LGP_DEBUG
	if(m_current_selector==NULL)
	{
		LGPExitSystem("LGPSelectionInstructionFactory::LGPSelectionInstructionFactory(const char* filename)", "m_current_selector==NULL");
	}
#endif
}

LGPSelectionInstructionFactory::~LGPSelectionInstructionFactory()
{
	if(m_current_selector!=NULL)
	{
		delete m_current_selector;
		m_current_selector=NULL;
	}
}

LGPProgram* LGPSelectionInstructionFactory::Select(LGPPop* lgpPop)
{
#ifdef LGP_DEBUG
	if(m_current_selector==NULL)
	{
		LGPExitSystem("LGPSelectionInstructionFactory::Select(LGPPop* lgpPop)", "m_current_selector==NULL");
	}
#endif
	return m_current_selector->Select(lgpPop);
}

LGPSelectionInstructionFactory::LGPSelectionInstructionFactory(const LGPSelectionInstructionFactory& rhs)
{
	m_current_selector=rhs.m_current_selector->Clone();
}

std::string LGPSelectionInstructionFactory::ToString() const
{
	return m_current_selector->ToString();
}

void LGPSelectionInstructionFactory::Select(LGPPop* lgpPop, std::pair<LGPProgram*, LGPProgram*>& best_pair, std::pair<LGPProgram*, LGPProgram*>& worst_pair)
{
#ifdef LGP_DEBUG
	if(m_current_selector==NULL)
	{
		LGPExitSystem("LGPSelectionInstructionFactory::Select(LGPPop* lgpPop, std::pair<LGPProgram*, LGPProgram*>& pair)", "m_current_selector==NULL");
	}
#endif
	return m_current_selector->Select(lgpPop, best_pair, worst_pair);
}

