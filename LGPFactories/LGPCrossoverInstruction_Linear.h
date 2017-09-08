#ifndef _H_LGP_CROSSOVER_INSTRUCTION_LINEAR_H
#define _H_LGP_CROSSOVER_INSTRUCTION_LINEAR_H

#include "LGPCrossoverInstruction.h"

// Xianshun says:
// this is derived from Algorithm 5.1 of Section 5.7.1 of Linear Genetic Programming
// this linear crossover can also be considered as two-point crossover

class LGPCrossoverInstruction_Linear : public LGPCrossoverInstruction
{
public:
	LGPCrossoverInstruction_Linear();
	LGPCrossoverInstruction_Linear(TiXmlElement* xml_level1);
	virtual ~LGPCrossoverInstruction_Linear();

public:
	LGPCrossoverInstruction_Linear(const LGPCrossoverInstruction_Linear& rhs);
private:
	LGPCrossoverInstruction_Linear& operator=(const LGPCrossoverInstruction_Linear& rhs) { return *this; }

public:
	virtual void Crossover(LGPPop* lgpPop, LGPProgram* child1, LGPProgram* child2);
	virtual std::string ToString() const;
	virtual LGPCrossoverInstruction* Clone() const;

protected:
	unsigned int m_max_program_length;
	unsigned int m_min_program_length;
	unsigned int m_max_segment_length;
	unsigned int m_max_distance_of_crossover_points;
	unsigned int m_max_difference_of_segment_length;
};
#endif