#ifndef _H_LGP_CONSTANT_SET_H
#define _H_LGP_CONSTANT_SET_H

#include "LGPRegister.h"
#include <utility>
#include <vector>

class LGPConstantSet
{
public:
	LGPConstantSet();
	virtual ~LGPConstantSet();

public:
	LGPConstantSet(const LGPConstantSet& rhs);
private:
	LGPConstantSet& operator=(const LGPConstantSet& rhs) { return *this; }

public:
	virtual LGPRegister* GetRandomRegister(LGPRegister* current_register=NULL);
	unsigned int GetRegisterCount() const { return static_cast<unsigned int>(m_registers.size()); }
	
public:
	void AddRegister(LGPRegister* lpgRegister, double weight=1);
	void AddConstant(double value, double weight=1);

public:
	virtual LGPConstantSet* Clone() const { return new LGPConstantSet(*this); }

public:
	virtual LGPRegister* GetRegister(unsigned int iRegisterIndex) const;
	virtual std::string ToString() const;

protected:
	std::vector<std::pair<LGPRegister*, double> > m_registers;
	double m_dWeightSum;
};

#endif