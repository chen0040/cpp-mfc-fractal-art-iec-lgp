// GeneticArtVCView.h : interface of the CGeneticArtVCView class
//


#pragma once


class CGeneticArtVCView : public CView
{
protected: // create from serialization only
	CGeneticArtVCView();
	DECLARE_DYNCREATE(CGeneticArtVCView)

// Attributes
public:
	CGeneticArtVCDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CGeneticArtVCView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // debug version in GeneticArtVCView.cpp
inline CGeneticArtVCDoc* CGeneticArtVCView::GetDocument() const
   { return reinterpret_cast<CGeneticArtVCDoc*>(m_pDocument); }
#endif

