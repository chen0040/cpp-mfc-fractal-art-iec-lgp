#pragma once


// CDlgImgConfig dialog

class CDlgImgConfig : public CDialog
{
	DECLARE_DYNAMIC(CDlgImgConfig)

public:
	CDlgImgConfig(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgImgConfig();

// Dialog Data
	enum { IDD = IDD_DIALOG_IMGCONFIG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	int m_img_width;
	int m_img_height;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedButtonBrowse();
	CString m_img_path;
	afx_msg void OnEnChangeEditWidth();
	afx_msg void OnEnChangeEditHeight();
};
