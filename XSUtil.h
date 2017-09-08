#pragma once
#include "afx.h"
#include <string>
#include <fstream>
#include <iostream>

class XSUtil :
	public CObject
{
public:
	static XSUtil* Instance();
	~XSUtil(void);

private:
	XSUtil(void);
	XSUtil(const XSUtil& rhs) { }
	XSUtil& operator=(const XSUtil& rhs) { return *this; }

public:
	void GetFilesInDirectory(CString DirectoryPath, CStringArray& files, CString filter);
	CString GetApplicationDirectoryPath();
	void ExecuteProcess(CString instruction);
	CString GetFullPath(CString relative_path);
	std::string GetFullPath(std::string relative_path);

public:
	std::ofstream fout;
	virtual bool FileExists(CString FilePath);
};

#define xsUtil (*(XSUtil::Instance()))
