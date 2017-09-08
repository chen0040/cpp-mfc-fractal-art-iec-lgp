#include "stdafx.h"
#include "ImgOperator_Mandelbrot.h"
#include <cmath>
#include <iostream>
#include <sstream>
#include "../algorithmic_image/algorithmic_image.h"

ImgOperator_Mandelbrot::ImgOperator_Mandelbrot(unsigned int degree)
: LGPOperator("")
, m_degree(degree)
{
	std::ostringstream oss;
	oss << "mandel" << m_degree;

	m_symbol=oss.str();
	m_method_name=m_symbol;
}

ImgOperator_Mandelbrot::~ImgOperator_Mandelbrot()
{

}

LGPOperator* ImgOperator_Mandelbrot::Clone() const
{
	return new ImgOperator_Mandelbrot(*this);
}

int ImgOperator_Mandelbrot::Execute(const LGPRegister *operand1, const LGPRegister *operand2, LGPRegister *destination_register)
{
	double x0=operand1->ToDouble();
	double y0=operand2->ToDouble();

	double result=0;

	switch(m_degree)
	{
	case 2:
		result=ai_mandel2(x0, y0);
		break;
	case 3:
		result=ai_mandel3(x0, y0);
		break;
	default:
		result=ai_mandel2(x0, y0);
		break;
	}
	
	destination_register->SetValue(result);

	return LGP_EXECUTE_NEXT_INSTRUCTION;
}

std::string ImgOperator_Mandelbrot::GetOperatorContent(std::string operand1, std::string operand2, std::string destination_register, std::string line_start, std::string line_end) const
{
	std::ostringstream oss;
	
	oss << line_start << destination_register << "=ai_mandel" << m_degree << "(" << operand1 << ", " << operand2 << ");" << line_end;

	return oss.str();
}

std::string ImgOperator_Mandelbrot::GetOperatorRequiredHeaderFiles() const
{
	std::ostringstream oss;
	oss << "#include <cmath>\n";
	oss << "#include \"algorithmic_image.h\"\n";
	return oss.str();
}

