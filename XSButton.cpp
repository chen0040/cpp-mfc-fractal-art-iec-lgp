#include "StdAfx.h"
#include "XSButton.h"

CXSButton::CXSButton(CString id, double left, double top, double width, double height)
: m_left(left)
, m_top(top)
, m_width(width)
, m_height(height)
, m_bMouseHovered(false)
, m_ButtonID(id)
{
	
}

CXSButton::~CXSButton(void)
{
}

bool CXSButton::OnMouseMove(const CRect& client_rect , CPoint point)
{
	CRect vp_rect=GetViewportRect(client_rect);

	bool prev_state=m_bMouseHovered;
	if(vp_rect.PtInRect(point))
	{
		m_bMouseHovered=true;
	}
	else
	{
		m_bMouseHovered=false;
	}

	return prev_state != m_bMouseHovered;
}


CRect CXSButton::GetViewportRect(const CRect& client_rect)
{
	double client_width=static_cast<double>(client_rect.Width());
	double client_height=static_cast<double>(client_rect.Height());

	CRect viewport_rect;
	viewport_rect.left=client_rect.left+static_cast<int>(m_left * client_width);
	viewport_rect.top=client_rect.top+static_cast<int>(m_top * client_height);
	viewport_rect.bottom=static_cast<int>(viewport_rect.top+m_height * client_height);
	viewport_rect.right=static_cast<int>(viewport_rect.left+m_width * client_width);

	return viewport_rect;
}

void CXSButton::Render(CDC* pDC, const CRect& client_rect)
{
	CRect vp_rect=GetViewportRect(client_rect);

	if(m_bMouseHovered)
	{
		CPen pen;
		pen.CreatePen(PS_SOLID, 1, RGB(130, 255, 255));

		CBrush brush;
		brush.CreateSolidBrush(RGB(205, 205, 255));

		CBrush brush2;
		brush2.CreateSolidBrush(RGB(245, 245, 255));

		CPen* old_pen=pDC->SelectObject(&pen);
		CBrush* old_brush=pDC->SelectObject(&brush);

		vp_rect.InflateRect(1, 1);
		vp_rect.top-=1;
		vp_rect.bottom-=1;
		vp_rect.left-=1;
		vp_rect.right-=1;
		pDC->RoundRect(vp_rect.left, vp_rect.top, vp_rect.right, vp_rect.bottom, 10, 10);

		vp_rect.InflateRect(-3, -3);
		pDC->SelectObject(&brush2);
		pDC->RoundRect(vp_rect.left, vp_rect.top, vp_rect.right, vp_rect.bottom, 10, 10);

		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(130, 130, 255));
		pDC->DrawText(m_ButtonID, vp_rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

		pDC->SelectObject(old_pen);
		pDC->SelectObject(old_brush);

		pen.DeleteObject();
		brush.DeleteObject();
		brush.DeleteObject();
	}
	else
	{
		CPen pen;
		pen.CreatePen(PS_SOLID, 1, RGB(180, 180, 255));

		CBrush brush;
		brush.CreateSolidBrush(RGB(235, 235, 235));

		CPen* old_pen=pDC->SelectObject(&pen);
		CBrush* old_brush=pDC->SelectObject(&brush);

		pDC->RoundRect(vp_rect.left, vp_rect.top, vp_rect.right, vp_rect.bottom, 10, 10);

		vp_rect.InflateRect(-3, -3);
		pDC->SelectStockObject(NULL_BRUSH);
		pDC->RoundRect(vp_rect.left, vp_rect.top, vp_rect.right, vp_rect.bottom, 10, 10);

		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(180, 180, 255));
		pDC->DrawText(m_ButtonID, vp_rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

		pDC->SelectObject(old_pen);
		pDC->SelectObject(old_brush);

		pen.DeleteObject();
		brush.DeleteObject();
	}
}
