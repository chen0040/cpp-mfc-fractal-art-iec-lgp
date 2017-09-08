#include "StdAfx.h"
#include "MVCSubscriber.h"
#include "GeneticArtVCDoc.h"
#include "GeneticArtVCView.h"

CMVCSubscriber::CMVCSubscriber(void)
: m_pDoc(NULL)
, m_pView(NULL)
{
}

CMVCSubscriber::~CMVCSubscriber(void)
{
}

CMVCSubscriber* CMVCSubscriber::Instance()
{
	static CMVCSubscriber theInstance;
	return &theInstance;
}


void CMVCSubscriber::InvalidateView(bool bErase)
{
	m_pView->Invalidate(bErase);
}
