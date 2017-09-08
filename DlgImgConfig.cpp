// DlgImgConfig.cpp : implementation file
//

#include "stdafx.h"
#include "GeneticArtVC.h"
#include "DlgImgConfig.h"
#include "XSUtil.h"


// CDlgImgConfig dialog

IMPLEMENT_DYNAMIC(CDlgImgConfig, CDialog)

CDlgImgConfig::CDlgImgConfig(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgImgConfig::IDD, pParent)
	, m_img_width(0)
	, m_img_height(0)
	, m_img_path(_T(""))
{

}

CDlgImgConfig::~CDlgImgConfig()
{
}

void CDlgImgConfig::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_WIDTH, m_img_width);
	DDV_MinMaxInt(pDX, m_img_width, 1, 2000000000);
	DDX_Text(pDX, IDC_EDIT_HEIGHT, m_img_height);
	DDV_MinMaxInt(pDX, m_img_height, 1, 2000000000);
	DDX_Text(pDX, IDC_EDIT_SAVEAS, m_img_path);
}


BEGIN_MESSAGE_MAP(CDlgImgConfig, CDialog)
	ON_BN_CLICKED(IDOK, &CDlgImgConfig::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CDlgImgConfig::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON_BROWSE, &CDlgImgConfig::OnBnClickedButtonBrowse)
	ON_EN_CHANGE(IDC_EDIT_WIDTH, &CDlgImgConfig::OnEnChangeEditWidth)
	ON_EN_CHANGE(IDC_EDIT_HEIGHT, &CDlgImgConfig::OnEnChangeEditHeight)
END_MESSAGE_MAP()


// CDlgImgConfig message handlers

void CDlgImgConfig::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	this->UpdateData(TRUE);
	if(m_img_path==_T(""))
	{
		AfxMessageBox(_T("image save as path should not be empty"), MB_OK);
		return;
	}
	CString folder_path=m_img_path.Left(m_img_path.ReverseFind('\\'));
	if(!xsUtil.FileExists(folder_path))
	{
		CString msg;
		msg.Format(_T("folder path %s does not exist"), folder_path);
		AfxMessageBox(msg, MB_OK);
		return;
	}
	OnOK();
}

void CDlgImgConfig::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	OnCancel();
}

void CDlgImgConfig::OnBnClickedButtonBrowse()
{
	// TODO: Add your control notification handler code here
	TCHAR saved_current_directory[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, saved_current_directory);

	CFileDialog saveAsDlg(FALSE, _T("jpg"), _T("pixel_artist.jpg"), OFN_OVERWRITEPROMPT, _T("JPEG Files (*.jpg)|*.jpg||"));

	if(saveAsDlg.DoModal()!=IDOK)
	{
		return;
	}

	CString image_path=saveAsDlg.GetPathName();

	SetCurrentDirectory(saved_current_directory);

	m_img_path=image_path;
	this->UpdateData(FALSE);
}

void CDlgImgConfig::OnEnChangeEditWidth()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	this->UpdateData(TRUE);
}

void CDlgImgConfig::OnEnChangeEditHeight()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	this->UpdateData(TRUE);
}
