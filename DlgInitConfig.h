#pragma once
#include "LGPConfig/LGPConfig.h"


// CDlgInitConfig dialog

class CDlgInitConfig : public CDialog
{
	DECLARE_DYNAMIC(CDlgInitConfig)

public:
	CDlgInitConfig(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgInitConfig();

// Dialog Data
	enum { IDD = IDD_DIALOG_INIT_CONFIG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	int mPopSize;
	int mRegisterCount;
	afx_msg void OnBnClickedOk();
	BOOL mLoadFromScripts;
};
