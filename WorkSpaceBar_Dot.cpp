#include "stdafx.h"
#include "WorkSpaceBar_Dot.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CWorkSpaceBar

BEGIN_MESSAGE_MAP(CWorkSpaceBar_Dot, CBCGPDockingControlBar)
	ON_WM_CREATE()
	ON_WM_SIZE()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWorkSpaceBar construction/destruction

CWorkSpaceBar_Dot::CWorkSpaceBar_Dot()
{
	m_pContext = NULL;
	m_pSymbolizerDot = new Symbolizer_Dot;
}

CWorkSpaceBar_Dot::~CWorkSpaceBar_Dot()
{
}


/////////////////////////////////////////////////////////////////////////////
// CWorkSpaceBar message handlers

int CWorkSpaceBar_Dot::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CBCGPDockingControlBar::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rectDummy;
	rectDummy.SetRectEmpty();

	if (m_pSymbolizerDot != NULL)
	{
		m_pSymbolizerDot->CreateView(this, m_pContext);
	}

	return 0;
}

void CWorkSpaceBar_Dot::OnSize(UINT nType, int cx, int cy)
{
	CBCGPDockingControlBar::OnSize(nType, cx, cy);

	if (m_pSymbolizerDot->GetSafeHwnd())
	{
		m_pSymbolizerDot->SetWindowPos(NULL, -1, -1, cx, cy, SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);
	}

	// Tree control should cover a whole client area:
	//m_wndTree.SetWindowPos(NULL, 0, 0, cx, cy, SWP_NOACTIVATE | SWP_NOZORDER);


}

std::string CWorkSpaceBar_Dot::SettingsXml()
{
	return m_pSymbolizerDot->SettingsXml();
}
void CWorkSpaceBar_Dot::SettingsXml(std::string str)
{
	m_pSymbolizerDot->SettingsXml(str);
}