#ifndef _H_LGP_OPERATOR_If_LESS_THAN_H
#define _H_LGP_OPERATOR_If_LESS_THAN_H

#include "../LGPComp/LGPOperator.h"

class LGPOperator_Iflt : public LGPOperator
{
public:
	LGPOperator_Iflt();
	virtual ~LGPOperator_Iflt();

public:
	virtual int Execute(const LGPRegister* operand1, const LGPRegister* operand2, LGPRegister* destination_register);
	LGPOperator* Clone() const;

public:
	virtual void WriteHeaderFile(std::string filename) const;
	virtual void WriteSourceFile(std::string filename, std::string header_file) const;
};
#endif

/* Xianshun says:
  this operator implements the "If less than" instruction
  Iflt(operand1 < operand2)
  {
	execute next line
  }
  else
  {
	skip next line
  }
*/
