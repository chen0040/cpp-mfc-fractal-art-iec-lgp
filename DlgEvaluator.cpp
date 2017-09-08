// DlgEvaluator.cpp : implementation file
//

#include "stdafx.h"
#include "GeneticArtVC.h"
#include "DlgEvaluator.h"
#include "PixelArtist/PixelArtist.h"
#include "XSUtil.h"
#include "CPPCompiler.h"
#include "DlgImgConfig.h"

// CDlgEvaluator dialog

IMPLEMENT_DYNAMIC(CDlgEvaluator, CDialog)

CDlgEvaluator::CDlgEvaluator(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgEvaluator::IDD, pParent)
	, m_score(0)
	, m_program(NULL)
{
	
}

CDlgEvaluator::~CDlgEvaluator()
{
}

void CDlgEvaluator::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_CODE, m_editCS);
}


BEGIN_MESSAGE_MAP(CDlgEvaluator, CDialog)
	ON_WM_KEYDOWN()
	ON_BN_CLICKED(ID_SCORE0, &CDlgEvaluator::OnBnClickedScore0)
	ON_BN_CLICKED(ID_SCORE1, &CDlgEvaluator::OnBnClickedScore1)
	ON_BN_CLICKED(ID_SCORE2, &CDlgEvaluator::OnBnClickedScore2)
	ON_BN_CLICKED(ID_SCORE3, &CDlgEvaluator::OnBnClickedScore3)
	ON_BN_CLICKED(ID_SCORE4, &CDlgEvaluator::OnBnClickedScore4)
	ON_BN_CLICKED(ID_SCORE5, &CDlgEvaluator::OnBnClickedScore5)
	ON_BN_CLICKED(ID_SCORE6, &CDlgEvaluator::OnBnClickedScore6)
	ON_BN_CLICKED(ID_SCORE7, &CDlgEvaluator::OnBnClickedScore7)
	ON_BN_CLICKED(ID_SCORE8, &CDlgEvaluator::OnBnClickedScore8)
	ON_BN_CLICKED(ID_SCORE9, &CDlgEvaluator::OnBnClickedScore9)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON_BUILD_SCRIPT, &CDlgEvaluator::OnBnClickedButtonBuildScript)
	ON_BN_CLICKED(IDC_BUTTON_BUILD_CODES, &CDlgEvaluator::OnBnClickedButtonBuildCodes)
	ON_BN_CLICKED(IDC_BUTTON_COMPILE, &CDlgEvaluator::OnBnClickedButtonCompile)
	ON_BN_CLICKED(IDC_BUTTON_LOAD, &CDlgEvaluator::OnBnClickedButtonLoad)
	ON_BN_CLICKED(IDC_BUTTON_MUTATE, &CDlgEvaluator::OnBnClickedButtonMutate)
	ON_BN_CLICKED(IDC_BUTTON_CREATE, &CDlgEvaluator::OnBnClickedButtonCreate)
	ON_BN_CLICKED(IDC_BUTTON_CANCELACTION, &CDlgEvaluator::OnBnClickedButtonCancelaction)
	ON_BN_CLICKED(IDC_BUTTON_GENIMAGE, &CDlgEvaluator::OnBnClickedButtonGenimage)
END_MESSAGE_MAP()


// CDlgEvaluator message handlers

void CDlgEvaluator::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default
	
	CDialog::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CDlgEvaluator::OnBnClickedScore0()
{
	// TODO: Add your control notification handler code here
	m_score=0;
	CDialog::OnOK();
}

void CDlgEvaluator::OnBnClickedScore1()
{
	// TODO: Add your control notification handler code here
	m_score=1;
	CDialog::OnOK();
}

void CDlgEvaluator::OnBnClickedScore2()
{
	// TODO: Add your control notification handler code here
	m_score=2;
	CDialog::OnOK();
}

void CDlgEvaluator::OnBnClickedScore3()
{
	// TODO: Add your control notification handler code here
	m_score=3;
	CDialog::OnOK();
}

void CDlgEvaluator::OnBnClickedScore4()
{
	// TODO: Add your control notification handler code here
	m_score=4;
	CDialog::OnOK();
}

void CDlgEvaluator::OnBnClickedScore5()
{
	// TODO: Add your control notification handler code here
	m_score=5;
	CDialog::OnOK();
}

void CDlgEvaluator::OnBnClickedScore6()
{
	// TODO: Add your control notification handler code here
	m_score=6;
	CDialog::OnOK();
}

void CDlgEvaluator::OnBnClickedScore7()
{
	// TODO: Add your control notification handler code here
	m_score=7;
	CDialog::OnOK();
}

void CDlgEvaluator::OnBnClickedScore8()
{
	// TODO: Add your control notification handler code here
	m_score=8;
	CDialog::OnOK();
}

void CDlgEvaluator::OnBnClickedScore9()
{
	// TODO: Add your control notification handler code here
	m_score=9;
	CDialog::OnOK();
}

void CDlgEvaluator::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	// Do not call CDialog::OnPaint() for painting messages

	m_image.StretchBlt(dc.m_hDC, 10, 10, 400, 300, SRCCOPY);
}

void CDlgEvaluator::CreateArt(PixelArtist* pProgram)
{
	if(!m_image.IsNull())
	{
		m_image.Destroy();	
	}
	m_image.Create(200, 150, 24);
	pProgram->Paint(m_image);
	m_program=pProgram;
}

double CDlgEvaluator::GetScore(void) const
{
	return m_score;
}

void CDlgEvaluator::OnBnClickedButtonBuildScript()
{
	// TODO: Add your control notification handler code here
	TCHAR saved_current_directory[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, saved_current_directory);

	CFileDialog saveAsDlg(FALSE, _T("lgp"), _T("pixel_artist.lgp"), OFN_OVERWRITEPROMPT, _T("Linear GP Files (*.lgp)|*.lgp||"));

	if(saveAsDlg.DoModal()!=IDOK)
	{
		return;
	}

	std::string script_name=CT2CA(saveAsDlg.GetPathName());

	SetCurrentDirectory(saved_current_directory);

	unsigned int input_count=2;
	unsigned int output_count=3;
	ParamPairList params;
	params["width"]="400";
	params["height"]="300";
	m_program->BuildScript(script_name, input_count, output_count, params, true);
}

void CDlgEvaluator::OnBnClickedButtonBuildCodes()
{
	// TODO: Add your control notification handler code here
	TCHAR saved_current_directory[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, saved_current_directory);

	CFileDialog saveAsDlg(FALSE, _T("bat"), _T("pixel_artist_exe.bat"), OFN_OVERWRITEPROMPT, _T("Batch File (*.bat)|*.bat||"));

	int ext_count=CString(_T("_exe.bat")).GetLength();
	if(saveAsDlg.DoModal()!=IDOK)
	{
		return;
	}

	CString makefile_name_mfc=saveAsDlg.GetPathName();

	SetCurrentDirectory(saved_current_directory);

	CString destination_folder_path=makefile_name_mfc.Left(makefile_name_mfc.ReverseFind('\\'));

	std::string makefile_name=CT2CA(makefile_name_mfc);
	std::string script_name=makefile_name;

	script_name.replace(script_name.begin()+(script_name.length()-ext_count), script_name.end(), ".lgp");

	unsigned int input_count=2;
	unsigned int output_count=3;
	ParamPairList params;
	params["width"]="400";
	params["height"]="300";
	m_program->BuildScript(script_name, input_count, output_count, params, true);

	std::string folder_name=makefile_name;
	folder_name.replace(folder_name.begin()+(folder_name.length()-ext_count), folder_name.end(), "source_codes");

	m_program->BuildCodes(script_name, "lgp_program", folder_name);

	CStringArray source_files;
	xsUtil.GetFilesInDirectory(CString(CA2CT(folder_name.c_str())), source_files, _T("*.cpp"));

	CString executable_name=makefile_name_mfc.Left(makefile_name_mfc.GetLength()-ext_count)+_T(".exe");

	cppCompiler.BuildMakeFile(makefile_name_mfc, source_files, executable_name);

	CString sdl_dll_path_source=xsUtil.GetApplicationDirectoryPath()+_T("\\SDL.dll");
	CString sdl_dll_path_destination=destination_folder_path+_T("\\SDL.dll");
	CopyFile(sdl_dll_path_source, sdl_dll_path_destination, FALSE);
}

BOOL CDlgEvaluator::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	if(m_program != NULL)
	{
		if(m_program->HasValidFitness())
		{
			m_score=m_program->GetFitness();

			CString title;
			title.Format(_T("Linear GP = %f"), m_score);
			this->SetWindowText(title);
		}
		else
		{
			CString title=_T("Linear GP = Undefined Fitness");
			this->SetWindowText(title);
		}

		CString msg=CA2CT(m_program->ToString(true).c_str());
		msg.Replace(_T("\n"), _T("\r\n"));

		m_editCS.SetWindowText(msg);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgEvaluator::OnBnClickedButtonCompile()
{
	// TODO: Add your control notification handler code here
	TCHAR saved_current_directory[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, saved_current_directory);

	CFileDialog saveAsDlg(FALSE, _T("exe"), _T("pixel_artist.exe"), OFN_OVERWRITEPROMPT, _T("Executable (*.exe)|*.exe||"));

	if(saveAsDlg.DoModal()!=IDOK)
	{
		return;
	}

	CString executable_name_mfc=saveAsDlg.GetPathName();

	SetCurrentDirectory(saved_current_directory);

	CString destination_folder_path=executable_name_mfc.Left(executable_name_mfc.ReverseFind('\\'));

	std::string executable_name=CT2CA(executable_name_mfc);
	std::string script_name=executable_name;

	script_name.replace(script_name.begin()+(script_name.length()-4), script_name.end(), ".lgp");

	unsigned int input_count=2;
	unsigned int output_count=3;
	ParamPairList params;
	params["width"]="400";
	params["height"]="300";
	m_program->BuildScript(script_name, input_count, output_count, params, true);

	std::string folder_name=executable_name;
	folder_name.replace(folder_name.begin()+(folder_name.length()-4), folder_name.end(), "source_codes");

	m_program->BuildCodes(script_name, "lgp_program", folder_name);

	CStringArray source_files;
	xsUtil.GetFilesInDirectory(CString(CA2CT(folder_name.c_str())), source_files, _T("*.cpp"));

	CString make_file_name=executable_name_mfc.Left(executable_name_mfc.GetLength()-4)+_T("_exe.bat");

	cppCompiler.BuildMakeFile(make_file_name, source_files, executable_name_mfc);
	cppCompiler.Compile(source_files, executable_name_mfc);

	CString sdl_dll_path_source=xsUtil.GetApplicationDirectoryPath()+_T("\\SDL.dll");
	CString sdl_dll_path_destination=destination_folder_path+_T("\\SDL.dll");
	CopyFile(sdl_dll_path_source, sdl_dll_path_destination, FALSE);
}

void CDlgEvaluator::OnBnClickedButtonLoad()
{
	// TODO: Add your control notification handler code here
	TCHAR saved_current_directory[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, saved_current_directory);

	CFileDialog openAsDlg(TRUE, _T("lgp"), _T("pixel_artist.lgp"), OFN_OVERWRITEPROMPT, _T("Linear GP (*.lgp)|*.lgp||"));

	if(openAsDlg.DoModal()!=IDOK)
	{
		return;
	}

	std::string script_name=CT2CA(openAsDlg.GetPathName());

	SetCurrentDirectory(saved_current_directory);

	if(m_program != NULL)
	{
		m_program->CreateFromScript(script_name);

		CString msg=CA2CT(m_program->ToString(true).c_str());
		msg.Replace(_T("\n"), _T("\r\n"));

		m_editCS.SetWindowText(msg);

		m_program->Paint(m_image);
		this->Invalidate(FALSE);
	}	
}

void CDlgEvaluator::OnBnClickedButtonMutate()
{
	// TODO: Add your control notification handler code here
	if(m_program != NULL)
	{
		m_program->MicroMutate();

		CString msg=CA2CT(m_program->ToString(true).c_str());
		msg.Replace(_T("\n"), _T("\r\n"));

		m_editCS.SetWindowText(msg);

		m_program->Paint(m_image);
		this->Invalidate(FALSE);
	}	
}

void CDlgEvaluator::OnBnClickedButtonCreate()
{
	// TODO: Add your control notification handler code here

	if(m_program != NULL)
	{
		unsigned int size=m_program->GetInstructionCount();
		m_program->Create(size);

		CString msg=CA2CT(m_program->ToString(true).c_str());
		msg.Replace(_T("\n"), _T("\r\n"));

		m_editCS.SetWindowText(msg);

		m_program->Paint(m_image);
		this->Invalidate(FALSE);
	}	
}

void CDlgEvaluator::OnBnClickedButtonCancelaction()
{
	// TODO: Add your control notification handler code here
	CDialog::OnOK();
}

void CDlgEvaluator::OnBnClickedButtonGenimage()
{
	// TODO: Add your control notification handler code here
	CDlgImgConfig dlg;
	dlg.m_img_height=300;
	dlg.m_img_width=400;
	if(dlg.DoModal() != IDOK)
	{
		return;
	}

	int img_width=dlg.m_img_width;
	int img_height=dlg.m_img_height;
	CString img_path=dlg.m_img_path;

	CImage img;
	img.Create(img_width, img_height, 24);

	if(m_program != NULL)
	{
		m_program->Paint(img);
	}

	img.Save(img_path);

	img.Destroy();

	AfxMessageBox(_T("Image Saved!!!"), MB_OK);

}
