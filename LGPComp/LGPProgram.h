#ifndef _H_LGP_PROGRAM_H
#define _H_LGP_PROGRAM_H

#include "LGPInstruction.h"
#include <vector>
#include <string>
#include "LGPOperatorSet.h"
#include "LGPRegisterSet.h"
#include "LGPConstantSet.h"
#include "../LGPEnvironment/LGPEnvironment.h"
#include "../LGPConfig/LGPConfig.h"
#include "../LGPFactories/LGPRegInitInstructionFactory.h"
#include <set>
#include <map>

typedef std::map<std::string, std::string> ParamPairList;

class LGPProgram
{
public:
	LGPProgram(LGPConfig* lgpConfig);
	virtual ~LGPProgram();

public:
	LGPProgram(const LGPProgram& rhs);
private:
	LGPProgram& operator=(const LGPProgram& rhs) { return *this; }

public:
	const std::vector<LGPInstruction*>& GetConstRawInstructions() const { return m_instructions; }
	std::vector<LGPInstruction*>& GetMutableRawInstruction() { return m_instructions; }
	unsigned int GetInstructionCount() const { return static_cast<unsigned int>(m_instructions.size()); }
	unsigned int GetEffectiveInstructionCount() const; // Xianshun says: this means the number of structurally effective instructions in the linear program

public:
	void MicroMutate();
	virtual void Create(unsigned int size);
	virtual void CreateFromScript(std::string script_name);

public:
	virtual LGPProgram* Clone() const=0;
	const LGPConfig* GetConfig() const;

public:
	virtual void EvaluateFitness(LGPEnvironment* env);
	virtual void Destroy();
protected:
	void EraseInstructions();
	virtual double EvaluateFitness(std::vector<LGPFitnessCase*>& fitness_cases)=0;
	
protected:
	virtual void InitializeProgramRegisters(const LGPFitnessCase* fitness_case);
	void EvaluateFitnessCase(LGPFitnessCase* lgpFitnessCase);

public:
	void MarkStructuralIntrons(unsigned int stop_point, std::set<unsigned int>& Reff);
protected:
	void MarkStructuralIntrons();

protected:
	void MutateInstructionOperator();
	void MutateInstructionConstant();
	void MutateInstructionRegister();

protected:
	bool m_bSetup;
	double m_dFitness;
	double m_objective_value;
	bool m_bFitnessValid;
public:
	bool IsBetterThan(const LGPProgram* lgp) const;
	void TrashFitness() { m_bFitnessValid=false; }
	bool HasValidFitness() const { return m_bFitnessValid; }
	double GetFitness() const;
	double GetObjectiveValue() const;

protected:
	LGPConfig* m_lgpConfig;
	std::vector<LGPInstruction*> m_instructions;
	ParamPairList m_parameter_list;
	LGPRegInitInstructionFactory* m_lgpRegInitInstructionFactory;

public:
	virtual std::string ToString(bool effective_only=false, bool print_fitness=false) const;
	virtual void BuildScript(std::string script_name, unsigned int input_count, unsigned int output_count, const ParamPairList& params, bool effective_only=false, bool print_fitness=false) const;
	virtual void BuildCodes(std::string script_name, std::string function_name="lgp_program", std::string output_location="lgp_codes");
	virtual std::string GetFactoryInfo() const;

public:
	LGPRegisterSet* m_register_set;
	LGPOperatorSet* m_operator_set;
	LGPConstantSet* m_constant_set;

protected:
	void Setup(); // this method must be called to set up the program properly

protected:
	virtual LGPRegisterSet* CreateRegisterSet();
	virtual LGPOperatorSet* CreateOperatorSet()=0;
	virtual LGPConstantSet* CreateConstantSet();
	virtual LGPRegInitInstructionFactory* CreateRegInitInstructionFactory(const char* filename);

public:
	LGPRegisterSet* GetRegisterSet() { return m_register_set; }
	LGPConstantSet* GetConstantSet() { return m_constant_set; }
	LGPOperatorSet* GetOperatorSet() { return m_operator_set; }
};

class LGPProgramSort_FittestFirst
{
public:
	bool operator() (LGPProgram* const & left, LGPProgram* const & right)
	{
		return left->IsBetterThan(right);
	}
};

class LGPProgramSort_FittestLast
{
public:
	bool operator() (LGPProgram* const & left, LGPProgram* const & right)
	{
		return right->IsBetterThan(left);
	}
};
#endif