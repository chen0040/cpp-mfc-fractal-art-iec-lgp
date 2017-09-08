#include "stdafx.h"
#include "LGPCrossoverInstruction_OnePoint.h"
#include "../LGPConstants/LGPFlags.h"
#include "../LGPUtil/LGPExitSystem.h"
#include "../LGPUtil/LGPRandom.h"
#include "../LGPComp/LGPPop.h"
#include "../LGPComp/LGPProgram.h"
#include <sstream>
#include <iostream>

LGPCrossoverInstruction_OnePoint::LGPCrossoverInstruction_OnePoint()
: LGPCrossoverInstruction()
, m_max_distance_of_crossover_points(1)
, m_max_program_length(100)
, m_min_program_length(1)
{

}

LGPCrossoverInstruction_OnePoint::LGPCrossoverInstruction_OnePoint(TiXmlElement* xml_level1)
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
			else if(strcmp(xml_level2->Attribute("name"), "max_distance_of_crossover_points")==0)
			{
				int value;
				xml_level2->QueryIntAttribute("value", &value);
				this->m_max_distance_of_crossover_points=value;
			}
		}
	}
}

LGPCrossoverInstruction_OnePoint::~LGPCrossoverInstruction_OnePoint()
{

}

LGPCrossoverInstruction_OnePoint::LGPCrossoverInstruction_OnePoint(const LGPCrossoverInstruction_OnePoint& rhs)
{
	m_max_program_length=rhs.m_max_program_length;
	m_min_program_length=rhs.m_min_program_length;
	m_max_distance_of_crossover_points=rhs.m_max_distance_of_crossover_points;
}

std::string LGPCrossoverInstruction_OnePoint::ToString() const
{
	std::ostringstream oss;

	oss << ">> Name: LGPCrossoverInstruction_OnePoint" << std::endl;
	oss << ">> Max Program Length: " << m_max_program_length << std::endl;
	oss << ">> Min Program Length: " << m_min_program_length << std::endl;
	oss << ">> Max Distance Between Crossover Points: " << m_max_distance_of_crossover_points;
	return oss.str();
}

LGPCrossoverInstruction* LGPCrossoverInstruction_OnePoint::Clone() const
{
	return new LGPCrossoverInstruction_OnePoint(*this);
}

void LGPCrossoverInstruction_OnePoint::Crossover(LGPPop *lgpPop, LGPProgram *child1, LGPProgram *child2)
{
	LGPProgram* gp1=child1;
	LGPProgram* gp2=child2;
	// ensure l(gp1) <= l(gp2)
	if(gp1->GetInstructionCount() > gp2->GetInstructionCount())
	{
		gp1=child2;
		gp2=child1;
	}

	unsigned int max_distance_of_crossover_points=(gp1->GetInstructionCount()-1) < m_max_distance_of_crossover_points ? (gp1->GetInstructionCount()-1) : m_max_distance_of_crossover_points;

	unsigned int i1=lgpRandom.nextInt(gp1->GetInstructionCount());
	unsigned int i2=lgpRandom.nextInt(gp2->GetInstructionCount());
	
	unsigned int crossover_point_distance=(i1 > i2) ? (i1-i2) : (i2-i1);

	unsigned int ls1=gp1->GetInstructionCount() - i1;
	unsigned int ls2=gp2->GetInstructionCount() - i2;

	// 1. assure abs(i1-i2) <= max_distance_of_crossover_points
	// 2. assure l(s1) <= l(s2)
	bool not_feasible=true;
	while(not_feasible)
	{
		not_feasible=false;
		// ensure that the maximum distance between two crossover points is not exceeded
		if(crossover_point_distance > max_distance_of_crossover_points)
		{
			not_feasible=true;
			i1=lgpRandom.nextInt(gp1->GetInstructionCount());
			i2=lgpRandom.nextInt(gp2->GetInstructionCount());
			crossover_point_distance=(i1 > i2) ? (i1-i2) : (i2-i1);
		}
		else
		{
			ls1=gp1->GetInstructionCount() - i1;
			ls2=gp2->GetInstructionCount() - i2;
			// assure than l(s1) <= l(s2)
			if(ls1 > ls2)
			{
				not_feasible=true;
				i1=lgpRandom.nextInt(gp1->GetInstructionCount());
				i2=lgpRandom.nextInt(gp2->GetInstructionCount());
				crossover_point_distance=(i1 > i2) ? (i1-i2) : (i2-i1);
			}
			else
			{
				// assure the length of the program after crossover do not exceed the maximum program length or below minimum program length
				if((gp2->GetInstructionCount() - (ls2-ls1)) < m_min_program_length || (gp1->GetInstructionCount() + (ls2-ls1)) > m_max_program_length)
				{
					not_feasible=true;	
					// when the length constraint is not satisfied, make the segments to be exchanged the same length
					if(gp1->GetInstructionCount() >= gp2->GetInstructionCount())
					{
						i1=i2;
					}
					else
					{
						i2=i1;
					}
					crossover_point_distance=0;
				}
				else
				{
					not_feasible=false;
				}
			}
		}

		/*
		std::cout << "before crossover: " << std::endl;
		std::cout << "gp1: " << std::endl;
		std::cout << gp1->ToString() << std::endl;
		std::cout << "gp2: " << std::endl;
		std::cout << gp2->ToString() << std::endl;
		*/

		std::vector<LGPInstruction*>& instructions1=gp1->GetMutableRawInstruction();
		std::vector<LGPInstruction*>& instructions2=gp2->GetMutableRawInstruction();

		std::vector<LGPInstruction*> s1(instructions1.begin() + i1, instructions1.end());
		std::vector<LGPInstruction*> s2(instructions2.begin() + i2, instructions2.end());

		instructions1.erase(instructions1.begin()+i1, instructions1.end());
		instructions2.erase(instructions2.begin()+i2, instructions2.end());

		instructions1.reserve(instructions1.size()+s2.size());
		instructions2.reserve(instructions2.size()+s1.size());

		for(size_t k=0; k<s2.size(); ++k)
		{
			s2[k]->SetOwnership(gp1);
			instructions1.push_back(s2[k]);
		}

		for(size_t k=0; k<s1.size(); ++k)
		{
			s1[k]->SetOwnership(gp2);
			instructions2.push_back(s1[k]);
		}

		gp1->TrashFitness();
		gp2->TrashFitness();

		/*
		std::cout << "after crossover: " << std::endl;
		std::cout << "gp1: " << std::endl;
		std::cout << gp1->ToString() << std::endl;
		std::cout << "gp2: " << std::endl;
		std::cout << gp2->ToString() << std::endl;
		*/
	}

	

	

}