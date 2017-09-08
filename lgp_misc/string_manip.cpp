#include "stdafx.h"
#include "string_manip.h"
#include <sstream>

std::string lgp_int2string(int number)
{
	std::ostringstream oss;
	oss << number;
	return oss.str();
}

int lgp_string2int(std::string value)
{
	int number;
	std::istringstream iss(value);
	iss >> number;
	return number;
}

std::string lgp_join(std::string sentence1, std::string sentence2)
{
	std::ostringstream oss;
	oss << sentence1 << sentence2;
	return oss.str();
}
