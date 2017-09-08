#ifndef _H_LGP_OPERATOR_SIN_H
#define _H_LGP_OPERATOR_SIN_H

#include "../LGPComp/LGPOperator.h"

class LGPOperator_Sin : public LGPOperator
{
public:
	LGPOperator_Sin();
	virtual ~LGPOperator_Sin();

public:
	virtual LGPOperator* Clone() const;
	virtual int Execute(const LGPRegister* operand1, const LGPRegister* operand2, LGPRegister* destination_register);

public:
	virtual std::string GetOperatorContent(std::string operand1, std::string operand2, std::string destination_register, std::string line_start="\t", std::string line_end="\n") const;
	virtual std::string GetOperatorRequiredHeaderFiles() const;
};
#endif