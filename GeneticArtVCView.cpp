// GeneticArtVCView.cpp : implementation of the CGeneticArtVCView class
//

#include "stdafx.h"
#include "GeneticArtVC.h"

#include "GeneticArtVCDoc.h"
#include "GeneticArtVCView.h"
#include "MVCSubscriber.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGeneticArtVCView

IMPLEMENT_DYNCREATE(CGeneticArtVCView, CView)

BEGIN_MESSAGE_MAP(CGeneticArtVCView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_SIZE()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
END_MESSAGE_MAP()

// CGeneticArtVCView construction/destruction

CGeneticArtVCView::CGeneticArtVCView()
{
	// TODO: add construction code here
	mvcSubscriber.SetView(this);
}

CGeneticArtVCView::~CGeneticArtVCView()
{
}

BOOL CGeneticArtVCView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CGeneticArtVCView drawing

void CGeneticArtVCView::OnDraw(CDC* pDC)
{
	CGeneticArtVCDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
	CRect client_rect;
	GetClientRect(&client_rect);
	pDoc->Render(pDC, client_rect);
}


// CGeneticArtVCView printing

BOOL CGeneticArtVCView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CGeneticArtVCView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CGeneticArtVCView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CGeneticArtVCView diagnostics

#ifdef _DEBUG
void CGeneticArtVCView::AssertValid() const
{
	CView::AssertValid();
}

void CGeneticArtVCView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGeneticArtVCDoc* CGeneticArtVCView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGeneticArtVCDoc)));
	return (CGeneticArtVCDoc*)m_pDocument;
}
#endif //_DEBUG


// CGeneticArtVCView message handlers

void CGeneticArtVCView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here	
	CGeneticArtVCDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CRect client_rect;
	GetClientRect(&client_rect);

	pDoc->OnSize(client_rect);
}

void CGeneticArtVCView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	CGeneticArtVCDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (pDoc)
	{
		CRect client_rect;
		GetClientRect(&client_rect);
		bool changed=pDoc->OnMouseMove(nFlags, client_rect, point);
		if(changed)
		{
			Invalidate(FALSE);
		}
	}

	
	CView::OnMouseMove(nFlags, point);
}

void CGeneticArtVCView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	CGeneticArtVCDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (pDoc)
	{
		CRect client_rect;
		GetClientRect(&client_rect);
		bool changed=pDoc->OnLButtonDown(nFlags, client_rect, point);
		if(changed)
		{
			Invalidate(FALSE);
		}
	}

	CView::OnLButtonDown(nFlags, point);
}

void CGeneticArtVCView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	CGeneticArtVCDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (pDoc)
	{
		CRect client_rect;
		GetClientRect(&client_rect);
		bool changed=pDoc->OnLButtonDbClk(nFlags, client_rect, point);
		if(changed)
		{
			Invalidate(FALSE);
		}
	}

	CView::OnLButtonDblClk(nFlags, point);
}

