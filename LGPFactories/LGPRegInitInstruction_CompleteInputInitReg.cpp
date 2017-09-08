#include "stdafx.h"
#include "LGPRegInitInstruction_CompleteInputInitReg.h"
#include <sstream>
#include <iostream>

LGPRegInitInstruction_CompleteInputInitReg::LGPRegInitInstruction_CompleteInputInitReg()
: LGPRegInitInstruction()
{
	
}

LGPRegInitInstruction_CompleteInputInitReg::LGPRegInitInstruction_CompleteInputInitReg(TiXmlElement* xml_level1)
: LGPRegInitInstruction(xml_level1)
{

}

LGPRegInitInstruction_CompleteInputInitReg::~LGPRegInitInstruction_CompleteInputInitReg()
{

}


LGPRegInitInstruction_CompleteInputInitReg::LGPRegInitInstruction_CompleteInputInitReg(const LGPRegInitInstruction_CompleteInputInitReg& rhs)
{

}

LGPRegInitInstruction* LGPRegInitInstruction_CompleteInputInitReg::Clone() const
{
	return new LGPRegInitInstruction_CompleteInputInitReg(*this);
}

int LGPRegInitInstruction_CompleteInputInitReg::GetInputInitializedRegisterCount() const
{
	return -1; 
}

void LGPRegInitInstruction_CompleteInputInitReg::InitializeRegisters(LGPRegisterSet *reg_set, LGPConstantSet* constant_set, const LGPFitnessCase *fitness_case)
{
	unsigned int iRegisterCount=reg_set->GetRegisterCount();
	unsigned int iInputCount=fitness_case->GetInputCount();

#ifdef LGP_DEBUG
	if(iInputCount > iRegisterCount)
	{
		LGPExitSystem("LGPRegInitInstruction_CompleteInputInitReg::InitializeRegisters(LGPProgram *lgp, const LGPFitnessCase *fitness_case)", "iInputCount > iRegisterCount");
	}
#endif

	unsigned int iRegisterIndex=0;
	while(iRegisterIndex < iRegisterCount)
	{
		for(unsigned int j=0; j<iInputCount; ++j, ++iRegisterIndex)
		{
			if(iRegisterIndex >= iRegisterCount)
			{
				break;
			}

			double value;
			fitness_case->QueryInput(j, &value);
			reg_set->GetRegister(iRegisterIndex)->SetValue(value);
		}
	}

}

std::string LGPRegInitInstruction_CompleteInputInitReg::ToString() const
{
	std::ostringstream oss;

	oss << ">> Name: LGPRegInitInstruction_CompleteInputInitReg" << std::endl;
	return oss.str();
}