#ifndef _H_LGP_OPERATOR_SET_H
#define _H_LGP_OPERATOR_SET_H

#include "LGPOperator.h"
#include <utility>
#include <vector>

class LGPOperatorSet
{
public:
	LGPOperatorSet();
	virtual ~LGPOperatorSet();

public:
	LGPOperatorSet(const LGPOperatorSet& rhs);
private:
	LGPOperatorSet& operator=(const LGPOperatorSet& rhs) { return *this; }

public:
	virtual LGPOperator* GetRandomOperator(LGPOperator* current_register=NULL);
	unsigned int GetOperatorCount() const { return static_cast<unsigned int>(m_registers.size()); }

public:
	void AddOperator(LGPOperator* lpgOperator, double weight=1);
	void AddIfltOperator(double weight=1); //Add if less than operator
	void AddIfgtOperator(double weight=1); //Add if greater than operator

public:
	virtual LGPOperator* GetOperator(unsigned int iRegisterIndex) const;
	virtual LGPOperatorSet* Clone() const=0;
	virtual std::string ToString() const;

public:
	virtual void WriteHeaderFiles(std::string directory_name, std::string operators_header_file);
	virtual void WriteSourceFiles(std::string directory_name, std::string operators_source_file, std::string operators_header_file);

protected:
	std::vector<std::pair<LGPOperator*, double> > m_registers;
	double m_dWeightSum;
};
#endif