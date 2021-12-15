#include "stdafx.h"
#include "WorkSpaceBar_Ogr.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CWorkSpaceBar

BEGIN_MESSAGE_MAP(CWorkSpaceBar_Ogr, CBCGPDockingControlBar)
	ON_WM_CREATE()
	ON_WM_SIZE()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWorkSpaceBar construction/destruction

CWorkSpaceBar_Ogr::CWorkSpaceBar_Ogr()
{
	m_pContext = NULL;
	m_pDatasourcesOgr = new Datasources_Ogr;
}

CWorkSpaceBar_Ogr::~CWorkSpaceBar_Ogr()
{
}


/////////////////////////////////////////////////////////////////////////////
// CWorkSpaceBar message handlers

int CWorkSpaceBar_Ogr::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CBCGPDockingControlBar::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rectDummy;
	rectDummy.SetRectEmpty();

	if (m_pDatasourcesOgr != NULL)
	{
		m_pDatasourcesOgr->CreateView(this, m_pContext);
	}

	return 0;
}

void CWorkSpaceBar_Ogr::OnSize(UINT nType, int cx, int cy)
{
	CBCGPDockingControlBar::OnSize(nType, cx, cy);

	if (m_pDatasourcesOgr->GetSafeHwnd())
	{
		m_pDatasourcesOgr->SetWindowPos(NULL, -1, -1, cx, cy, SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);
	}

	// Tree control should cover a whole client area:
	//m_wndTree.SetWindowPos(NULL, 0, 0, cx, cy, SWP_NOACTIVATE | SWP_NOZORDER);


}

std::string CWorkSpaceBar_Ogr::SettingsXml()
{
	return m_pDatasourcesOgr->SettingsXml();
}
void CWorkSpaceBar_Ogr::SettingsXml(std::string str)
{
	m_pDatasourcesOgr->SettingsXml(str);
}