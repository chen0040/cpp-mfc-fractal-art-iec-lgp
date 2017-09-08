#include "stdafx.h"
#include "LGPCrossoverInstruction_Linear.h"
#include "../LGPComp/LGPPop.h"
#include "../LGPComp/LGPProgram.h"
#include "../LGPUtil/LGPRandom.h"
#include "../LGPConstants/LGPFlags.h"
#include "../LGPUtil/LGPExitSystem.h"
#include <sstream>
#include <iostream>

LGPCrossoverInstruction_Linear::LGPCrossoverInstruction_Linear()
: LGPCrossoverInstruction()
, m_max_program_length(100)
, m_min_program_length(20)
, m_max_segment_length(10)
, m_max_distance_of_crossover_points(10)
, m_max_difference_of_segment_length(5)
{

}

LGPCrossoverInstruction_Linear::LGPCrossoverInstruction_Linear(TiXmlElement* xml_level1)
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
			else if(strcmp(xml_level2->Attribute("name"), "max_distance_of_crossover_points")==0)
			{
				int value;
				xml_level2->QueryIntAttribute("value", &value);
				this->m_max_distance_of_crossover_points=value;
			}
			else if(strcmp(xml_level2->Attribute("name"), "max_difference_in_segment_length")==0)
			{
				int value;
				xml_level2->QueryIntAttribute("value", &value);
				this->m_max_difference_of_segment_length=value;
			}
		}
	}
}

LGPCrossoverInstruction_Linear::~LGPCrossoverInstruction_Linear()
{

}

LGPCrossoverInstruction* LGPCrossoverInstruction_Linear::Clone() const
{
	return new LGPCrossoverInstruction_Linear(*this);
}

std::string LGPCrossoverInstruction_Linear::ToString() const
{
	std::ostringstream oss;

	oss << ">> Name: LGPCrossoverInstruction_Linear" << std::endl;
	oss << ">> Max Program Length: " << this->m_max_program_length << std::endl;
	oss << ">> Min Program Length: " << this->m_min_program_length << std::endl;
	oss << ">> Max Distance of Crossover Points: " << this->m_max_distance_of_crossover_points << std::endl;
	oss << ">> Max Difference in Segment Length: " << this->m_max_difference_of_segment_length << std::endl;

	return oss.str();
}

void LGPCrossoverInstruction_Linear::Crossover(LGPPop *lgpPop, LGPProgram *child1, LGPProgram *child2)
{
	// Xianshun says:
	// this implementation is derived from Algorithm 5.1 in Section 5.7.1 of Linear
	// Genetic Programming

	LGPProgram* gp1=child1;
	LGPProgram* gp2=child2;

	// length(gp1) >= length(gp2)
	if(gp1->GetInstructionCount() > gp2->GetInstructionCount())
	{
		gp1=child2;
		gp2=child1;
	}

	// select i1 from gp1 and i2 from gp2 such that abs(i1-i2) <= max_crossover_point_distance
	// max_crossover_point_distance=min{length(gp1) - 1, m_max_distance_of_crossover_points}
	unsigned int i1=lgpRandom.nextInt(gp1->GetInstructionCount());
	unsigned int i2=lgpRandom.nextInt(gp2->GetInstructionCount());
	unsigned int crossover_point_distance=(i1 > i2) ? (i1 - i2) : (i2 - i1);
	unsigned int max_crossover_point_distance=(gp1->GetInstructionCount() -1) > m_max_distance_of_crossover_points ? m_max_distance_of_crossover_points : (gp1->GetInstructionCount() - 1);
	while(crossover_point_distance > max_crossover_point_distance)
	{ 
		i1=lgpRandom.nextInt(gp1->GetInstructionCount());
		i2=lgpRandom.nextInt(gp2->GetInstructionCount());
		crossover_point_distance=(i1 > i2) ? (i1 - i2) : (i2 - i1);
	}

	unsigned int s1_max=(gp1->GetInstructionCount() - i1) > m_max_difference_of_segment_length ? m_max_difference_of_segment_length : (gp1->GetInstructionCount() - i1);
	unsigned int s2_max=(gp2->GetInstructionCount() - i2) > m_max_difference_of_segment_length ? m_max_difference_of_segment_length : (gp2->GetInstructionCount() - i2);
	
	// select s1 from gp1 (start at i1) and s2 from gp2 (start at i2)
	// such that length(s1) <= length(s2)
	// and abs(length(s1) - length(s2)) <= m_max_difference_of_segment_length)
	unsigned int ls1=1 + lgpRandom.nextInt(s1_max);
	unsigned int ls2=1 + lgpRandom.nextInt(s2_max);
	unsigned int lsd=(ls1 > ls2) ? (ls1 - ls2) : (ls2 - ls1);
	while((ls1 > ls2) && (lsd > m_max_difference_of_segment_length))
	{
		ls1=1 + lgpRandom.nextInt(s1_max);
		ls2=1 + lgpRandom.nextInt(s2_max);
		lsd=(ls1 > ls2) ? (ls1 - ls2) : (ls2 - ls1);
	}

	if(((gp2->GetInstructionCount() - (ls2 - ls1)) < m_min_program_length) || ((gp1->GetInstructionCount() + (ls2 - ls1)) > m_max_program_length))
	{
		if(lgpRandom.nextDouble() < 0.5)
		{
			ls2=ls1;
		}
		else
		{
			ls1=ls2;
		}
		if((i1 + ls1) > gp1->GetInstructionCount())
		{
			ls1=ls2=gp1->GetInstructionCount() - i1;
		}
	}

	std::vector<LGPInstruction*>& instructions1=gp1->GetMutableRawInstruction();
	std::vector<LGPInstruction*>& instructions2=gp2->GetMutableRawInstruction();

	std::vector<LGPInstruction*> s1(instructions1.begin()+i1, instructions1.begin()+(i1+ls1));
	std::vector<LGPInstruction*> s2(instructions2.begin()+i2, instructions2.begin()+(i2+ls2));

	instructions1.erase(instructions1.begin()+i1, instructions1.begin()+(i1+ls1));
	instructions2.erase(instructions2.begin()+i2, instructions2.begin()+(i2+ls2));

	std::vector<LGPInstruction*>::iterator pos_instruction;
	for(pos_instruction=s1.begin(); pos_instruction != s1.end(); ++pos_instruction)
	{
		(*pos_instruction)->SetOwnership(gp2);
	}
	for(pos_instruction=s2.begin(); pos_instruction != s2.end(); ++pos_instruction)
	{
		(*pos_instruction)->SetOwnership(gp1);
	}

	instructions1.insert(instructions1.begin()+i1, s2.begin(), s2.end());
	instructions2.insert(instructions2.begin()+i2, s1.begin(), s1.end());

	/*
	for(size_t i=0; i<s1.size(); i++)
	{
		std::cout << "s1[" << i << "]: " << s1[i]->ToString() << std::endl;
	}

	for(size_t i=0; i<s2.size(); i++)
	{
		std::cout << "s2[" << i << "]: " << s2[i]->ToString() << std::endl;
	}
	*/

	gp1->TrashFitness();
	gp2->TrashFitness();
}

LGPCrossoverInstruction_Linear::LGPCrossoverInstruction_Linear(const LGPCrossoverInstruction_Linear &rhs)
{
	this->m_max_difference_of_segment_length=rhs.m_max_difference_of_segment_length;
	this->m_max_distance_of_crossover_points=rhs.m_max_distance_of_crossover_points;
	this->m_max_program_length=rhs.m_max_program_length;
	this->m_max_segment_length=rhs.m_max_segment_length;
	this->m_min_program_length=rhs.m_min_program_length;
}	