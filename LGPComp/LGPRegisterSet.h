#ifndef _H_LGP_REGISTER_SET_H
#define _H_LGP_REGISTER_SET_H

#include "LGPRegister.h"
#include <utility>
#include <vector>

class LGPRegisterSet
{
public:
	LGPRegisterSet();
	virtual ~LGPRegisterSet();

public:
	LGPRegisterSet(const LGPRegisterSet& rhs);
private:
	LGPRegisterSet& operator=(const LGPRegisterSet& rhs) { return *this; }

public:
	virtual LGPRegister* GetRandomRegister(LGPRegister* current_register=NULL);
	
public:
	void AddRegister(LGPRegister* lpgRegister, double weight=1);

public:
	virtual LGPRegisterSet* Clone() const { return new LGPRegisterSet(*this); }

public:
	virtual LGPRegister* GetRegister(unsigned int iRegisterIndex) const;
	unsigned int GetRegisterCount() const { return static_cast<unsigned int>(m_registers.size()); }
	virtual std::string ToString() const;

protected:
	std::vector<std::pair<LGPRegister*, double> > m_registers;
	double m_dWeightSum;
};
#endif