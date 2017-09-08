#ifndef _H_LGP_SELECTION_INSTRUCTION_H
#define _H_LGP_SELECTION_INSTRUCTION_H

#include "../tinyxml/tinyxml.h"
#include <string>
#include <vector>
#include <utility>

class LGPPop;
class LGPProgram;

class LGPSelectionInstruction
{
public:
	LGPSelectionInstruction();
	LGPSelectionInstruction(TiXmlElement* xml_level1);
	virtual ~LGPSelectionInstruction();

public:
	virtual LGPProgram* Select(LGPPop* lgpPop)=0;
	virtual void Select(LGPPop* lgpPop, std::pair<LGPProgram*, LGPProgram*>& best_pair, std::pair<LGPProgram*, LGPProgram*>& worst_pair)=0;
	virtual std::string ToString() const=0;
	virtual LGPSelectionInstruction* Clone() const=0;
};
#endif