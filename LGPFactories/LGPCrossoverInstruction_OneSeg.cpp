#include "stdafx.h"
#include "LGPCrossoverInstruction_OneSeg.h"
#include "../LGPConstants/LGPFlags.h"
#include "../LGPUtil/LGPExitSystem.h"
#include "../LGPUtil/LGPRandom.h"
#include "../LGPComp/LGPPop.h"
#include "../LGPComp/LGPProgram.h"
#include <sstream>
#include <iostream>

LGPCrossoverInstruction_OneSeg::LGPCrossoverInstruction_OneSeg()
: LGPCrossoverInstruction()
, m_max_segment_length(10)
, m_max_program_length(200)
, m_min_program_length(1)
, m_insertion_probability(0.5)
{

}

LGPCrossoverInstruction_OneSeg::LGPCrossoverInstruction_OneSeg(TiXmlElement* xml_level1)
: LGPCrossoverInstruction(xml_level1)
{
	for(TiXmlElement* xml_level2=xml_level1->FirstChildElement(); xml_level2 != NULL; xml_level2=xml_level2->NextSiblingElement())
	{
		if(strcmp(xml_level2->Value(), "param")==0)
		{
			if(strcmp(xml_level2->Attribute("name"), "max_program_length")==0)
			{
				int value;
				xml_level2->QueryIntAttribute("value", &value);
				this->m_max_program_length=value;
			}
			else if(strcmp(xml_level2->Attribute("name"), "min_program_length")==0)
			{
				int value;
				xml_level2->QueryIntAttribute("value", &value);
				this->m_min_program_length=value;
			}
			else if(strcmp(xml_level2->Attribute("name"), "max_segment_length")==0)
			{
				int value;
				xml_level2->QueryIntAttribute("value", &value);
				this->m_max_segment_length=value;
			}
			else if(strcmp(xml_level2->Attribute("name"), "insertion_probability")==0)
			{
				xml_level2->QueryDoubleAttribute("value", &m_insertion_probability);
			}
		}
	}
}

LGPCrossoverInstruction_OneSeg::~LGPCrossoverInstruction_OneSeg()
{

}

LGPCrossoverInstruction_OneSeg::LGPCrossoverInstruction_OneSeg(const LGPCrossoverInstruction_OneSeg& rhs)
{
	m_max_program_length=rhs.m_max_program_length;
	m_min_program_length=rhs.m_min_program_length;
	m_max_segment_length=rhs.m_max_segment_length;
	m_insertion_probability=rhs.m_insertion_probability;
}

std::string LGPCrossoverInstruction_OneSeg::ToString() const
{
	std::ostringstream oss;

	oss << ">> Max Program Length: " << m_max_program_length << std::endl;
	oss << ">> Min Program Length: " << m_min_program_length << std::endl;
	oss << ">> Max Segment Length: " << m_max_segment_length << std::endl;
	oss << ">> Insertion Probability: " << m_insertion_probability * 100 << "%" << std::endl;
	oss << ">> Deletion Probability: " << (1-m_insertion_probability) * 100 << "%";

	return oss.str();
}

LGPCrossoverInstruction* LGPCrossoverInstruction_OneSeg::Clone() const
{
	return new LGPCrossoverInstruction_OneSeg(*this);
}

void LGPCrossoverInstruction_OneSeg::Crossover(LGPPop *lgpPop, LGPProgram *child1, LGPProgram *child2)
{
	CrossoverOneSegment(child1, child2);
	CrossoverOneSegment(child2, child1);
}

void LGPCrossoverInstruction_OneSeg::CrossoverOneSegment(LGPProgram* gp1, LGPProgram* gp2)
{
	double prob_r=lgpRandom.nextDouble();

	if((gp1->GetInstructionCount() < m_max_program_length) && ((prob_r <= m_insertion_probability) || gp1->GetInstructionCount()==m_min_program_length))
	{
		unsigned int i1=lgpRandom.nextInt(gp1->GetInstructionCount());
		unsigned int max_segment_length=(gp2->GetInstructionCount() < m_max_segment_length) ? gp2->GetInstructionCount() : m_max_segment_length;
		unsigned int ls2=1+lgpRandom.nextInt(max_segment_length);
		if(gp1->GetInstructionCount() + ls2 > m_max_program_length)
		{
			ls2=m_max_program_length - gp1->GetInstructionCount();
		}
		unsigned int i2=lgpRandom.nextInt(gp2->GetInstructionCount()-ls2);
		std::vector<LGPInstruction*>& instructions1=gp1->GetMutableRawInstruction();
		const std::vector<LGPInstruction*>& instructions2=gp2->GetConstRawInstructions();

		std::vector<LGPInstruction*>::const_iterator pos_s;
		std::vector<LGPInstruction*> s;
		s.reserve(ls2);
		for(pos_s=instructions2.begin()+i2; pos_s != instructions2.begin()+(i2+ls2); ++pos_s)
		{
			LGPInstruction* instruction_cloned=(*pos_s)->Clone();
			instruction_cloned->SetOwnership(gp1);
			s.push_back(instruction_cloned);
		}

		instructions1.insert(instructions1.begin()+i1, s.begin(), s.end());
	}
	if((gp1->GetInstructionCount() > m_min_program_length) && ((prob_r > m_insertion_probability) || gp1->GetInstructionCount() == m_max_program_length))
	{
		unsigned int max_segment_length=(gp2->GetInstructionCount() < m_max_segment_length) ? gp2->GetInstructionCount() : m_max_segment_length;
		unsigned int ls1=1+lgpRandom.nextInt(max_segment_length);
#ifdef LGP_DEBUG
		if(gp1->GetInstructionCount() < m_min_program_length)
		{
			LGPExitSystem("LGPCrossoverInstruction_OneSeg::CrossoverOneSegment(LGPProgram* gp1, LGPProgram* gp2)", "gp1->GetInstructionCount() < m_min_program_length");
		}
#endif
		if(gp1->GetInstructionCount() < ls1)
		{
			ls1=gp1->GetInstructionCount() - m_min_program_length;
		}
		else if(gp1->GetInstructionCount() - ls1 < m_min_program_length)
		{
			ls1=gp1->GetInstructionCount() - m_min_program_length;
		}
		unsigned int i1=lgpRandom.nextInt(gp1->GetInstructionCount()-ls1);
		std::vector<LGPInstruction*>& instructions1=gp1->GetMutableRawInstruction();

		std::vector<LGPInstruction*>::iterator pos_s;
		for(pos_s=instructions1.begin()+i1; pos_s != instructions1.begin()+(i1+ls1); ++pos_s)
		{
			delete (*pos_s);
		}
		instructions1.erase(instructions1.begin()+i1, instructions1.begin()+(i1+ls1));
	}

	gp1->TrashFitness();
}