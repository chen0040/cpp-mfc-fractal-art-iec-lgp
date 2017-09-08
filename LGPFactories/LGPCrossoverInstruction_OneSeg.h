#ifndef _H_LGP_CROSSOVER_INSTRUCTION_ONE_SEG_H
#define _H_LGP_CROSSOVER_INSTRUCTION_ONE_SEG_H

#include "LGPCrossoverInstruction.h"

class LGPCrossoverInstruction_OneSeg : public LGPCrossoverInstruction
{
public:
	LGPCrossoverInstruction_OneSeg();
	LGPCrossoverInstruction_OneSeg(TiXmlElement* xml_level1);
	virtual ~LGPCrossoverInstruction_OneSeg();

public:
	LGPCrossoverInstruction_OneSeg(const LGPCrossoverInstruction_OneSeg& rhs);
private:
	LGPCrossoverInstruction_OneSeg& operator=(const LGPCrossoverInstruction_OneSeg& rhs) { }

public:
	virtual void Crossover(LGPPop* lgpPop, LGPProgram* child1, LGPProgram* child2);
	virtual LGPCrossoverInstruction* Clone() const;
	virtual std::string ToString() const;

protected:
	void CrossoverOneSegment(LGPProgram* gp1, LGPProgram* gp2);

protected:
	double m_insertion_probability;
	unsigned int m_max_segment_length;
	unsigned int m_max_program_length;
	unsigned int m_min_program_length;
};
#endif

/* Xianshun says:
   This operator is derived from Algorithm 5.3 in Section 5.7.3 of Linear Genetic Programming
*/

/* Xianshun says: (From Section 5.7.3 of Linear Genetic Programming
   Crossover requires, by definition, that information is exchanged between individual programs.
   However, an exchange always includes two operations on an individual, the deletion and
   the insertion of a subprogram. The imperative program representation allows instructions to be 
   deleted without replacement since instructon operands, e.g. register pointers, are always defined.
   Instructions may also be inserted at any position without a preceding deletion, at least if the maximum 
   program length is not exceeded. 

   If we want linear crossover to be less disruptive it may be a good idea to execute only one operation per
   individual. this consideration motivates a one-segment or one-way recombination of linear genetic
   programs as described by Algorithm 5.3.

   Standard linear crossover may also be refered to as two-segment recombinations, in these terms.
*/