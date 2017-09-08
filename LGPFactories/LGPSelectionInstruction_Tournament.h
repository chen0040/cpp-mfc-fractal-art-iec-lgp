#ifndef _H_LGP_SELECTION_INSTRUCTION_TOURNAMENT_H
#define _H_LGP_SELECTION_INSTRUCTION_TOURNAMENT_H

#include "LGPSelectionInstruction.h"

class LGPSelectionInstruction_Tournament : public LGPSelectionInstruction
{
public:
	LGPSelectionInstruction_Tournament();
	LGPSelectionInstruction_Tournament(TiXmlElement* xml_level1);
	virtual ~LGPSelectionInstruction_Tournament();

public:
	LGPSelectionInstruction_Tournament(const LGPSelectionInstruction_Tournament& rhs);
private:
	LGPSelectionInstruction_Tournament& operator=(const LGPSelectionInstruction_Tournament& rhs) { return *this; }

public:
	virtual LGPProgram* Select(LGPPop* lgpPop);
	virtual void Select(LGPPop* lgpPop, std::pair<LGPProgram*, LGPProgram*>& best_pair, std::pair<LGPProgram*, LGPProgram*>& worst_pair);
	virtual std::string ToString() const;
	virtual LGPSelectionInstruction* Clone() const { return new LGPSelectionInstruction_Tournament(*this); }

protected:
	unsigned int m_tournament_size;
};
#endif