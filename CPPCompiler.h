#pragma once
#include "afx.h"

class CPPCompiler :
	public CObject
{
public:
	static CPPCompiler* Instance();
	~CPPCompiler(void);

private:
	CPPCompiler(void);
	CPPCompiler(const CPPCompiler& rhs) { }
	CPPCompiler& operator=(const CPPCompiler& rhs) { return *this; }

public:
	void Compile(const CStringArray& source_files, CString output=_T(""));
	void Compile(CString& source_files, CString output=_T(""));
	void BuildMakeFile(CString make_file_name, const CStringArray& source_files, CString output);
	void BuildMakeFile(CString make_file_name, CString& source_files, CString output);	

protected:
	CString mCompilerName;
	CString mCompilerConfig;
	CString mCflags;
	CString mLibs;
	CString mDefaultOutput;
	CStringArray mLibRel;
	CStringArray mIncludeRel;
};

#define cppCompiler (*(CPPCompiler::Instance()))
