#ifndef _H_LGP_SELECTION_INSTRUCTION_FACTORY_H
#define _H_LGP_SELECTION_INSTRUCTION_FACTORY_H

#include "LGPSelectionInstruction.h"

class LGPSelectionInstructionFactory 
{
public:
	LGPSelectionInstructionFactory(const char* filename);
	virtual ~LGPSelectionInstructionFactory();

public:
	LGPProgram* Select(LGPPop* lgpPop);
	void Select(LGPPop* lgpPop, std::pair<LGPProgram*, LGPProgram*>& best_pair, std::pair<LGPProgram*, LGPProgram*>& worst_pair);

public:
	LGPSelectionInstructionFactory(const LGPSelectionInstructionFactory& rhs);
private:
	LGPSelectionInstructionFactory& operator=(const LGPSelectionInstructionFactory& rhs) { return *this; }

public:
	virtual std::string ToString() const;
	virtual LGPSelectionInstructionFactory* Clone() const { return new LGPSelectionInstructionFactory(*this); }

protected:
	LGPSelectionInstruction* m_current_selector;
};
#endif