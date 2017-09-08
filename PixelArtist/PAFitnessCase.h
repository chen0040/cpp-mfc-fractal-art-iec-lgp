#ifndef _H_PA_FITNESS_CASE_H
#define _H_PA_FITNESS_CASE_H

#include "../LGPEnvironment/LGPFitnessCase.h"

class PAFitnessCase : public LGPFitnessCase
{
public:
	PAFitnessCase();
	virtual ~PAFitnessCase();

public:
	virtual void SetInput(double x, unsigned int index=0) { m_x[index] = x; }
	virtual void QueryInput(unsigned int index, double* input) const { *input=m_x[index]; }
	virtual void QueryLGPOutput(unsigned int index, double * output) const { *output=m_output[index]; }

public:
	unsigned int GetInputCount() const { return 2; }
	unsigned int GetAuxDataCount() const { return 0; }
	unsigned int GetLGPOutputCount() const { return 3; }

public:
	virtual std::string ToString() const;
	virtual void Update(const LGPOperator* op, const LGPRegister* operand1, const LGPRegister* operand2, const LGPRegister* destination_register, const LGPRegisterSet* lgpRegSet);
	virtual void Update(const LGPRegisterSet* lgpRegSet);

protected:
	double Normalize(double value);

protected:
	double m_x[2];
	double m_output[3];
};

#endif
