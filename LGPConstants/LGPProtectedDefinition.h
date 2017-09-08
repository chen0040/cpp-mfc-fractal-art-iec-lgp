#ifndef _H_LGP_PROTECTED_DEFINITION_H
#define _H_LGP_PROTECTED_DEFINITION_H

class LGPProtectedDefinition
{
public:
	static LGPProtectedDefinition* Instance();
	~LGPProtectedDefinition();

protected:
	LGPProtectedDefinition();
	LGPProtectedDefinition(const LGPProtectedDefinition& rhs) { }
	LGPProtectedDefinition& operator=(const LGPProtectedDefinition& rhs) { return *this; }

public:
	double LGP_UNDEFINED() const { return m_C_UNDEFINED; }
	double LGP_REG_POSITIVE_INF() const { return m_REG_POSITIVE_INFINITE; }
	double LGP_REG_NEGATIVE_INF() const { return m_REG_NEGATIVE_INFINITE; }

protected:
	double m_C_UNDEFINED;
	double m_REG_POSITIVE_INFINITE;
	double m_REG_NEGATIVE_INFINITE;
};

#define LGP_UNDEFINED (LGPProtectedDefinition::Instance()->LGP_UNDEFINED())
#define LGP_REG_POSITIVE_INF (LGPProtectedDefinition::Instance()->LGP_REG_POSITIVE_INF())
#define LGP_REG_NEGATIVE_INF (LGPProtectedDefinition::Instance()->LGP_REG_NEGATIVE_INF())

#endif