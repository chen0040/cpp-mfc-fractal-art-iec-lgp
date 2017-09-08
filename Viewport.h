#pragma once
#include "afx.h"

class PixelArtist;

class CViewport :
	public CObject
{
public:
	CViewport(double left, double top, double width, double height);
	~CViewport(void);

public:
	void Render(CDC* pDC, const CRect& client_rect);

protected:
	double m_left;
	double m_top;
	double m_width;
	double m_height;
	COLORREF m_background_color;
	COLORREF m_frame_color;
	COLORREF m_hoverred_frame_color;
	bool m_bMouseHovered;
	CImage m_image;
	PixelArtist* m_program;
	CString m_text;
public:
	virtual void SetMouseHovered(bool bHovered);
	virtual bool IsMouseHovered(const CRect& client_rect, CPoint point);
	virtual bool GetMouseHovered() const { return m_bMouseHovered; }
	virtual void OnSize(const CRect& client_rect);
	virtual void SetArtist(PixelArtist* pProgram);
	virtual void PaintImage(CImage& img, PixelArtist* program=NULL);
	virtual void Invalidate();
	virtual void SetText(CString text);
	virtual bool OnLButtonDbClk(int nFlags, const CRect& client_rect, CPoint point);
protected:
	CRect GetViewportRect(const CRect& client_rect);
public:
	virtual CString ToString(void);
};
