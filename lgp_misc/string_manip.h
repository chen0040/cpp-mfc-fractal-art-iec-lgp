#ifndef _H_LGP_MISC_STRING_MANIP_H
#define _H_LGP_MISC_STRING_MANIP_H
#include <string>

std::string lgp_int2string(int number);
int lgp_string2int(std::string value);

std::string lgp_join(std::string sentence1, std::string sentence2);

#endif
