#include "StdAfx.h"
#include "Viewport.h"
#include "PixelArtist/PixelArtist.h"
#include "MVCSubscriber.h"

CViewport::CViewport(double left, double top, double width, double height)
: m_left(left)
, m_top(top)
, m_width(width)
, m_height(height)
, m_background_color(RGB(235, 235, 255))
, m_frame_color(RGB(180, 180, 255))
, m_hoverred_frame_color(RGB(180, 180, 255))
, m_bMouseHovered(false)
, m_program(NULL)
{
}

CViewport::~CViewport(void)
{
	if(!m_image.IsNull())
	{
		m_image.Destroy();
	}
}

void CViewport::Invalidate()
{
	this->PaintImage(m_image, m_program); 
}

void CViewport::PaintImage(CImage& img, PixelArtist* program)
{
	if(program != NULL)
	{
		program->Paint(img);
	}
	else
	{
		CDC* image_dc=CDC::FromHandle(img.GetDC());

		CBrush brush;
		brush.CreateSolidBrush(m_background_color);

		CPen* old_pen=static_cast<CPen*>(image_dc->SelectStockObject(NULL_PEN));
		CBrush* old_brush=image_dc->SelectObject(&brush);

		image_dc->Rectangle(0, 0, img.GetWidth(), img.GetHeight());

		image_dc->SelectObject(old_pen);
		image_dc->SelectObject(old_brush);

		brush.DeleteObject();

		img.ReleaseDC();
	}
}

void CViewport::SetArtist(PixelArtist* pProgram)
{
	m_program=pProgram; 
	if(m_program->HasValidFitness())
	{
		m_text.Format(_T("H:%f"), m_program->GetFitness());
	}
}

void CViewport::OnSize(const CRect& client_rect)
{
	CRect viewport_rect=GetViewportRect(client_rect);

	CImage timg;
	timg.Create(viewport_rect.Width(), viewport_rect.Height(), 24);

	if(!m_image.IsNull())
	{
		CDC* timg_dc=CDC::FromHandle(timg.GetDC());	
		m_image.StretchBlt(timg_dc->m_hDC, 0, 0, timg.GetWidth(), timg.GetHeight(), SRCCOPY);
		timg.ReleaseDC();

		m_image.Destroy();
	}
	else
	{
		this->PaintImage(timg);
	}

	m_image.Create(viewport_rect.Width(), viewport_rect.Height(), 24);
	CDC* img_dc=CDC::FromHandle(m_image.GetDC());
	timg.BitBlt(img_dc->m_hDC, 0, 0, SRCCOPY);
	m_image.ReleaseDC();

	timg.Destroy();
}

void CViewport::Render(CDC* pDC, const CRect& client_rect)
{
	CRect viewport_rect=GetViewportRect(client_rect);

	if(m_image.IsNull())
	{
		m_image.Create(viewport_rect.Width(), viewport_rect.Height(), 24);
		PaintImage(m_image);
	}

	CPen pen;
	if(m_bMouseHovered)
	{
		pen.CreatePen(PS_SOLID, 3, m_hoverred_frame_color);
		viewport_rect.InflateRect(1, 1);
	}
	else
	{
		pen.CreatePen(PS_SOLID, 1, m_frame_color);
	}

	CPen* old_pen=pDC->SelectObject(&pen);
	CBrush* old_brush=static_cast<CBrush*>(pDC->SelectStockObject(NULL_BRUSH));

	m_image.BitBlt(pDC->m_hDC, viewport_rect.left, viewport_rect.top, SRCCOPY);

	if(m_text != _T(""))
	{
		pDC->SetBkMode(OPAQUE);
		if(m_bMouseHovered)
		{
			pDC->SetBkColor(RGB(255, 0, 0));
			pDC->SetTextColor(RGB(255, 255, 255));
		}
		else
		{
			pDC->SetBkColor(RGB(0, 0, 0));
			pDC->SetTextColor(RGB(255, 255, 255));
		}

		pDC->TextOut(viewport_rect.left, viewport_rect.top, m_text);
	}

	pDC->Rectangle(viewport_rect);
	//pDC->RoundRect(viewport_rect.left, viewport_rect.top, viewport_rect.right, viewport_rect.bottom, 5, 5);

	pDC->SelectObject(old_pen);
	pDC->SelectObject(old_brush);

	pen.DeleteObject();
}

void CViewport::SetText(CString text)
{
	m_text=text;
}

void CViewport::SetMouseHovered(bool bHovered)
{
	m_bMouseHovered=bHovered;
}

bool CViewport::IsMouseHovered(const CRect& client_rect, CPoint point)
{
	CRect viewport_rect=GetViewportRect(client_rect);

	if(viewport_rect.PtInRect(point)==TRUE)
	{
		return true;
	}

	return false;
}

CRect CViewport::GetViewportRect(const CRect& client_rect)
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

bool CViewport::OnLButtonDbClk(int nFlags, const CRect& client_rect, CPoint point)
{
	CRect viewport_rect=GetViewportRect(client_rect);

	if(viewport_rect.PtInRect(point)==TRUE)
	{
		if(m_program == NULL)
		{
			return false;
		}

		m_program->EvaluateFitness(NULL);
		if(m_program->HasValidFitness())
		{
			m_text.Format(_T("H:%f"), m_program->GetFitness());
		}

		this->Invalidate();
		return true;
	}

	return false;
}


CString CViewport::ToString(void)
{
	if(m_program != NULL)
	{
		CString msg=CA2CT(m_program->ToString(true, true).c_str());
		msg.Replace(_T("\n"), _T("\r\n"));
		return msg;
	}

	return _T("Uninitialized");
}
