#ifndef _H_LGP_OPERATOR_PLUS_H
#define _H_LGP_OPERATOR_PLUS_H

#include "../LGPComp/LGPOperator.h"

class LGPOperator_Plus : public LGPOperator
{
public:
	LGPOperator_Plus();
	virtual ~LGPOperator_Plus();

public:
	virtual LGPOperator* Clone() const { return new LGPOperator_Plus(*this); }
	virtual int Execute(const LGPRegister* operand1, const LGPRegister* operand2, LGPRegister* destination_register);

public:
	virtual std::string GetOperatorContent(std::string operand1, std::string operand2, std::string destination_register, std::string line_start="\t", std::string line_end="\n") const;
	virtual std::string GetOperatorRequiredHeaderFiles() const;
};
#endif