#pragma once


// CDlgEvoConfig dialog

class CDlgEvoConfig : public CDialog
{
	DECLARE_DYNAMIC(CDlgEvoConfig)

public:
	CDlgEvoConfig(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgEvoConfig();

// Dialog Data
	enum { IDD = IDD_DIALOG_EVO_CONFIG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	int mEvoStrategy;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedRadioSteadyState();
	afx_msg void OnBnClickedRadioGenerational();
	double mCrossoverRate;
	double mMacroMutationRate;
	double mMicroMutationRate;
	afx_msg void OnBnClickedOk();
};

#define EVO_CONFIG_STRATEGY_STEADY_STATE 0
#define EVO_CONFIG_STRATEGY_GENERATIONAL 1