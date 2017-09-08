#ifndef _H_LGP_OPERATOR_ATAN_H
#define _H_LGP_OPERATOR_ATAN_H

#include "../LGPComp/LGPOperator.h"

class LGPOperator_Atan : public LGPOperator
{
public:
	LGPOperator_Atan();
	virtual ~LGPOperator_Atan();

public:
	virtual LGPOperator* Clone() const;
	virtual int Execute(const LGPRegister* operand1, const LGPRegister* operand2, LGPRegister* destination_register);

protected:
	virtual std::string GetOperatorContent(std::string operand1, std::string operand2, std::string destination_register, std::string line_start="\t", std::string line_end="\n") const;
	virtual std::string GetOperatorRequiredHeaderFiles() const;
};
#endif