#include "stdafx.h"
#include "LGPRegInitInstructionFactory.h"
#include "../LGPUtil/LGPExitSystem.h"
#include "../LGPConstants/LGPFlags.h"
#include "LGPRegInitInstruction_Standard.h"
#include "LGPRegInitInstruction_CompleteInputInitReg.h"
#include <sstream>
#include <iostream>

LGPRegInitInstructionFactory::LGPRegInitInstructionFactory(const char* filename)
: m_reg_initializer(NULL)
{
	TiXmlDocument doc;
	if(!doc.LoadFile(filename))
	{
		std::ostringstream oss;
		oss << "Failed to load " << filename;
		LGPExitSystem("LGPRegInitInstructionFactory::LGPRegInitInstructionFactory(const char* filename)", oss.str().c_str());
	}

	TiXmlElement* xml_root=doc.RootElement();
	for(TiXmlElement* xml_level1=xml_root->FirstChildElement(); xml_level1 != NULL; xml_level1=xml_level1->NextSiblingElement())
	{
		if(strcmp(xml_level1->Value(), "strategy")==0)
		{
			if(strcmp(xml_level1->Attribute("name"), xml_root->Attribute("strategy"))==0)
			{
				if(strcmp(xml_level1->Attribute("name"), "initialize_register_with_input")==0)
				{
					m_reg_initializer=new LGPRegInitInstruction_Standard(xml_level1);
				}
				else if(strcmp(xml_level1->Attribute("name"), "complete_initialization_of_register_with_input")==0)
				{
					m_reg_initializer=new LGPRegInitInstruction_CompleteInputInitReg(xml_level1);
				}
			}
		}
	}

#ifdef LGP_DEBUG
	if(m_reg_initializer==NULL)
	{
		LGPExitSystem("LGPRegInitInstructionFactory::LGPRegInitInstructionFactory(const char* filename)", "m_reg_initializer==NULL");
	}
#endif
}

LGPRegInitInstructionFactory::~LGPRegInitInstructionFactory()
{
	if(m_reg_initializer != NULL)
	{
		delete m_reg_initializer;
		m_reg_initializer=NULL;
	}
}

LGPRegInitInstructionFactory::LGPRegInitInstructionFactory(const LGPRegInitInstructionFactory &rhs)
{
#ifdef LGP_DEBUG
	if(m_reg_initializer==NULL)
	{
		LGPExitSystem("LGPRegInitInstructionFactory::LGPRegInitInstructionFactory(const LGPRegInitInstructionFactory &rhs)", "m_reg_initializer==NULL");
	}
#endif
	m_reg_initializer=rhs.m_reg_initializer->Clone();
}

LGPRegInitInstructionFactory* LGPRegInitInstructionFactory::Clone() const
{
	return new LGPRegInitInstructionFactory(*this);
}

void LGPRegInitInstructionFactory::InitializeRegisters(LGPRegisterSet* reg_set, LGPConstantSet* constant_set, const LGPFitnessCase *fitness_case)
{
#ifdef LGP_DEBUG
	if(m_reg_initializer==NULL)
	{
		LGPExitSystem("LGPRegInitInstructionFactory::InitializeRegisters(LGPRegisterSet *reg_set, const LGPFitnessCase *fitness_case)", "m_reg_initializer==NULL");
	}
#endif
	m_reg_initializer->InitializeRegisters(reg_set, constant_set, fitness_case);
}

std::string LGPRegInitInstructionFactory::ToString() const
{
#ifdef LGP_DEBUG
	if(m_reg_initializer==NULL)
	{
		LGPExitSystem("LGPRegInitInstructionFactory::ToString() const", "m_reg_initializer==NULL");
	}
#endif

	std::ostringstream oss;
	oss << m_reg_initializer->ToString() << std::endl;
	return oss.str();
}

int LGPRegInitInstructionFactory::GetInputInitializedRegisterCount() const
{
#ifdef LGP_DEBUG
	if(m_reg_initializer==NULL)
	{
		LGPExitSystem("LGPRegInitInstructionFactory::GetInputInitializedRegisterCount() const", "m_reg_initializer==NULL");
	}
#endif

	return m_reg_initializer->GetInputInitializedRegisterCount();
}

double LGPRegInitInstructionFactory::GetDefaultRegValue() const
{
#ifdef LGP_DEBUG
	if(m_reg_initializer==NULL)
	{
		LGPExitSystem("LGPRegInitInstructionFactory::GetDefaultRegValue() const", "m_reg_initializer==NULL");
	}
#endif

	return m_reg_initializer->GetDefaultRegValue();
}