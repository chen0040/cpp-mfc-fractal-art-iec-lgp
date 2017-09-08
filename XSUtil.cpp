#include "StdAfx.h"
#include "XSUtil.h"
#include <io.h>
#include <sstream>

XSUtil::XSUtil(void)
{
	CString debug_path=this->GetApplicationDirectoryPath()+_T("\\xspac_debug.txt");
	fout.open(CT2CA(debug_path));
}

XSUtil::~XSUtil(void)
{
	fout.close();
}

XSUtil* XSUtil::Instance()
{
	static XSUtil theInstance;
	return &theInstance;
}

CString XSUtil::GetApplicationDirectoryPath()
{
	TCHAR path[MAX_PATH];
	::GetModuleFileName(NULL, path, MAX_PATH);

	CString AppPath(path);

	int point=AppPath.ReverseFind('\\');

	return AppPath.Left(point);
}

CString XSUtil::GetFullPath(CString relative_path)
{
	CString AppDir=GetApplicationDirectoryPath();
	CString FullPath;
	FullPath.Format(_T("%s\\%s"), AppDir, relative_path);
	return FullPath;
}

std::string XSUtil::GetFullPath(std::string relative_path)
{
	std::string AppDir=CT2CA(GetApplicationDirectoryPath());
	std::ostringstream oss;
	oss << AppDir << "\\" << relative_path;
	return oss.str();
}

void XSUtil::GetFilesInDirectory(CString DirectoryPath, CStringArray &files, CString filters)
{
	CFileFind fFind;
	BOOL bWorking=fFind.FindFile(DirectoryPath+_T("\\")+filters);
	while(bWorking==TRUE)
	{
		bWorking=fFind.FindNextFile();
		if(fFind.IsDots())
		{
			continue;
		}
		if(fFind.IsDirectory())
		{
			continue;
		}
		files.Add(fFind.GetFilePath());
	}
	fFind.Close();
}

void XSUtil::ExecuteProcess(CString instruction)
{
	STARTUPINFO siStartupInfo;
	PROCESS_INFORMATION piProcessInfo;
	memset(&siStartupInfo, 0, sizeof(siStartupInfo));
	memset(&piProcessInfo, 0, sizeof(piProcessInfo));
	siStartupInfo.cb = sizeof(siStartupInfo);

	//const_cast<LPCWSTR>
	if (CreateProcess(NULL, instruction.GetBuffer(),
							  NULL, NULL, false,
							  NORMAL_PRIORITY_CLASS | CREATE_NO_WINDOW, NULL, NULL,
							  &siStartupInfo, &piProcessInfo) != false)
	{
		WaitForSingleObject(piProcessInfo.hProcess, INFINITE); //
	}
	else
	{
		AfxMessageBox(_T("An error occurred during call to CreateProcess() in XSUtil::ExecuteProcess(CString)"));
	}
	instruction.ReleaseBuffer();

	/* Release handles */
	CloseHandle(piProcessInfo.hProcess);
	CloseHandle(piProcessInfo.hThread);
}

bool XSUtil::FileExists(CString FilePath)
{
	if(_access(CT2CA(FilePath), 0)==-1)
	{
		return false;
	}
	return true;
}
