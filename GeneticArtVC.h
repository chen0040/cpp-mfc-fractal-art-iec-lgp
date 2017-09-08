// GeneticArtVC.h : main header file for the GeneticArtVC application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CGeneticArtVCApp:
// See GeneticArtVC.cpp for the implementation of this class
//

class CGeneticArtVCApp : public CWinApp
{
public:
	CGeneticArtVCApp();


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CGeneticArtVCApp theApp;