#ifndef _H_LGP_REGISTER_H
#define _H_LGP_REGISTER_H

#include <string>

class LGPRegisterSet;
class LGPConstantSet;

class LGPRegister
{
public:
	LGPRegister();
	virtual ~LGPRegister();

public:
	bool IsConstant() const { return m_bIsConstant; }

public:
	LGPRegister(const LGPRegister& rhs);
private:
	LGPRegister& operator=(const LGPRegister& rhs) { return *this; }

public:
	virtual LGPRegister* Clone() const { return new LGPRegister(*this); }
	virtual void Mutate(double standard_deviation);

public:
	virtual double ToDouble() const { return m_value; }
	virtual int ToInteger() const { return static_cast<int>(m_value); }
	virtual bool ToBoolean() const { return m_value > 0; }
	virtual void SetValue(double value);
protected:
	double m_value; 

public:
	virtual std::string ToString(bool bShowIndex=false) const;

protected:
	unsigned int m_iRegisterIndex;
public:
	unsigned int GetRegisterIndex() const { return m_iRegisterIndex; }

protected:
	bool m_bIsConstant;
	friend class LGPRegisterSet;
	friend class LGPConstantSet;
};
#endif