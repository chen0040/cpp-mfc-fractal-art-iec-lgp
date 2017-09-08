#ifndef _H_LGP_OPERATOR_JULIA_H
#define _H_LGP_OPERATOR_JULIA_H

#include "../LGPComp/LGPOperator.h"

class ImgOperator_Julia : public LGPOperator
{
public:
	ImgOperator_Julia(unsigned int degree=2);
	virtual ~ImgOperator_Julia();

public:
	virtual LGPOperator* Clone() const;
	virtual int Execute(const LGPRegister* operand1, const LGPRegister* operand2, LGPRegister* destination_register);

protected:
	unsigned int m_degree;

public:
	virtual std::string GetOperatorContent(std::string operand1, std::string operand2, std::string destination_register, std::string line_start="\t", std::string line_end="\n") const;
	virtual std::string GetOperatorRequiredHeaderFiles() const;
};
#endif