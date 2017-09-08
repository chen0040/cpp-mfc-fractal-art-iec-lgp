#pragma once


// CDlgMicroMutationConfig dialog

class CDlgMicroMutationConfig : public CDialog
{
	DECLARE_DYNAMIC(CDlgMicroMutationConfig)

public:
	CDlgMicroMutationConfig(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgMicroMutationConfig();

// Dialog Data
	enum { IDD = IDD_DIALOG_MICRO_MUTATION };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	double mRegisterProb;
	double mOperatorProb;
	double mConstantProb;
};
