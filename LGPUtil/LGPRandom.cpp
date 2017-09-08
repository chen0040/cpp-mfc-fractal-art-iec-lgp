#include "stdafx.h"
#include "LGPRandom.h"
#include <ctime>
#include <cstdlib>
#include <cmath>

LGPRandom::LGPRandom()
{
	srand(static_cast<unsigned int>(time(NULL)));
}

LGPRandom::~LGPRandom()
{

}

LGPRandom* LGPRandom::Instance()
{
	static LGPRandom theInstance;
	return &theInstance;
}

unsigned int LGPRandom::nextInt(unsigned int upper_bound) const
{
	if(upper_bound==0)
	{
		return 0;
	}

	return rand() % upper_bound;
}

double LGPRandom::nextDouble() const
{
	return static_cast<double>(rand())/ (static_cast<double>(RAND_MAX) + 1.0);
}

double LGPRandom::normal(double mean, double standard_deviation) const
{
	double u1,u2,r,theta,v,pi=3.141592654;
	u1 = nextDouble();
	u2 = nextDouble();

	r = sqrt(-2.0*log(u1));
	theta =2.0*pi*u2;
	v = r*cos(theta);

	return ( standard_deviation * v + mean);
}
