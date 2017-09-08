#pragma once
#include "afx.h"

class CXSButton :
	public CObject
{
public:
	CXSButton(CString id, double left, double top, double width, double height);
	~CXSButton(void);

protected:
	double m_left;
	double m_top;
	double m_width;
	double m_height;
	bool m_bMouseHovered;
	CString m_ButtonID;
public:
	virtual bool OnMouseMove(const CRect& client_rect , CPoint point);
	virtual bool IsMouseHovered() const { return m_bMouseHovered; }
	CString GetButtonID() const { return m_ButtonID; }
protected:
	CRect GetViewportRect(const CRect& client_rect);
public:
	void Render(CDC* pDC, const CRect& client_rect);
};
