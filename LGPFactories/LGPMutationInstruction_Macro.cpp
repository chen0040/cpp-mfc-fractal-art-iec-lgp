#include "stdafx.h"
#include "LGPMutationInstruction_Macro.h"
#include "../LGPComp/LGPProgram.h"
#include "../LGPComp/LGPPop.h"
#include "../LGPUtil/LGPRandom.h"
#include <sstream>

LGPMutationInstruction_Macro::LGPMutationInstruction_Macro()
: LGPMutationInstruction()
, m_macro_mutate_insertion_rate(0.5)
, m_macro_mutate_deletion_rate(0.5)
, m_effective_mutation(false)
, m_macro_mutate_max_program_length(100)
, m_macro_mutate_min_program_length(20)
{

}

LGPMutationInstruction_Macro::LGPMutationInstruction_Macro(const LGPMutationInstruction_Macro& rhs)
{
	this->m_macro_mutate_insertion_rate=rhs.m_macro_mutate_insertion_rate;
	this->m_macro_mutate_deletion_rate=rhs.m_macro_mutate_deletion_rate;
	this->m_macro_mutate_max_program_length=rhs.m_macro_mutate_max_program_length;
	this->m_macro_mutate_min_program_length=rhs.m_macro_mutate_min_program_length;
	this->m_effective_mutation=rhs.m_effective_mutation;
}

LGPMutationInstruction_Macro::LGPMutationInstruction_Macro(TiXmlElement* xml_level1)
: LGPMutationInstruction(xml_level1)
{
	for(TiXmlElement* xml_level2=xml_level1->FirstChildElement(); xml_level2 != NULL; xml_level2=xml_level2->NextSiblingElement())
	{
		if(strcmp(xml_level2->Value(), "param")==0)
		{
			if(strcmp(xml_level2->Attribute("name"), "insertion_mutation_probability")==0)
			{
				xml_level2->QueryDoubleAttribute("value", &m_macro_mutate_insertion_rate);
					
			}
			else if(strcmp(xml_level2->Attribute("name"), "deletion_mutation_probability")==0)
			{
				xml_level2->QueryDoubleAttribute("value", &m_macro_mutate_deletion_rate);
			}
			else if(strcmp(xml_level2->Attribute("name"), "min_program_length")==0)
			{
				int value;
				xml_level2->QueryIntAttribute("value", &value);
				m_macro_mutate_min_program_length=value;
			}
			else if(strcmp(xml_level2->Attribute("name"), "max_program_length")==0)
			{
				int value;
				xml_level2->QueryIntAttribute("value", &value);
				m_macro_mutate_max_program_length=value;
			}
			else if(strcmp(xml_level2->Attribute("name"), "effective_mutation")==0)
			{
				if(strcmp(xml_level2->Attribute("value"), "true")==0)
				{
					m_effective_mutation=true;
				}
				else
				{
					m_effective_mutation=false;
				}
			}
		}
	}

	m_macro_mutate_insertion_rate /= (m_macro_mutate_insertion_rate + m_macro_mutate_deletion_rate);
	m_macro_mutate_deletion_rate = 1 - m_macro_mutate_insertion_rate;
}

LGPMutationInstruction_Macro::~LGPMutationInstruction_Macro()
{

}

void LGPMutationInstruction_Macro::Mutate(LGPPop* lgpPop, LGPProgram* child)
{
	// Xianshun says:
	// This is derived from Algorithm 6.1 (Section 6.2.1) of Linear Genetic Programming
	// Macro instruction mutations either insert or delete a single instruction.
	// In doing so, they change absolute program length with minimum step size on the 
	// level of full instructions, the macro level. On the functional level , a single 
	// node is inserted in or deleted from the program graph, together with all 
	// its connecting edges.
	// Exchanging an instruction or change the position of an existing instruction is not 
	// regarded as macro mutation. Both of these variants are on average more 
	// destructive, i.e. they imply a larger variation step size, since they include a deletion
	// and an insertion at the same time. A further, but important argument against 
	// substitutios of single instructions is that these do not vary program length. If
	// single instruction would only be exchanged there would be no code growth.

	double r=lgpRandom.nextDouble();
	std::vector<LGPInstruction*>& instructions=child->GetMutableRawInstruction();
	if(child->GetInstructionCount() < m_macro_mutate_max_program_length && ((r < m_macro_mutate_insertion_rate)  || child->GetInstructionCount() == m_macro_mutate_min_program_length))
	{
		LGPInstruction* inserted_instruction=new LGPInstruction(child);
		inserted_instruction->Create();
		unsigned int loc=lgpRandom.nextInt(static_cast<unsigned int>(instructions.size()));
		if(loc==instructions.size() - 1)
		{
			instructions.push_back(inserted_instruction);
		}
		else
		{
			instructions.insert(instructions.begin() + loc, inserted_instruction);
		}

		if(m_effective_mutation)
		{
			while(instructions[loc]->IsConditionalConstruct() && loc < instructions.size())
			{
				loc++;
			}
			if(loc < instructions.size())
			{
				std::set<unsigned int> Reff;
				child->MarkStructuralIntrons(loc, Reff);
				if(!Reff.empty())
				{
					std::set<unsigned int>::iterator pos_reff;
					unsigned int iRegisterIndex=0;
					for(pos_reff = Reff.begin(); pos_reff != Reff.end(); ++pos_reff)
					{
						if(pos_reff == Reff.begin())
						{
							iRegisterIndex=*pos_reff;
						}
						else if(lgpRandom.nextDouble() < 0.5)
						{
							iRegisterIndex=*pos_reff;
						}
					}
					instructions[loc]->SetDestinationRegister(child->GetRegisterSet()->GetRegister(iRegisterIndex));
				}
			}
		}
	}
	else if(child->GetInstructionCount() > m_macro_mutate_min_program_length && ((r > m_macro_mutate_insertion_rate) || child->GetInstructionCount() == m_macro_mutate_max_program_length))
	{
		unsigned int loc=lgpRandom.nextInt(static_cast<unsigned int>(instructions.size()));
		if(m_effective_mutation)
		{
			for(int i=0; i<10; i++)
			{
				loc=lgpRandom.nextInt(static_cast<unsigned int>(instructions.size()));
				if(! instructions[loc]->IsStructuralIntron())
				{
					break;
				}
			}
		}

		delete instructions[loc];
		instructions.erase(instructions.begin()+loc);
	}

	child->TrashFitness();
}

LGPMutationInstruction* LGPMutationInstruction_Macro::Clone() const
{
	return new LGPMutationInstruction_Macro(*this);
}
std::string LGPMutationInstruction_Macro::ToString() const
{
	std::ostringstream oss;

	oss << ">> Name: LGPMutationInstruction_Macro" << std::endl;
	oss << ">> Insertion mutation probability: " << m_macro_mutate_insertion_rate * 100 << "%" << std::endl;
	oss << ">> Deletion mutation probability: " << m_macro_mutate_deletion_rate * 100 << "%" << std::endl;
	oss << ">> Max Program Length: " << m_macro_mutate_max_program_length << std::endl;
	oss << ">> Min Program Length: " << m_macro_mutate_min_program_length << std::endl;

	if(m_effective_mutation)
	{
		oss << ">> Effective Mutation: true" << std::endl;
	}
	else
	{
		oss << ">> Effective Mutation: false" << std::endl;
	}

	return oss.str();
}