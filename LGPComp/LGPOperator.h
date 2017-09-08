#ifndef _H_LGP_OPERATOR_H
#define _H_LGP_OPERATOR_H

#include "LGPRegister.h"
#include "../LGPConstants/LGPFlags.h"
#include <string>

class LGPOperatorSet;

class LGPOperator
{
public:
	LGPOperator(const char* symbol);
	virtual ~LGPOperator();

public:
	LGPOperator(const LGPOperator& rhs);
private:
	LGPOperator& operator=(const LGPOperator& rhs) { return *this; }

protected:
	bool m_bIsConditionalConstruct;
public:
	bool IsConditionalConstruct() { return m_bIsConditionalConstruct; }

protected:
	unsigned int m_iOperatorIndex;
public:
	unsigned int GetOperatorIndex() const { return m_iOperatorIndex; }

public:
	virtual LGPOperator* Clone() const=0;
	virtual std::string ToString() const;
	virtual std::string GetMethodName() const;

public:
	virtual int Execute(const LGPRegister* operand1, const LGPRegister* operand2, LGPRegister* destination_register)=0;
	virtual void WriteHeaderFile(std::string filename) const;
	virtual void WriteSourceFile(std::string filename, std::string header_file) const;

protected:
	virtual std::string GetOperatorContent(std::string operand1, std::string operand2, std::string destination_register, std::string line_start="\t", std::string line_end="\n") const { return ""; }
	virtual std::string GetOperatorRequiredHeaderFiles() const { return ""; }

protected:
	friend class LGPOperatorSet;
	std::string m_symbol;
	std::string m_method_name;
};
#endif