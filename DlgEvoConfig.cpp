// DlgEvoConfig.cpp : implementation file
//

#include "stdafx.h"
#include "GeneticArtVC.h"
#include "DlgEvoConfig.h"


// CDlgEvoConfig dialog

IMPLEMENT_DYNAMIC(CDlgEvoConfig, CDialog)

CDlgEvoConfig::CDlgEvoConfig(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgEvoConfig::IDD, pParent)
	, mEvoStrategy(EVO_CONFIG_STRATEGY_GENERATIONAL)
	, mCrossoverRate(0)
	, mMacroMutationRate(0)
	, mMicroMutationRate(0)
{

}

CDlgEvoConfig::~CDlgEvoConfig()
{
}

void CDlgEvoConfig::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_CROSSOVERRATE, mCrossoverRate);
	DDV_MinMaxDouble(pDX, mCrossoverRate, 0, 1);
	DDX_Text(pDX, IDC_EDIT_MACROMUTATIONRATE, mMacroMutationRate);
	DDV_MinMaxDouble(pDX, mMacroMutationRate, 0, 1);
	DDX_Text(pDX, IDC_EDIT_MICROMUTATIONRATE, mMicroMutationRate);
	DDV_MinMaxDouble(pDX, mMicroMutationRate, 0, 1);
}


BEGIN_MESSAGE_MAP(CDlgEvoConfig, CDialog)
	ON_BN_CLICKED(IDC_RADIO_STEADY_STATE, &CDlgEvoConfig::OnBnClickedRadioSteadyState)
	ON_BN_CLICKED(IDC_RADIO_GENERATIONAL, &CDlgEvoConfig::OnBnClickedRadioGenerational)
	ON_BN_CLICKED(IDOK, &CDlgEvoConfig::OnBnClickedOk)
END_MESSAGE_MAP()


// CDlgEvoConfig message handlers

BOOL CDlgEvoConfig::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	switch(mEvoStrategy)
	{
	case EVO_CONFIG_STRATEGY_STEADY_STATE:
		this->CheckDlgButton(IDC_RADIO_STEADY_STATE, 1);
		break;
	case EVO_CONFIG_STRATEGY_GENERATIONAL:
		this->CheckDlgButton(IDC_RADIO_GENERATIONAL, 1);
		break;
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgEvoConfig::OnBnClickedRadioSteadyState()
{
	// TODO: Add your control notification handler code here
	mEvoStrategy=EVO_CONFIG_STRATEGY_STEADY_STATE;
}

void CDlgEvoConfig::OnBnClickedRadioGenerational()
{
	// TODO: Add your control notification handler code here
	mEvoStrategy=EVO_CONFIG_STRATEGY_GENERATIONAL;
}

void CDlgEvoConfig::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	this->UpdateData(TRUE);

	OnOK();
}
