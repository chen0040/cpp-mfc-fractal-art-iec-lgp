#ifndef _H_LGP_IO_MANIP_H
#define _H_LGP_IO_MANIP_H

#include <string>

bool lgp_copy_file(std::string source_file_name, std::string destination_file_name);
bool file_exists(std::string file);
void make_dir_if_not_exists(std::string dir);

#endif
