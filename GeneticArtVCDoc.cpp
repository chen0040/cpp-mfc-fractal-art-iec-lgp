// GeneticArtVCDoc.cpp : implementation of the CGeneticArtVCDoc class
//

#include "stdafx.h"
#include "GeneticArtVC.h"

#include "GeneticArtVCDoc.h"
#include "MVCSubscriber.h"
#include "Viewport.h"
#include "LGPUtil/LGPLogger.h"
#include "PixelArtist/PixelArtist.h"
#include "DlgInitConfig.h"
#include "DlgEvoConfig.h"
#include "DlgMicroMutationConfig.h"
#include "XSUtil.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGeneticArtVCDoc

IMPLEMENT_DYNCREATE(CGeneticArtVCDoc, CDocument)

BEGIN_MESSAGE_MAP(CGeneticArtVCDoc, CDocument)
	ON_COMMAND(ID_EVOLUTION_EVOLVE, &CGeneticArtVCDoc::OnEvolutionEvolve)
	ON_COMMAND(ID_EVOLUTION_RUNSCRIPT, &CGeneticArtVCDoc::OnEvolutionRunscript)
	ON_COMMAND(ID_CONFIGURATION_LGPCONFIG, &CGeneticArtVCDoc::OnConfigurationLgpconfig)
	ON_UPDATE_COMMAND_UI(ID_CONFIGURATION_LGPCONFIG, &CGeneticArtVCDoc::OnUpdateConfigurationLgpconfig)
	ON_COMMAND(ID_LGPCONFIG_EVOLUTIONCONFIG, &CGeneticArtVCDoc::OnLgpconfigEvolutionconfig)
	ON_COMMAND(ID_LGPCONFIG_MICROMUTATIONCONFIG, &CGeneticArtVCDoc::OnLgpconfigMicromutationconfig)
	ON_COMMAND(ID_FILE_OPEN, &CGeneticArtVCDoc::OnFileOpen)
END_MESSAGE_MAP()


// CGeneticArtVCDoc construction/destruction

CGeneticArtVCDoc::CGeneticArtVCDoc()
: m_lgp_configuration_file(xsUtil.GetFullPath("LGPConfig.xml").c_str())
, mThumbnailViewLeft(0.01)
, mThumbnailViewTop(0.01)
, mThumbnailViewWidth(0.7)
, mThumbnailViewHeight(0.8)
, mCommandViewLeft(0.01)
, mCommandViewTop(0.815)
, mCommandViewWidth(0.7)
, mCommandViewHeight(0.175)
, mThumbnailGapH(0.05)
, mThumbnailGapV(0.05)
, m_pHoverThumbnail(NULL)
//, m_incubator_port(NULL)
, mIncubatorViewLeft(0.715)
, mIncubatorViewTop(0.01)
, mIncubatorViewWidth(0.275)
, mIncubatorViewHeight(0.98)
, mIncubatorPortLeft(0.02)
, mIncubatorPortTop(0.01)
, mIncubatorPortWidth(0.96)
, mIncubatorPortHeight(0.49)
, mCmdEvolve(_T("Evolve (G1)"))
, mCmdRunScript(_T("Run Script"))
, mCmdRefresh(_T("Refresh"))
, mGPText(_T("LGP Evolution Unitialized"))
, mLoadFromScripts(true)
{
	// TODO: add one-time construction code here
	this->SetConfig(&m_lgp_configuration_file);
	mvcSubscriber.SetDoc(this);

	CreateThumbnails();

	/*
	m_incubator_port=new CViewport(
		mIncubatorViewLeft + mIncubatorPortLeft * mIncubatorViewWidth,
		mIncubatorViewTop + mIncubatorPortTop * mIncubatorViewHeight,
		mIncubatorViewWidth * mIncubatorPortWidth,
		mIncubatorViewHeight * mIncubatorPortHeight);
		*/

	CXSButton* pButton=NULL;

	pButton=new CXSButton(mCmdEvolve, 0.01, 0.05, 0.16, 0.25);
	m_commands.push_back(pButton);

	pButton=new CXSButton(mCmdRunScript, 0.01, 0.31, 0.16, 0.25);
	m_commands.push_back(pButton);

	pButton=new CXSButton(mCmdRefresh, 0.01, 0.57, 0.16, 0.25);
	m_commands.push_back(pButton);
}

CGeneticArtVCDoc::~CGeneticArtVCDoc()
{
	if(!m_buffer.IsNull())
	{
		m_buffer.Destroy();
	}

	ViewportGroup::iterator pos_vp;
	for(pos_vp=m_thumbnails.begin(); pos_vp != m_thumbnails.end(); ++pos_vp)
	{
		delete *pos_vp;
	}
	m_thumbnails.clear();

	/*
	if(m_incubator_port)
	{
		delete m_incubator_port;
		m_incubator_port=NULL;
	}
	*/

	std::vector<CXSButton*>::iterator pos_c;
	for(pos_c=m_commands.begin(); pos_c != m_commands.end(); ++pos_c)
	{
		delete *pos_c;
	}
	m_commands.clear();
}

BOOL CGeneticArtVCDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CGeneticArtVCDoc serialization

void CGeneticArtVCDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}


// CGeneticArtVCDoc diagnostics

#ifdef _DEBUG
void CGeneticArtVCDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CGeneticArtVCDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// this method is called by CGeneticArtVCView::OnSize() when the window is resized

void CGeneticArtVCDoc::OnSize(const CRect& client_rect)
{
	if(!m_buffer.IsNull())
	{
		m_buffer.Destroy();
	}
	m_buffer.Create(client_rect.Width(), client_rect.Height(), 24);

	unsigned int program_count=m_lgp_configuration_file.GetPopulationSize();
	for(unsigned int k=0; k<program_count; ++k)
	{
		m_thumbnails[k]->OnSize(client_rect);
	}

	//m_incubator_port->OnSize(client_rect);
}

void CGeneticArtVCDoc::Render(CDC* pDC , const CRect& client_rect)
{
	if(m_buffer.IsNull())
	{
		m_buffer.Create(client_rect.Width(), client_rect.Height(), 24);
	}

	CDC* buffer_dc=CDC::FromHandle(m_buffer.GetDC());

	RenderBackground(buffer_dc, client_rect);
	RenderThumbnailView(buffer_dc, client_rect);
	RenderIncubatorView(buffer_dc, client_rect);
	RenderCommandView(buffer_dc, client_rect);

	m_buffer.ReleaseDC();

	m_buffer.BitBlt(pDC->m_hDC, 0, 0, SRCCOPY);
}

// paint the background of the client rect
void CGeneticArtVCDoc::RenderBackground(CDC* pDC , const CRect& client_rect)
{
	CPen pen;
	pen.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	CBrush brush;
	brush.CreateSolidBrush(RGB(204, 204, 255));

	CPen* old_pen=pDC->SelectObject(&pen);
	CBrush* old_brush=pDC->SelectObject(&brush);

	pDC->Rectangle(client_rect);

	pDC->SelectObject(old_pen);
	pDC->SelectObject(old_brush);

	pen.DeleteObject();
	brush.DeleteObject();
}

// render the thumbnail view window
void CGeneticArtVCDoc::RenderThumbnailView(CDC* pDC, const CRect& client_rect)
{
	CPen pen;
	pen.CreatePen(PS_SOLID, 1, RGB(180, 180, 255));
	CBrush brush;
	brush.CreateSolidBrush(RGB(224, 224, 255));

	CPen* old_pen=pDC->SelectObject(&pen);
	CBrush* old_brush=pDC->SelectObject(&brush);

	CRect thumbnail_view_rect;
	thumbnail_view_rect.left=static_cast<LONG>(client_rect.left+mThumbnailViewLeft*client_rect.Width());
	thumbnail_view_rect.top=static_cast<LONG>(client_rect.top+mThumbnailViewTop*client_rect.Height());
	thumbnail_view_rect.right=static_cast<LONG>(thumbnail_view_rect.left + mThumbnailViewWidth * client_rect.Width());
	thumbnail_view_rect.bottom=static_cast<LONG>(thumbnail_view_rect.top+mThumbnailViewHeight * client_rect.Height());

	//pDC->Rectangle(thumbnail_view_rect);
	pDC->RoundRect(thumbnail_view_rect.left, thumbnail_view_rect.top, thumbnail_view_rect.right, thumbnail_view_rect.bottom, 10, 10);

	pDC->SelectObject(old_pen);
	pDC->SelectObject(old_brush);

	pen.DeleteObject();
	brush.DeleteObject();

	ViewportGroup::const_iterator pos_vp;
	for(pos_vp=m_thumbnails.begin(); pos_vp != m_thumbnails.end(); ++pos_vp)
	{
		(*pos_vp)->Render(pDC, client_rect);
	}
}

// called by CGeneticArtVCView::OnMouseMove
bool CGeneticArtVCDoc::OnMouseMove(UINT nFlags, const CRect& client_rect, CPoint point)
{
	bool changed=false;

	if(m_pHoverThumbnail != NULL)
	{
		m_pHoverThumbnail->SetMouseHovered(false);
	}

	CViewport* pHoverThumbnail=NULL;
	ViewportGroup::iterator pos_vp;
	for(pos_vp=m_thumbnails.begin(); pos_vp != m_thumbnails.end(); ++pos_vp)
	{
		if((*pos_vp)->IsMouseHovered(client_rect, point))
		{
			(*pos_vp)->SetMouseHovered(true);
			pHoverThumbnail=(*pos_vp);
			break;
		}
	}

	if(m_pHoverThumbnail != pHoverThumbnail)
	{
		m_pHoverThumbnail=pHoverThumbnail;
		if(pHoverThumbnail != NULL)
		{
			mIncubatorText=pHoverThumbnail->ToString();
		}
		else
		{
			mIncubatorText=_T("");
		}
		changed= true;
	}

	/*
	bool prev_hover=m_incubator_port->GetMouseHovered();
	if(m_incubator_port->IsMouseHovered(client_rect, point))
	{
		m_incubator_port->SetMouseHovered(true);
		if(prev_hover==false)
		{
			changed=true;
		}
	}
	else
	{
		m_incubator_port->SetMouseHovered(false);
		if(prev_hover==true)
		{
			changed=true;
		}
	}
	*/

	std::vector<CXSButton*>::iterator pos_c;
	for(pos_c=m_commands.begin(); pos_c != m_commands.end(); ++pos_c)
	{
		if((*pos_c)->OnMouseMove(GetCommandRect(client_rect), point))
		{
			changed=true;
		}
	}

	return changed;
}

void CGeneticArtVCDoc::RenderIncubatorView(CDC* pDC, const CRect& client_rect)
{
	CPen pen;
	pen.CreatePen(PS_SOLID, 1, RGB(180, 180, 255));
	CBrush brush;
	
	//COLORREF brush_color=RGB(215, 215, 215);
	COLORREF brush_color=RGB(224, 224, 255);
	brush.CreateSolidBrush(brush_color);

	CPen* old_pen=pDC->SelectObject(&pen);
	CBrush* old_brush=pDC->SelectObject(&brush);

	CRect incubator_view_rect;
	incubator_view_rect.left=static_cast<LONG>(client_rect.left+mIncubatorViewLeft*client_rect.Width());
	incubator_view_rect.top=static_cast<LONG>(client_rect.top+mIncubatorViewTop*client_rect.Height());
	incubator_view_rect.right=static_cast<LONG>(incubator_view_rect.left + mIncubatorViewWidth * client_rect.Width());
	incubator_view_rect.bottom=static_cast<LONG>(incubator_view_rect.top+mIncubatorViewHeight * client_rect.Height());

	//pDC->Rectangle(incubator_view_rect);
	pDC->RoundRect(incubator_view_rect.left, incubator_view_rect.top, incubator_view_rect.right, incubator_view_rect.bottom, 10, 10);

	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextColor(RGB(130, 130, 255));

	CRect lgp_rect=incubator_view_rect;
	lgp_rect.InflateRect(-3, -3);
	lgp_rect.bottom=incubator_view_rect.Height() * 2 / 3;
	pDC->RoundRect(lgp_rect, CPoint(10, 10));
	lgp_rect.InflateRect(-3, -3);
	pDC->DrawText(mIncubatorText, -1, lgp_rect, DT_TOP | DT_LEFT | DT_WORDBREAK | DT_EXPANDTABS);

	CRect gp_rect=incubator_view_rect;
	gp_rect.InflateRect(-3, -3);
	gp_rect.top+=(lgp_rect.Height()+10);
	pDC->RoundRect(gp_rect, CPoint(10, 10));
	gp_rect.InflateRect(-3, -3);
	mGPText.Format(_T("Linear GP Statistics:\r\nGeneration: %d\r\nPopulation Size: %d\r\nStrategy: %s")
		, this->GetCurrentGeneration()
		, this->GetProgramCount()
		, m_lgp_configuration_file.GetEvolutionaryStrategy()==LGP_EVOLUTION_STRATEGY_STEADY_STATE ? _T("Steady State") : _T("Generational")
		);
	pDC->DrawText(mGPText, -1, gp_rect, DT_TOP | DT_LEFT | DT_WORDBREAK | DT_EXPANDTABS);

	pDC->SelectObject(old_pen);
	pDC->SelectObject(old_brush);

	pen.DeleteObject();
	brush.DeleteObject();

	//m_incubator_port->Render(pDC, client_rect);
}

CRect CGeneticArtVCDoc::GetCommandRect(const CRect& client_rect)
{
	CRect command_view_rect;
	command_view_rect.left=static_cast<LONG>(client_rect.left+mCommandViewLeft*client_rect.Width());
	command_view_rect.top=static_cast<LONG>(client_rect.top+mCommandViewTop*client_rect.Height());
	command_view_rect.right=static_cast<LONG>(command_view_rect.left + mCommandViewWidth * client_rect.Width());
	command_view_rect.bottom=static_cast<LONG>(command_view_rect.top+mCommandViewHeight * client_rect.Height());

	return command_view_rect;
}

void CGeneticArtVCDoc::RenderCommandView(CDC* pDC, const CRect& client_rect)
{
	CPen pen;
	pen.CreatePen(PS_SOLID, 1, RGB(180, 180, 255));
	CBrush brush;
	
	//COLORREF brush_color=RGB(215, 215, 215);
	COLORREF brush_color=RGB(224, 224, 255);
	brush.CreateSolidBrush(brush_color);

	CPen* old_pen=pDC->SelectObject(&pen);
	CBrush* old_brush=pDC->SelectObject(&brush);

	CRect command_view_rect=GetCommandRect(client_rect);

	//pDC->Rectangle(command_view_rect);
	pDC->RoundRect(command_view_rect.left, command_view_rect.top, command_view_rect.right, command_view_rect.bottom, 10, 10);

	pDC->SelectObject(old_pen);
	pDC->SelectObject(old_brush);

	pen.DeleteObject();
	brush.DeleteObject();

	std::vector<CXSButton*>::iterator pos_c;
	for(pos_c=m_commands.begin(); pos_c != m_commands.end(); ++pos_c)
	{
		(*pos_c)->Render(pDC, command_view_rect);
	}
}

bool CGeneticArtVCDoc::OnLButtonDown(UINT nFlags, const CRect& client_rect, CPoint point)
{
	CString command=_T("");
	std::vector<CXSButton*>::iterator pos_c;
	for(pos_c=m_commands.begin(); pos_c != m_commands.end(); ++pos_c)
	{
		if((*pos_c)->IsMouseHovered())
		{
			command=(*pos_c)->GetButtonID();
			break;
		}
	}

	if(command==mCmdEvolve)
	{
		this->OnEvolutionEvolve();
		return true;
	}
	else if(command==mCmdRunScript)
	{
		this->OnEvolutionRunscript();
		return false;
	}
	else if(command==mCmdRefresh)
	{
		ViewportGroup::iterator pos_vp;
		for(pos_vp=m_thumbnails.begin(); pos_vp != m_thumbnails.end(); ++pos_vp)
		{
			(*pos_vp)->Invalidate();
		}
		return true;
	}
	
	return false;
}

void CGeneticArtVCDoc::OnEvolutionEvolve()
{
	// TODO: Add your command handler code here
	if(!this->IsSetup())
	{
		this->BreedInitialPopulation(mLoadFromScripts);

		unsigned int program_count=this->GetProgramCount();
		for(unsigned int k=0; k<program_count; ++k)
		{
			m_thumbnails[k]->SetArtist(this->GetPixelArtist(k));
			m_thumbnails[k]->Invalidate();
		}
	}
	else
	{
		this->Evolve();

		unsigned int program_count=this->GetProgramCount();
		for(unsigned int k=0; k<program_count; ++k)
		{
			m_thumbnails[k]->SetArtist(this->GetPixelArtist(k));
			m_thumbnails[k]->Invalidate();
		}
	}
	mvcSubscriber.InvalidateView(FALSE);
}

bool CGeneticArtVCDoc::OnLButtonDbClk(int nFlags, const CRect& client_rect, CPoint point)
{
	bool changed=false;

	CViewport* pHoverThumbnail=NULL;
	ViewportGroup::iterator pos_vp;
	for(pos_vp=m_thumbnails.begin(); pos_vp != m_thumbnails.end(); ++pos_vp)
	{
		if((*pos_vp)->OnLButtonDbClk(nFlags, client_rect, point))
		{
			changed=true;
			break;
		}
	}

	//changed=m_incubator_port->OnLButtonDbClk(nFlags, client_rect, point) ? true : changed;

	return changed;
}

void CGeneticArtVCDoc::OnEvolutionRunscript()
{
	// TODO: Add your command handler code here

	TCHAR saved_current_directory[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, saved_current_directory);

	CFileDialog openAsDlg(TRUE, _T("lgp"), _T("pixel_artist.lgp"), OFN_OVERWRITEPROMPT, _T("Linear GP (*.lgp)|*.lgp||"));
	
	if(openAsDlg.DoModal()!=IDOK)
	{
		return;
	}

	std::string script_name=CT2CA(openAsDlg.GetPathName());

	SetCurrentDirectory(saved_current_directory);


	PixelArtist program(&m_lgp_configuration_file);
	program.CreateFromScript(script_name);

	program.EvaluateFitness(NULL);	

	
}

void CGeneticArtVCDoc::OnConfigurationLgpconfig()
{
	// TODO: Add your command handler code here
	CDlgInitConfig dlg;
	int iPopSize=static_cast<int>(m_lgp_configuration_file.GetPopulationSize());
	dlg.mPopSize=iPopSize;
	dlg.mRegisterCount=static_cast<int>(m_lgp_configuration_file.GetNumRegisters());
	dlg.mLoadFromScripts=mLoadFromScripts ? TRUE : FALSE;

	if(dlg.DoModal()==IDOK)
	{
		bool must_invalidate=false;
		if(iPopSize != dlg.mPopSize)
		{
			iPopSize=dlg.mPopSize;
			m_lgp_configuration_file.SetPopulationSize(static_cast<unsigned int>(iPopSize));
			CreateThumbnails();

			/*
			ViewportGroup::iterator pos_vp;
			for(pos_vp=m_thumbnails.begin(); pos_vp != m_thumbnails.end(); ++pos_vp)
			{
				(*pos_vp)->Invalidate();
			}
			*/
			must_invalidate=true;
		}
		mLoadFromScripts = (dlg.mLoadFromScripts==TRUE) ? true : false;
		m_lgp_configuration_file.SetNumRegisters(static_cast<unsigned int>(dlg.mRegisterCount));
		if(must_invalidate)
		{
			mvcSubscriber.InvalidateView(FALSE);
		}
	}
}

void CGeneticArtVCDoc::OnUpdateConfigurationLgpconfig(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	if(this->IsSetup())
	{
		pCmdUI->Enable(FALSE);
	}
	else
	{
		pCmdUI->Enable(TRUE);
	}
}

void CGeneticArtVCDoc::CreateThumbnails(void)
{
	ViewportGroup::iterator pos_vp;
	for(pos_vp=m_thumbnails.begin(); pos_vp != m_thumbnails.end(); ++pos_vp)
	{
		delete *pos_vp;
	}
	m_thumbnails.clear();

	unsigned int population_size=m_lgp_configuration_file.GetPopulationSize();
	m_thumbnail_rows=static_cast<unsigned int>(floor(sqrt(static_cast<double>(population_size))));
	m_thumbnail_cols=static_cast<unsigned int>(ceil(sqrt(static_cast<double>(population_size))));

	if(m_thumbnail_rows * m_thumbnail_cols < population_size)
	{
		m_thumbnail_rows ++;
	}
	
	double ThumbnailWidth=mThumbnailViewWidth / m_thumbnail_cols * (1.0 - mThumbnailGapH);
	double ThumbnailHeight=mThumbnailViewHeight / m_thumbnail_rows * (1.0 - mThumbnailGapV); 

	unsigned int program_counter=0;
	for(unsigned int row=0; row < m_thumbnail_rows; ++row)
	{
		double ThumbnailTop=mThumbnailViewTop+ThumbnailHeight * row + (ThumbnailHeight * mThumbnailGapV) * (row + 0.5);
		for(unsigned int col=0; col < m_thumbnail_cols; ++col)
		{
			double ThumbnailLeft=mThumbnailViewLeft+ThumbnailWidth * col + ThumbnailWidth * mThumbnailGapH * (col+0.5);
			m_thumbnails.push_back(new CViewport(ThumbnailLeft, ThumbnailTop, ThumbnailWidth, ThumbnailHeight));
			program_counter++;
			if(program_counter >= population_size) break;
		}
	}
}

void CGeneticArtVCDoc::OnLgpconfigEvolutionconfig()
{
	// TODO: Add your command handler code here
	CDlgEvoConfig dlg;
	if(m_lgp_configuration_file.GetEvolutionaryStrategy()==LGP_EVOLUTION_STRATEGY_STEADY_STATE)
	{
		dlg.mEvoStrategy=EVO_CONFIG_STRATEGY_STEADY_STATE;
	}
	else if(m_lgp_configuration_file.GetEvolutionaryStrategy()==LGP_EVOLUTION_STRATEGY_GENERATIONAL)
	{
		dlg.mEvoStrategy=EVO_CONFIG_STRATEGY_GENERATIONAL;
	}
	dlg.mCrossoverRate=m_lgp_configuration_file.GetCrossoverRate();
	dlg.mMacroMutationRate=m_lgp_configuration_file.GetMacroMutationRate();
	dlg.mMicroMutationRate=m_lgp_configuration_file.GetMicroMutationRate();

	if(dlg.DoModal() == IDOK)
	{
		switch(dlg.mEvoStrategy)
		{
		case EVO_CONFIG_STRATEGY_GENERATIONAL:
			m_lgp_configuration_file.SetEvolutionaryStrategy(LGP_EVOLUTION_STRATEGY_GENERATIONAL);
			break;
		case EVO_CONFIG_STRATEGY_STEADY_STATE:
			m_lgp_configuration_file.SetEvolutionaryStrategy(LGP_EVOLUTION_STRATEGY_STEADY_STATE);
			break;
		}
		m_lgp_configuration_file.SetCrossoverRate(dlg.mCrossoverRate);
		m_lgp_configuration_file.SetMicroMutationRate(dlg.mMicroMutationRate);
		m_lgp_configuration_file.SetMacroMutationRate(dlg.mMacroMutationRate);
	}
}

void CGeneticArtVCDoc::OnLgpconfigMicromutationconfig()
{
	// TODO: Add your command handler code here
	CDlgMicroMutationConfig dlg;
	dlg.mRegisterProb=m_lgp_configuration_file.GetMicroMutateRegisterRate();
	dlg.mConstantProb=m_lgp_configuration_file.GetMicroMutateConstantRate();
	dlg.mOperatorProb=m_lgp_configuration_file.GetMicroMutateOperatorRate();

	if(dlg.DoModal()==IDOK)
	{
		m_lgp_configuration_file.SetMicroMutateRegisterRate(dlg.mRegisterProb);
		m_lgp_configuration_file.SetMicroMutateOperatorRate(dlg.mOperatorProb);
		m_lgp_configuration_file.setMicroMutateConstantRate(dlg.mConstantProb);
	}
}

void CGeneticArtVCDoc::OnFileOpen()
{
	// TODO: Add your command handler code here
	this->OnEvolutionRunscript();
}
