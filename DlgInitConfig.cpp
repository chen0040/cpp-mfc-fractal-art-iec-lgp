// DlgInitConfig.cpp : implementation file
//

#include "stdafx.h"
#include "GeneticArtVC.h"
#include "DlgInitConfig.h"


// CDlgInitConfig dialog

IMPLEMENT_DYNAMIC(CDlgInitConfig, CDialog)

CDlgInitConfig::CDlgInitConfig(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgInitConfig::IDD, pParent)
	, mPopSize(0)
	, mRegisterCount(0)
	, mLoadFromScripts(FALSE)
{

}

CDlgInitConfig::~CDlgInitConfig()
{
}

void CDlgInitConfig::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_POP_SIZE, mPopSize);
	DDV_MinMaxInt(pDX, mPopSize, 1, 1000);
	DDX_Text(pDX, IDC_EDIT_LGP_REGISTER_COUNT, mRegisterCount);
	DDV_MinMaxInt(pDX, mRegisterCount, 3, 1000);
	DDX_Check(pDX, IDC_CHECK_LOAD_FROM_SCRIPTS, mLoadFromScripts);
}


BEGIN_MESSAGE_MAP(CDlgInitConfig, CDialog)
	ON_BN_CLICKED(IDOK, &CDlgInitConfig::OnBnClickedOk)
END_MESSAGE_MAP()


// CDlgInitConfig message handlers


void CDlgInitConfig::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	this->UpdateData(TRUE);
	OnOK();
}
