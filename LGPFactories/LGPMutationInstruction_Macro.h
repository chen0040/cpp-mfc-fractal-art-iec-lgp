#ifndef _H_LGP_MUTATION_INSTRUCTION_MACRO_H
#define _H_LGP_MUTATION_INSTRUCTION_MACRO_H

#include "LGPMutationInstruction.h"

class LGPMutationInstruction_Macro : public LGPMutationInstruction
{
public:
	LGPMutationInstruction_Macro();
	LGPMutationInstruction_Macro(TiXmlElement* xml_level1);
	virtual ~LGPMutationInstruction_Macro();

public:
	LGPMutationInstruction_Macro(const LGPMutationInstruction_Macro& rhs);
private:
	LGPMutationInstruction_Macro& operator=(const LGPMutationInstruction_Macro& rhs) { return *this; }

public:
	virtual void Mutate(LGPPop* lgpPop, LGPProgram* child);
	virtual std::string ToString() const;
	virtual LGPMutationInstruction* Clone() const;

protected:
	double m_macro_mutate_insertion_rate;
	double m_macro_mutate_deletion_rate;
	unsigned int m_macro_mutate_min_program_length;
	unsigned int m_macro_mutate_max_program_length;
	bool m_effective_mutation;
public:
	double GetMacroMutateInsertionRate() const { return m_macro_mutate_insertion_rate; }
	double GetMacroMutateDeletionRate() const { return m_macro_mutate_deletion_rate; }
	unsigned int GetMacroMutateMinProgLength() const { return m_macro_mutate_min_program_length; }
	unsigned int GetMacroMutateMaxProgLength() const { return m_macro_mutate_max_program_length; }
	bool IsEffectiveMutation() const { return m_effective_mutation; }
};
#endif