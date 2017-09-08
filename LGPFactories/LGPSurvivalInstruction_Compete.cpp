#include "stdafx.h"
#include "LGPSurvivalInstruction_Compete.h"
#include "../LGPComp/LGPPop.h"
#include "../LGPComp/LGPProgram.h"
#include <sstream>

LGPSurvivalInstruction_Compete::LGPSurvivalInstruction_Compete()
: LGPSurvivalInstruction()
{

}

LGPSurvivalInstruction_Compete::LGPSurvivalInstruction_Compete(TiXmlElement* xml_level1)
{
	
}

LGPSurvivalInstruction_Compete::~LGPSurvivalInstruction_Compete()
{

}

LGPSurvivalInstruction_Compete::LGPSurvivalInstruction_Compete(const LGPSurvivalInstruction_Compete& rhs)
{
	
}

LGPProgram* LGPSurvivalInstruction_Compete::Compete(LGPPop* lgpPop, LGPProgram* weak_program_in_current_pop, LGPProgram* child_program)
{
	if(child_program->IsBetterThan(weak_program_in_current_pop))
	{
		lgpPop->Replace(weak_program_in_current_pop, child_program);
		return weak_program_in_current_pop;
	}
	return child_program;
	
}

LGPSurvivalInstruction* LGPSurvivalInstruction_Compete::Clone() const
{
	return new LGPSurvivalInstruction_Compete(*this);
}

std::string LGPSurvivalInstruction_Compete::ToString() const
{
	std::ostringstream oss;

	oss << ">> Name: LGPSurvivalInstruction_Compete";

	return oss.str();
}