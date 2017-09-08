#include "stdafx.h"
#include "PAOperatorSet.h"
#include "../LGPOperators/LGPOperator_Plus.h"
#include "../LGPOperators/LGPOperator_Minus.h"
#include "../LGPOperators/LGPOperator_Multiplication.h"
#include "../LGPOperators/LGPOperator_Division.h"
#include "../LGPOperators/LGPOperator_Power.h"
#include "../LGPOperators/LGPOperator_Sin.h"
#include "../LGPOperators/LGPOperator_Cos.h"
#include "../LGPOperators/LGPOperator_Exp.h"
#include "../LGPOperators/LGPOperator_Ln.h"
#include "../LGPOperators/LGPOperator_Atan.h"
#include "../LGPOperators/LGPOperator_Sinh.h"
#include "../ImgOperators/ImgOperator_Mandelbrot.h"
#include "../ImgOperators/ImgOperator_Julia.h"

PAOperatorSet::PAOperatorSet()
: LGPOperatorSet()
{
	this->AddOperator(new LGPOperator_Plus());
	this->AddOperator(new LGPOperator_Minus());
	this->AddOperator(new LGPOperator_Division());
	this->AddOperator(new LGPOperator_Multiplication());
	//this->AddOperator(new LGPOperator_Power());
	this->AddOperator(new LGPOperator_Sin());
	this->AddOperator(new LGPOperator_Cos());
	this->AddOperator(new LGPOperator_Atan());
	//this->AddOperator(new LGPOperator_Sinh());
	this->AddOperator(new LGPOperator_Exp());
	this->AddOperator(new LGPOperator_Ln());

	//the following operators come 
	this->AddOperator(new ImgOperator_Mandelbrot(2));
	this->AddOperator(new ImgOperator_Mandelbrot(3));
	this->AddOperator(new ImgOperator_Julia(2)); 
	this->AddOperator(new ImgOperator_Julia(3));
	this->AddOperator(new ImgOperator_Julia(5));

	this->AddIfltOperator();
}

PAOperatorSet::~PAOperatorSet()
{

}