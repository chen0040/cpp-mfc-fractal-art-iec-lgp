#include "stdafx.h"
#include "io_manip.h"
#include <io.h>
#include <direct.h>
#include <fstream>
#include <iostream>

bool file_exists(std::string file)
{
	if(_access(file.c_str(), 0)==-1)
	{
		return false;
	}
	return true;
}

void make_dir_if_not_exists(std::string dir)
{
	if(!file_exists(dir))
	{
		_mkdir(dir.c_str());
	}
}

bool lgp_copy_file(std::string source_file_name, std::string destination_file_name)
{
	std::ifstream ifs(source_file_name.c_str(), std::ios::binary);
	std::ofstream ofs(destination_file_name.c_str(), std::ios::binary);

	ifs.seekg(0, std::ios::end);
	long file_size = ifs.tellg();

	if(ifs.is_open() && ofs.is_open())
	{
		short * buffer = new short[file_size/2];

		//Determine the file's size
		//Then starts from the beginning
		ifs.seekg(0, std::ios::beg);

		//Then read enough of the file to fill the buffer
		ifs.read((char*)buffer, file_size);

		//And then write out all that was read
		ofs.write((char*)buffer, file_size);
		delete[] buffer;
	}
	else if(!ifs.is_open())
	{
		std::cerr <<"lgp_copy_file: failed to open "<<source_file_name<<" for reading!\n";
		return 0;
	}
	else if(!ofs.is_open())
	{
		std::cerr << "lgp_copy_file: failed to open "<< destination_file_name <<" for writing!\n";
		return 0;
	}


	return true;
}
