#ifndef _H_LGP_POP_H
#define _H_LGP_POP_H

#include "../LGPConfig/LGPConfig.h"
#include "../LGPEnvironment/LGPEnvironment.h"
#include "../LGPFactories/LGPMutationInstructionFactory.h"
#include "../LGPFactories/LGPCrossoverInstructionFactory.h"
#include "../LGPFactories/LGPPopInitInstructionFactory.h"
#include "../LGPFactories/LGPSelectionInstructionFactory.h"
#include "../LGPFactories/LGPSurvivalInstructionFactory.h"
#include "LGPProgram.h"
#include <algorithm>
#include <string>

/*
#define VLD_MAX_DATA_DUMP 0
#define VLD_AGGREGATE_DUPLICATES 1

#include <vld.h>
*/

class LGPPop
{
public:
	LGPPop(LGPConfig* lgpConfig=NULL);
	virtual ~LGPPop();

private:
	LGPPop(const LGPPop& rhs) { }
	LGPPop& operator=(const LGPPop& rhs) { return *this; }

protected:
	LGPConfig* m_lgpConfig;
public:
	LGPConfig* GetConfig() const { return m_lgpConfig; }
	void SetConfig(LGPConfig* lgpConfig) { m_lgpConfig=lgpConfig; }

protected:
	bool m_bSetup;
protected:
	void Setup();
public:
	bool IsSetup() const { return m_bSetup; }

public:
	unsigned int GetProgramCount() const { return static_cast<unsigned int>(m_programs.size()); }
	LGPProgram* GetProgram(unsigned int r) { return m_programs[r]; }
	void AddProgram(LGPProgram* lgp) { m_programs.push_back(lgp); }

public:
	virtual void Evolve();
	virtual void BreedInitialPopulation(bool load=true);
	virtual void SteadyStateEvolve(); // evolve of a new generation of programs using steady-state LGP model
	virtual void GenerationEvolve(size_t elites=0); // evolve of a new generation of programs using generational LGP model
	virtual bool Terminated() const;
protected:
	virtual void EvaluateFitness();
	virtual void Attempt2LoadSolutionsFromFiles();

public:
	void RandomShuffle() { std::random_shuffle(m_programs.begin(), m_programs.end()); }
	void SortFittestProgramFirst();
	void SortFittestProgramLast();
	void SortFittestProgramFirst(std::vector<LGPProgram*>& progs);
	void SortFittestProgramLast(std::vector<LGPProgram*>& progs);
	LGPProgram* GetFittestProgram();
	const LGPProgram* GetGlobalFittestProgram() const;

public:
	virtual std::string ToString(bool effective_only=false) const;
	LGPEnvironment* GetEnvironment() { return m_env; }

protected:
	virtual LGPEnvironment* CreateEnvironment(LGPConfig* lgpConfig)=0;
	virtual LGPMutationInstructionFactory* CreateMutationInstructionFactory(const char* filename);
	virtual LGPCrossoverInstructionFactory* CreateCrossoverInstructionFactory(const char* filename);
	virtual LGPPopInitInstructionFactory* CreatePopInitInstructionFactory(const char* filename);
	virtual LGPSelectionInstructionFactory* CreateReproductionSelectionInstructionFactory(const char* filename);
	virtual LGPSurvivalInstructionFactory* CreateSurvivalInstructionFactory(const char* filename);
public:
	virtual LGPProgram* CreateProgram(unsigned int size, LGPEnvironment* env)=0;

public:
	void Replace(LGPProgram* program_to_be_replaced, LGPProgram* program_to_replace);

protected:
	LGPEnvironment* m_env;
	LGPMutationInstructionFactory* m_lgpMutationInstructionFactory;
	LGPCrossoverInstructionFactory* m_lgpCrossoverInstructionFactory;
	LGPPopInitInstructionFactory* m_lgpPopInitInstructionFactory;
	LGPSelectionInstructionFactory* m_lgpReproductionSelectionInstructionFactory;
	LGPSurvivalInstructionFactory* m_lgpSurvivalInstructionFactory;
	unsigned int m_iCurrentGeneration;

public:
	unsigned int GetCurrentGeneration() const { return m_iCurrentGeneration; }

protected:
	std::vector<LGPProgram*> m_programs;
	LGPProgram* m_global_fittest_program;
};
#endif

/* Xianshun says:
 Algorithm 2.1 (LGP algorithm)
 1. Initialize the population with random programs and calculate their fitness value
 2. Randomly select 2 * nt individuals from the pouplation without replacement
 3. Perform two fitness tournament of size nt
 4. Make temporary copies of the two tournament winners
 5. Modify the two winners by one or more variation operators with certain probabilities
 6. Evaluate the fitness of the two offspring
 7. If the current best-fit indivdiual is replaced by one of the spring validate the new best program using unknown data (only required for machine learning) * 
 8. Reproduce the two tournament winnners within the population with a certain probability (This is the "Reproduction" Mechansim) by replacing the two tournament losers with the temporary copies of the winners under a certain condition (This is "Population Replacement" for steady-state LGP)
 9. Repeat Step 2 to 8 until maximum number of generations is reached.

 Note that the population size stay fixed
*/

/* Xianshun says:
 In step 5 of Algorithm 2.1, three different variation mechanism can be used to modify the two temporary copies of the tournament winners:
  1. crossover 
  2. macro mutation
  3. micro mutation
These three variation mechanism can be applied in combination or one at a time to modify the two temporary copies of the tournament winners.
*/

/* Xianshun says:
 The current model is based on steady-state LGP
 Regarding what is meant by a "generation" in steady-state LGP, I quote a paragraph from "Genetic Programming" by Wolfgang Banzhaf, Peter Nordin, Robert E. Keller, Frank D. Francone
 The steady-state GP models do not have distinct generations. Steady-state GP maintains the illusion of generations 
 by stopping once very P fitness evaluations (where P is the populaton size) and measuring their online statistics. 
 This convention has proved effective and is used almost universally in steady-state GP systems. Here we will follow this convention. 
 
 The reader should recall, however, that a generaytion is no more than an agreed convention in steady-state models and any 
 online statistic could be calculated so as to reflect the reality of a steady-state system more precisely.

 Also stated in "Linear Genetic Programming": In a steady-state LGP, ... a generation (equivalent) is complete if the number of new individuals
 equals the population size.
 */