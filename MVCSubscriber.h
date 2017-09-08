#pragma once
#include "afx.h"

class CGeneticArtVCDoc;
class CGeneticArtVCView;

class CMVCSubscriber :
	public CObject
{
public:
	static CMVCSubscriber* Instance();
	~CMVCSubscriber(void);

private:
	CMVCSubscriber(void);
	CMVCSubscriber(const CMVCSubscriber& rhs) { }
	CMVCSubscriber& operator=(const CMVCSubscriber& rhs) { return *this; }

public:
	void SetView(CGeneticArtVCView* pView) { m_pView=pView; }
	void SetDoc(CGeneticArtVCDoc* pDoc) { m_pDoc=pDoc; }

private:
	CGeneticArtVCView* m_pView;
	CGeneticArtVCDoc* m_pDoc;
public:
	virtual void InvalidateView(bool bErase=TRUE);
};

#define mvcSubscriber (*(CMVCSubscriber::Instance()))
