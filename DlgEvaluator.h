#pragma once
#include "afxwin.h"


// CDlgEvaluator dialog
class PixelArtist;

class CDlgEvaluator : public CDialog
{
	DECLARE_DYNAMIC(CDlgEvaluator)

public:
	CDlgEvaluator(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgEvaluator();

// Dialog Data
	enum { IDD = IDD_DIALOG_EVALUATOR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnBnClickedScore0();
	afx_msg void OnBnClickedScore1();
	afx_msg void OnBnClickedScore2();
	afx_msg void OnBnClickedScore3();
	afx_msg void OnBnClickedScore4();
	afx_msg void OnBnClickedScore5();
	afx_msg void OnBnClickedScore6();
	afx_msg void OnBnClickedScore7();
	afx_msg void OnBnClickedScore8();
	afx_msg void OnBnClickedScore9();
public:
	afx_msg void OnPaint();
protected:
	CImage m_image;
	PixelArtist* m_program;
public:
	void CreateArt(PixelArtist* pProgram);
protected:
	double m_score;
public:
	virtual double GetScore(void) const;
	afx_msg void OnBnClickedButtonBuildScript();
	afx_msg void OnBnClickedButtonBuildCodes();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonCompile();
	CEdit m_editCS;
	afx_msg void OnBnClickedButtonLoad();
	afx_msg void OnBnClickedButtonMutate();
	afx_msg void OnBnClickedButtonCreate();
	afx_msg void OnBnClickedButtonCancelaction();
	afx_msg void OnBnClickedButtonGenimage();
};
