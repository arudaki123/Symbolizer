#include "stdafx.h"
#include "WorkSpaceBar_Point.h"
#include "BCGPSymbolizer.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CWorkSpaceBar

BEGIN_MESSAGE_MAP(CWorkSpaceBar_Point, CBCGPDockingControlBar)
	ON_WM_CREATE()
	ON_WM_SIZE()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWorkSpaceBar construction/destruction

CWorkSpaceBar_Point::CWorkSpaceBar_Point()
{
	m_pContext = NULL;
	m_pSymbolizerPoint = new Symbolizer_Point;
}

CWorkSpaceBar_Point::~CWorkSpaceBar_Point()
{
}


/////////////////////////////////////////////////////////////////////////////
// CWorkSpaceBar message handlers

int CWorkSpaceBar_Point::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CBCGPDockingControlBar::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rectDummy;
	rectDummy.SetRectEmpty();

	if (m_pSymbolizerPoint != NULL)
	{
		m_pSymbolizerPoint->CreateView(this, m_pContext);
	}

	return 0;
}

void CWorkSpaceBar_Point::OnSize(UINT nType, int cx, int cy)
{
	CBCGPDockingControlBar::OnSize(nType, cx, cy);

	if (m_pSymbolizerPoint->GetSafeHwnd())
	{
		m_pSymbolizerPoint->SetWindowPos(NULL, -1, -1, cx, cy, SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);
	}

	// Tree control should cover a whole client area:
	//m_wndTree.SetWindowPos(NULL, 0, 0, cx, cy, SWP_NOACTIVATE | SWP_NOZORDER);


}

std::string CWorkSpaceBar_Point::SettingsXml()
{
	return m_pSymbolizerPoint->SettingsXml();
}
void CWorkSpaceBar_Point::SettingsXml(std::string str)
{
	m_pSymbolizerPoint->SettingsXml(str);
}