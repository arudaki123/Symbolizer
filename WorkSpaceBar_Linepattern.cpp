// workspace.cpp : implementation of the CWorkSpaceBar class
//

#include "stdafx.h"
#include "BCGPSymbolizer.h"
#include "WorkSpaceBar_Linepattern.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CWorkSpaceBar

BEGIN_MESSAGE_MAP(CWorkSpaceBar_Linepattern, CBCGPDockingControlBar)
	ON_WM_CREATE()
	ON_WM_SIZE()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWorkSpaceBar construction/destruction

CWorkSpaceBar_Linepattern::CWorkSpaceBar_Linepattern()
{
	m_pContext = NULL;
	m_pSymbolizerLinepattern = new Symbolizer_Linepattern;
}

CWorkSpaceBar_Linepattern::~CWorkSpaceBar_Linepattern()
{
}


/////////////////////////////////////////////////////////////////////////////
// CWorkSpaceBar message handlers

int CWorkSpaceBar_Linepattern::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CBCGPDockingControlBar::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rectDummy;
	rectDummy.SetRectEmpty();

	if (m_pSymbolizerLinepattern != NULL)
	{
		m_pSymbolizerLinepattern->CreateView(this, m_pContext);
	}

	return 0;
}

void CWorkSpaceBar_Linepattern::OnSize(UINT nType, int cx, int cy)
{
	CBCGPDockingControlBar::OnSize(nType, cx, cy);

	if (m_pSymbolizerLinepattern->GetSafeHwnd())
	{
		m_pSymbolizerLinepattern->SetWindowPos(NULL, -1, -1, cx, cy, SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);
	}

	// Tree control should cover a whole client area:
	//m_wndTree.SetWindowPos(NULL, 0, 0, cx, cy, SWP_NOACTIVATE | SWP_NOZORDER);


}

std::string CWorkSpaceBar_Linepattern::SettingsXml()
{
	return m_pSymbolizerLinepattern->SettingsXml();
}
void CWorkSpaceBar_Linepattern::SettingsXml(std::string str)
{
	m_pSymbolizerLinepattern->SettingsXml(str);
}