#include "stdafx.h"
#include "LGPMutationInstruction.h"
#include "../LGPComp/LGPPop.h"
#include "../LGPComp/LGPProgram.h"

LGPMutationInstruction::LGPMutationInstruction()
{

}

LGPMutationInstruction::LGPMutationInstruction(TiXmlElement* xml_level1)
{
	
}

LGPMutationInstruction::~LGPMutationInstruction()
{

}

void LGPMutationInstruction::Mutate(LGPPop* lgpPop, LGPProgram* child1, LGPProgram* child2)
{
	Mutate(lgpPop, child1);
	Mutate(lgpPop, child2);
}