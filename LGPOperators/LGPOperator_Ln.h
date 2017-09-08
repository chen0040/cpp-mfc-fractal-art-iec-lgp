#ifndef _H_LGP_OPERATOR_LN_H
#define _H_LGP_OPERATOR_LN_H

#include "../LGPComp/LGPOperator.h"

class LGPOperator_Ln : public LGPOperator
{
public:
	LGPOperator_Ln();
	virtual ~LGPOperator_Ln();

public:
	LGPOperator* Clone() const { return new LGPOperator_Ln(*this); }
	virtual int Execute(const LGPRegister* operand1, const LGPRegister* operand2, LGPRegister* destination_register);

public:
	virtual std::string GetOperatorContent(std::string operand1, std::string operand2, std::string destination_register, std::string line_start="\t", std::string line_end="\n") const;
	virtual std::string GetOperatorRequiredHeaderFiles() const;
};

#endif