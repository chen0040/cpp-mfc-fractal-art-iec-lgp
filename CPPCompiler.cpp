#include "StdAfx.h"
#include "CPPCompiler.h"
#include "XSUtil.h"
#include "tinyxml/tinyxml.h"
#include <sstream>

CPPCompiler* CPPCompiler::Instance()
{
	static CPPCompiler theInstance;
	return &theInstance;
}

CPPCompiler::CPPCompiler(void)
{
	mCompilerName=_T("\"")+(xsUtil.GetApplicationDirectoryPath()+_T("\\mingw\\bin\\g++.exe"))+_T("\"");

	std::ostringstream oss;
	oss << CT2CA(xsUtil.GetApplicationDirectoryPath()) << "\\" << "compiler.xml";

	TiXmlDocument doc;
	if(!doc.LoadFile(oss.str().c_str()))
	{
		AfxMessageBox(_T("Failed to load compiler.xml"), MB_OK);
		exit(0);
	}

	TiXmlElement* xml_root=doc.RootElement();
	for(TiXmlElement* xml_level1=xml_root->FirstChildElement(); xml_level1 != NULL; xml_level1=xml_level1->NextSiblingElement())
	{
		if(strcmp(xml_level1->Value(), "param")==0)
		{
			if(strcmp(xml_level1->Attribute("name"), "configuration")==0)
			{
				mCompilerConfig=CA2CT(xml_level1->Attribute("value"));
			}
			else if(strcmp(xml_level1->Attribute("name"), "output")==0)
			{
				mDefaultOutput=CA2CT(xml_level1->Attribute("value"));
			}
			else if(strcmp(xml_level1->Attribute("name"), "lib_relative")==0)
			{
				mLibRel.Add(CA2CT(xml_level1->Attribute("value")));
			}
			else if(strcmp(xml_level1->Attribute("name"), "include_relative")==0)
			{
				mIncludeRel.Add(CA2CT(xml_level1->Attribute("value")));
			}
			else if(strcmp(xml_level1->Attribute("name"), "cflags")==0)
			{
				mCflags=CA2CT(xml_level1->Attribute("value"));
			}
			else if(strcmp(xml_level1->Attribute("name"), "libs")==0)
			{
				mLibs=CA2CT(xml_level1->Attribute("value"));
			}
		}
	}
}

CPPCompiler::~CPPCompiler(void)
{
}

void CPPCompiler::Compile(const CStringArray& source_files, CString output)
{
	CString file_lst=_T("");
	for(int i=0; i<source_files.GetCount(); i++)
	{
		file_lst+=_T("\"")+source_files[i]+_T("\" ");
	}

	Compile(file_lst, output);
}

void CPPCompiler::Compile(CString& source_files, CString output)
{
	if(output==_T("")) output=mDefaultOutput;

	CString instruction;
	instruction=mCompilerName; 
	instruction+=_T(" -o \"")+output+_T("\"");

	instruction+=_T(" ") + mCompilerConfig;

	instruction+=_T(" ") + source_files;

	for(int i=0; i<mIncludeRel.GetCount(); ++i)
	{
		instruction+=_T(" -I\"")+xsUtil.GetApplicationDirectoryPath()+_T("\\")+mIncludeRel[i]+_T("\"");
	}

	instruction+=_T(" ") + mCflags;

	for(int i=0; i<mLibRel.GetCount(); ++i)
	{
		instruction+=_T(" -L\"")+xsUtil.GetApplicationDirectoryPath()+_T("\\")+mLibRel[i]+_T("\"");
	}
	
	instruction+=_T(" ") + mLibs;


	//std::cout <<  CT2CA(instruction) << std::endl;
	//xsUtil.fout << CT2CA(instruction) << std::endl;

	xsUtil.ExecuteProcess(instruction);
}

void CPPCompiler::BuildMakeFile(CString make_file_name, const CStringArray& source_files, CString output)
{
	CString file_lst=_T("");
	for(int i=0; i<source_files.GetCount(); i++)
	{
		file_lst+=_T("\"")+source_files[i]+_T("\" ");
	}

	BuildMakeFile(make_file_name, file_lst, output);
}

void CPPCompiler::BuildMakeFile(CString make_file_name, CString& source_files, CString output)
{
	if(output==_T("")) output=mDefaultOutput;

	CString instruction;
	instruction=mCompilerName; 
	instruction+=_T(" -o \"")+output+_T("\"");

	instruction+=_T(" ") + mCompilerConfig;

	instruction+=_T(" ") + source_files;

	for(int i=0; i<mIncludeRel.GetCount(); ++i)
	{
		instruction+=_T(" -I\"")+xsUtil.GetApplicationDirectoryPath()+_T("\\")+mIncludeRel[i]+_T("\"");
	}

	instruction+=_T(" ") + mCflags;

	for(int i=0; i<mLibRel.GetCount(); ++i)
	{
		instruction+=_T(" -L\"")+xsUtil.GetApplicationDirectoryPath()+_T("\\")+mLibRel[i]+_T("\"");
	}
	
	instruction+=_T(" ") + mLibs;

	CStdioFile stdFile(make_file_name, CFile::modeCreate | CFile::modeWrite);
	stdFile.WriteString(instruction);
	stdFile.Close();
}
