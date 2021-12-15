#include "stdafx.h"
#include "WorkSpaceBar_Osm.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CWorkSpaceBar

BEGIN_MESSAGE_MAP(CWorkSpaceBar_Osm, CBCGPDockingControlBar)
	ON_WM_CREATE()
	ON_WM_SIZE()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWorkSpaceBar construction/destruction

CWorkSpaceBar_Osm::CWorkSpaceBar_Osm()
{
	m_pContext = NULL;
	m_pDatasourcesOsm = new Datasources_Osm;
}

CWorkSpaceBar_Osm::~CWorkSpaceBar_Osm()
{
}


/////////////////////////////////////////////////////////////////////////////
// CWorkSpaceBar message handlers

int CWorkSpaceBar_Osm::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CBCGPDockingControlBar::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rectDummy;
	rectDummy.SetRectEmpty();

	if (m_pDatasourcesOsm != NULL)
	{
		m_pDatasourcesOsm->CreateView(this, m_pContext);
	}

	return 0;
}

void CWorkSpaceBar_Osm::OnSize(UINT nType, int cx, int cy)
{
	CBCGPDockingControlBar::OnSize(nType, cx, cy);

	if (m_pDatasourcesOsm->GetSafeHwnd())
	{
		m_pDatasourcesOsm->SetWindowPos(NULL, -1, -1, cx, cy, SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);
	}

	// Tree control should cover a whole client area:
	//m_wndTree.SetWindowPos(NULL, 0, 0, cx, cy, SWP_NOACTIVATE | SWP_NOZORDER);


}

std::string CWorkSpaceBar_Osm::SettingsXml()
{
	return m_pDatasourcesOsm->SettingsXml();
}
void CWorkSpaceBar_Osm::SettingsXml(std::string str)
{
	m_pDatasourcesOsm->SettingsXml(str);
}