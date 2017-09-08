// DlgMicroMutationConfig.cpp : implementation file
//

#include "stdafx.h"
#include "GeneticArtVC.h"
#include "DlgMicroMutationConfig.h"


// CDlgMicroMutationConfig dialog

IMPLEMENT_DYNAMIC(CDlgMicroMutationConfig, CDialog)

CDlgMicroMutationConfig::CDlgMicroMutationConfig(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgMicroMutationConfig::IDD, pParent)
	, mRegisterProb(0)
	, mOperatorProb(0)
	, mConstantProb(0)
{

}

CDlgMicroMutationConfig::~CDlgMicroMutationConfig()
{
}

void CDlgMicroMutationConfig::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_REGISTER_MUTATION_PROB, mRegisterProb);
	DDV_MinMaxDouble(pDX, mRegisterProb, 0, 1);
	DDX_Text(pDX, IDC_EDIT_OPERATOR_MUTATION_PROB, mOperatorProb);
	DDV_MinMaxDouble(pDX, mOperatorProb, 0, 1);
	DDX_Text(pDX, IDC_EDIT_CONSTANT_MUTATION_PROB, mConstantProb);
}


BEGIN_MESSAGE_MAP(CDlgMicroMutationConfig, CDialog)
	ON_BN_CLICKED(IDOK, &CDlgMicroMutationConfig::OnBnClickedOk)
END_MESSAGE_MAP()


// CDlgMicroMutationConfig message handlers

void CDlgMicroMutationConfig::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	this->UpdateData(TRUE);
	if(mConstantProb+mOperatorProb+mRegisterProb==0)
	{
		AfxMessageBox(_T("Sum of Probabilities should not be zero"), MB_OK);
		return;
	}
	OnOK();
}
