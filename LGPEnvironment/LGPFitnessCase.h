#ifndef _H_LGP_FITNESS_CASE_H
#define _H_LGP_FITNESS_CASE_H

#include "../LGPComp/LGPOperator.h"
#include "../LGPComp/LGPRegisterSet.h"
#include "../LGPUtil/LGPExitSystem.h"
#include <string>

class LGPFitnessCase
{
public:
	LGPFitnessCase();
	virtual ~LGPFitnessCase();

private:
	LGPFitnessCase(const LGPFitnessCase& rhs) { }
	LGPFitnessCase& operator=(const LGPFitnessCase& rhs) { return *this; }

public:
	virtual void SetBooleanInput(bool input, unsigned int index) { LGPExitSystem("LGPFitnessCase::SetBooleanInput(bool input, unsigned int index)", "this method is called without being overriden"); }
	virtual void SetInput(double input, unsigned int index) { LGPExitSystem("LGPFitnessCase::SetInput(double input, unsigned int index)", "this method is called without being overriden"); }
	virtual void SetIntegerInput(int input, unsigned int index) { LGPExitSystem("LGPFitnessCase::SetIntegerInput(int input, unsigned int index)", "this method is called without being overriden"); }
	virtual unsigned int GetInputCount() const=0;
	virtual void QueryIntegerInput(unsigned int index, int* input) const { LGPExitSystem("LGPFitnessCase::QueryIntegerInput(unsigned int index, int* input)", "this method is called without being overriden"); }
	virtual void QueryInput(unsigned int index, double* input) const { LGPExitSystem("LGPFitnessCase::QueryInput(unsigned int index, double* input)", "this method is called without being overriden"); }
	virtual void QueryBooleanInput(unsigned int index, bool* input) const { LGPExitSystem("LGPFitnessCase::QueryBooleanInput(unsigned int index, bool* input)", "this method is called without being overriden"); }

public:
	virtual void SetAuxData(bool output, unsigned int index=0) { LGPExitSystem("LGPFitnessCase::SetAuxData(bool output, unsigned int index)", "this method is called without being override"); }
	virtual void SetAuxData(double output, unsigned int index=0) { LGPExitSystem("LGPFitnessCase::SetAuxData(double output, unsigned int index)", "this method is called without being overriden"); }
	virtual void SetAuxData(int output, unsigned int index=0) { LGPExitSystem("LGPFitnessCase::SetAuxData(int output, unsigned int index)", "this method is called without being overriden"); }
	virtual unsigned int GetAuxDataCount() const=0;
	virtual void QueryAuxData(unsigned int index, int* output) const { LGPExitSystem("LGPFitnessCase::QueryAuxData(unsigned int index, int* output)", "this method is called without being overriden"); }
	virtual void QueryAuxData(unsigned int index, double* output) const { LGPExitSystem("LGPFitnessCase::QueryAuxData(unsigned int index, double* output)", "this method is called without being overriden"); }
	virtual void QueryAuxData(unsigned int index, bool* output) const { LGPExitSystem("LGPFitnessCase::QueryAuxData(unsigned int index, bool * output)", "this method is called without being overriden"); }

public:
	virtual void SetBooleanLGPOutput(bool output, unsigned int index=0) { LGPExitSystem("LGPFitnessCase::SetBooleanLGPOutput(bool output, unsigned int index)", "this method is called without being overriden"); }
	virtual void SetLGPOutput(double output, unsigned int index=0) { LGPExitSystem("LGPFitnessCase::SetLGPOutput(double output, unsigned int index)", "this method is called withtout being overriden"); }
	virtual void SetIntegerLGPOutput(int output, unsigned int index=0) { LGPExitSystem("LGPFitnessCase::SetIntegerLGPOutput(int output, unsigned int index)", "this method is called without being overriden"); }
	virtual unsigned int GetLGPOutputCount() const=0;
	virtual void QueryIntegerLGPOutput(unsigned int index, int* output) const { LGPExitSystem("LGPFitnessCase::QueryIntegerLGPOutput(unsigned int index, int* output)", "this method is called without being overriden");}
	virtual void QueryBooleanLGPOutput(unsigned int index, bool* output) const { LGPExitSystem("LGPFitnessCase::QueryBooleanLGPOutput(unsigned int index, bool* output)", "this method is called without being overriden");}
	virtual void QueryLGPOutput(unsigned int index, double* output) const { LGPExitSystem("LGPFitnessCase::QueryLGPOutput(unsigned int index, double* output)", "this method is called without being overriden");}

public:
	virtual void Update(const LGPOperator* op, const LGPRegister* operand1, const LGPRegister* operand2, const LGPRegister* destination_register, const LGPRegisterSet* lgpRegSet)=0;
	virtual void Update(const LGPRegisterSet* lgpRegSet)=0;

public:
	virtual std::string ToString() const=0;
};
#endif