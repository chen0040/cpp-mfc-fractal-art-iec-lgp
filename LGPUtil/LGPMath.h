#ifndef _H_LGP_MATH_H
#define _H_LGP_MATH_H

class LGPMath
{
public:
	static LGPMath* Instance();
	virtual ~LGPMath() { }

public:
	double PI() const { return 3.141592654; }

private:
	LGPMath() { }
	LGPMath(const LGPMath& rhs) { }
	LGPMath& operator=(const LGPMath& rhs) { return *this; }
};
#endif