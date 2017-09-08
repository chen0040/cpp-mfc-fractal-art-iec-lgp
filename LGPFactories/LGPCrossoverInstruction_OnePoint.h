#ifndef _H_LGP_CROSSOVER_INSTRUCTION_ONE_POINT_H
#define _H_LGP_CROSSOVER_INSTRUCTION_ONE_POINT_H

#include "LGPCrossoverInstruction.h"

class LGPCrossoverInstruction_OnePoint : public LGPCrossoverInstruction
{
public:
	LGPCrossoverInstruction_OnePoint();
	LGPCrossoverInstruction_OnePoint(TiXmlElement* xml_level1);
	virtual ~LGPCrossoverInstruction_OnePoint();

public:
	LGPCrossoverInstruction_OnePoint(const LGPCrossoverInstruction_OnePoint& rhs);
private:
	LGPCrossoverInstruction_OnePoint& operator=(const LGPCrossoverInstruction_OnePoint& rhs) { }

public:
	virtual void Crossover(LGPPop* lgpPop, LGPProgram* child1, LGPProgram* child2);
	virtual LGPCrossoverInstruction* Clone() const;
	virtual std::string ToString() const;

protected:
	unsigned int m_max_distance_of_crossover_points;
	unsigned int m_max_program_length;
	unsigned int m_min_program_length;
};
#endif

/* Xianshun says:
   This operator is derived from Algorithm 5.2 in Section 5.7.2 of Linear Genetic Programming
*/