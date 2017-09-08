#include "stdafx.h"
#include "LGPSelectionInstruction_Tournament.h"
#include <sstream>
#include <set>
#include "../LGPUtil/LGPRandom.h"
#include "../LGPComp/LGPPop.h"
#include "../LGPConstants/LGPFlags.h"
#include "../LGPUtil/LGPExitSystem.h"
#include <algorithm>
#include <iostream>

LGPSelectionInstruction_Tournament::LGPSelectionInstruction_Tournament()
: m_tournament_size(5)
{
}

LGPSelectionInstruction_Tournament::LGPSelectionInstruction_Tournament(TiXmlElement* xml_level1)
: LGPSelectionInstruction(xml_level1)
{
	for(TiXmlElement* xml_level2=xml_level1->FirstChildElement(); xml_level2 != NULL; xml_level2=xml_level2->NextSiblingElement())
	{
		if(strcmp(xml_level2->Value(), "param")==0)
		{
			if(strcmp(xml_level2->Attribute("name"), "tournament_size")==0)
			{
				int value;
				xml_level2->QueryIntAttribute("value", &value);
				m_tournament_size=value;
			}
		}
	}

#ifdef LGP_DEBUG
	if(m_tournament_size < 1)
	{
		LGPExitSystem("LGPSelectionInstruction_Tournament::LGPSelectionInstruction_Tournament(TiXmlElement* xml_level1)", "m_tournament_size < 1");
	}
#endif
}

LGPSelectionInstruction_Tournament::~LGPSelectionInstruction_Tournament()
{

}

void LGPSelectionInstruction_Tournament::Select(LGPPop* lgpPop, std::pair<LGPProgram*, LGPProgram*>& best_pair, std::pair<LGPProgram*, LGPProgram*>& worst_pair)
{
	std::vector<LGPProgram*> tournament1;
	std::vector<LGPProgram*> tournament2;
	unsigned int tournament_size2=m_tournament_size * 2;
	if(tournament_size2 > lgpPop->GetProgramCount())
	{
		tournament_size2=lgpPop->GetProgramCount();
		unsigned int tournament_size=tournament_size2 / 2;
		lgpPop->RandomShuffle();
		for(unsigned int i=0; i<tournament_size; i++)
		{
			tournament1.push_back(lgpPop->GetProgram(i));
		}
		for(unsigned int i=tournament_size; i<tournament_size2; i++)
		{
			tournament2.push_back(lgpPop->GetProgram(i));
		}
	}
	else
	{
		lgpPop->RandomShuffle();
		for(unsigned int i=0; i<m_tournament_size; i++)
		{
			tournament1.push_back(lgpPop->GetProgram(i));
		}
		for(unsigned int i=m_tournament_size; i<tournament_size2; i++)
		{
			tournament2.push_back(lgpPop->GetProgram(i));
		}
	}	

#ifdef LGP_DEBUG
	if(tournament1.empty())
	{
		LGPExitSystem("Select(LGPPop* lgpPop, std::pair<LGPProgram*, LGPProgram*>& best_pair, std::pair<LGPProgram*, LGPProgram*>& worst_pair, unsigned int best_count, unsigned int worst_count)", 
			"tournament1.empty()");
	}
	if(tournament2.empty())
	{
		LGPExitSystem("Select(LGPPop* lgpPop, std::pair<LGPProgram*, LGPProgram*>& best_pair, std::pair<LGPProgram*, LGPProgram*>& worst_pair, unsigned int best_count, unsigned int worst_count)",
			"tournament2.empty()");
	}
#endif

	std::sort(tournament1.begin(), tournament1.end(), LGPProgramSort_FittestFirst());
	std::sort(tournament2.begin(), tournament2.end(), LGPProgramSort_FittestFirst());

	/*
	std::cout << "tournament1: " << std::endl;
	
	for(size_t i=0; i<tournament1.size(); ++i)
	{
		std::cout << "program[" << i << "]: " << tournament1[i]->GetFitness() << std::endl;
	}

	std::cout << "tournament2: " << std::endl;
	for(size_t i=0; i<tournament2.size(); ++i)
	{
		std::cout << "program[" << i << "]: " << tournament2[i]->GetFitness() << std::endl;
	}
	exit(0);
	*/

	best_pair=std::make_pair<LGPProgram*, LGPProgram*>(tournament1[0], tournament2[0]);
	worst_pair=std::make_pair<LGPProgram*, LGPProgram*>(tournament1[tournament1.size()-1], tournament2[tournament2.size()-1]);
}

LGPProgram* LGPSelectionInstruction_Tournament::Select(LGPPop *lgpPop)
{
	std::set<LGPProgram*> tournament;
	while(tournament.size() < m_tournament_size)
	{
		unsigned int r=lgpRandom.nextInt(lgpPop->GetProgramCount());
		tournament.insert(lgpPop->GetProgram(r));
	}

	std::vector<LGPProgram*> programs(tournament.begin(), tournament.end());

	std::sort(programs.begin(), programs.end(), LGPProgramSort_FittestFirst());

	return *(programs.begin());
}

std::string LGPSelectionInstruction_Tournament::ToString() const
{
	std::ostringstream oss;

	oss << ">> Name: LGPSelectionInstruction_Tournament" << std::endl;
	oss << ">> Tournament Size: " << m_tournament_size << std::endl;

	return oss.str();
}

LGPSelectionInstruction_Tournament::LGPSelectionInstruction_Tournament(const LGPSelectionInstruction_Tournament& rhs)
{
	this->m_tournament_size=rhs.m_tournament_size;
}