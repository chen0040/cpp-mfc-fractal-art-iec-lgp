#ifndef _H_LGP_RANDOM_H
#define _H_LGP_RANDOM_H

class LGPRandom
{
public:
	static LGPRandom* Instance();
	virtual ~LGPRandom();

private:
	LGPRandom();
	LGPRandom(const LGPRandom& rhs) { }
	LGPRandom& operator=(const LGPRandom& rhs) { return *this; }

public:
	unsigned int nextInt(unsigned int upper_bound) const; // return value between 0 and upper_bound-1
	double nextDouble() const; 
	double normal(double mean, double standard_deviation) const;
};

#define lgpRandom (*(LGPRandom::Instance()))
#endif