#include "stdafx.h"
#include "algorithmic_image.h"

double ai_mandel2(double x0, double y0)
{
	static const int MANDELBROT_MAX_ITERATIONS=255;
	static const double BAILOUT2=4.0;

	int number=0;
	double zr=0;
	double zi=0;
	while(true)
	{
		number++;

		double zr2=zr*zr - zi*zi;
		double zi2=2*zr*zi;

		zr=zr2+x0;
		zi=zi2+y0;

		if(number > MANDELBROT_MAX_ITERATIONS)
		{
			return 0;
		}
		
		if(zr*zr + zi*zi > BAILOUT2)
		{
			return static_cast<double>(number) / MANDELBROT_MAX_ITERATIONS;
		}
	}

	return 0;
}

double ai_julia2(double x0, double y0, double c_real, double c_imagine)
{
	static const int MANDELBROT_MAX_ITERATIONS=255;
	static const double BAILOUT2=4.0;

	int number=0;
	double zr=x0;
	double zi=y0;
	while(true)
	{
		number++;

		double zr2=zr*zr - zi*zi;
		double zi2=2*zr*zi;

		zr=zr2+c_real;
		zi=zi2+c_imagine;

		if(number > MANDELBROT_MAX_ITERATIONS)
		{
			return 0;
		}
		
		if(zr*zr + zi*zi > BAILOUT2)
		{
			return static_cast<double>(number) / MANDELBROT_MAX_ITERATIONS;
		}
	}

	return 0;
}


double ai_mandel3(double x0, double y0)
{
	static const int MANDELBROT_MAX_ITERATIONS=255;
	static const double BAILOUT2=4.0;

	int number=0;
	double zr=0;
	double zi=0;
	while(true)
	{
		number++;

		double zr2=zr*zr - zi*zi;
		double zi2=2*zr*zi;

		double zr3=zr2*zr - zi2*zi;
		double zi3=zr2*zi + zr * zi2;

		zr=zr3+x0;
		zi=zi3+y0;

		if(number > MANDELBROT_MAX_ITERATIONS)
		{
			return 0;
		}
		
		if(zr*zr + zi*zi > BAILOUT2)
		{
			return static_cast<double>(number) / MANDELBROT_MAX_ITERATIONS;
		}
	}

	return 0;
}

double ai_mandel4(double x0, double y0)
{
	static const int MANDELBROT_MAX_ITERATIONS=255;
	static const double BAILOUT2=4.0;

	int number=0;
	double zr=0;
	double zi=0;
	while(true)
	{
		number++;

		double zr2=zr*zr - zi*zi;
		double zi2=2*zr*zi;

		double zr3=zr2*zr - zi2*zi;
		double zi3=zr2*zi + zr * zi2;

		double zr4=zr3*zr - zi3*zi;
		double zi4=zr3*zi + zr * zi3;

		zr=zr4+x0;
		zi=zi4+y0;

		if(number > MANDELBROT_MAX_ITERATIONS)
		{
			return 0;
		}
		
		if(zr*zr + zi*zi > BAILOUT2)
		{
			return static_cast<double>(number) / MANDELBROT_MAX_ITERATIONS;
		}
	}

	return 0;
}

double ai_julia3(double x0, double y0, double c_real, double c_imagine)
{
	static const int MANDELBROT_MAX_ITERATIONS=255;
	static const double BAILOUT2=4.0;

	int number=0;
	double zr=x0;
	double zi=y0;
	while(true)
	{
		number++;

		double zr2=zr*zr - zi*zi;
		double zi2=2*zr*zi;

		double zr3=zr2*zr - zi2*zi;
		double zi3=zr2*zi + zr * zi2;

		zr=zr3+c_real;
		zi=zi3+c_imagine;

		if(number > MANDELBROT_MAX_ITERATIONS)
		{
			return 0;
		}
		
		if(zr*zr + zi*zi > BAILOUT2)
		{
			return static_cast<double>(number) / MANDELBROT_MAX_ITERATIONS;
		}
	}

	return 0;
}

double ai_julia4(double x0, double y0, double c_real, double c_imagine)
{
	static const int MANDELBROT_MAX_ITERATIONS=255;
	static const double BAILOUT2=4.0;

	int number=0;
	double zr=x0;
	double zi=y0;
	while(true)
	{
		number++;

		double zr2=zr*zr - zi*zi;
		double zi2=2*zr*zi;

		double zr3=zr2*zr - zi2*zi;
		double zi3=zr2*zi + zr * zi2;

		double zr4=zr3*zr - zi3*zi;
		double zi4=zr3*zi + zr * zi3;

		zr=zr4+c_real;
		zi=zi4+c_imagine;

		if(number > MANDELBROT_MAX_ITERATIONS)
		{
			return 0;
		}
		
		if(zr*zr + zi*zi > BAILOUT2)
		{
			return static_cast<double>(number) / MANDELBROT_MAX_ITERATIONS;
		}
	}

	return 0;
}


double ai_julia5(double x0, double y0, double c_real, double c_imagine)
{
	static const int MANDELBROT_MAX_ITERATIONS=255;
	static const double BAILOUT2=4.0;

	int number=0;
	double zr=x0;
	double zi=y0;
	while(true)
	{
		number++;

		double zr2=zr*zr - zi*zi;
		double zi2=2*zr*zi;

		double zr3=zr2*zr - zi2*zi;
		double zi3=zr2*zi + zr * zi2;

		double zr4=zr3*zr - zi3*zi;
		double zi4=zr3*zi + zr * zi3;

		double zr5=zr4*zr - zi4*zi;
		double zi5=zr4*zi + zr * zi4;

		zr=zr5+c_real;
		zi=zi5+c_imagine;

		if(number > MANDELBROT_MAX_ITERATIONS)
		{
			return 0;
		}
		
		if(zr*zr + zi*zi > BAILOUT2)
		{
			return static_cast<double>(number) / MANDELBROT_MAX_ITERATIONS;
		}
	}

	return 0;
}
