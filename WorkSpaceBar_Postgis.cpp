// workspace.cpp : implementation of the CWorkSpaceBar class
//

#include "stdafx.h"
#include "BCGPSymbolizer.h"
#include "WorkSpaceBar_Postgis.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CWorkSpaceBar

BEGIN_MESSAGE_MAP(CWorkSpaceBar_Postgis, CBCGPDockingControlBar)
	ON_WM_CREATE()
	ON_WM_SIZE()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWorkSpaceBar construction/destruction

CWorkSpaceBar_Postgis::CWorkSpaceBar_Postgis()
{
	m_pContext = NULL;
	m_pDatasourcesPostgis = new Datasources_Postgis;
}

CWorkSpaceBar_Postgis::~CWorkSpaceBar_Postgis()
{
}


/////////////////////////////////////////////////////////////////////////////
// CWorkSpaceBar message handlers

int CWorkSpaceBar_Postgis::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CBCGPDockingControlBar::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rectDummy;
	rectDummy.SetRectEmpty();

	if (m_pDatasourcesPostgis != NULL)
	{
		m_pDatasourcesPostgis->CreateView(this, m_pContext);
	}

	return 0;
}

void CWorkSpaceBar_Postgis::OnSize(UINT nType, int cx, int cy)
{
	CBCGPDockingControlBar::OnSize(nType, cx, cy);

	if (m_pDatasourcesPostgis->GetSafeHwnd())
	{
		m_pDatasourcesPostgis->SetWindowPos(NULL, -1, -1, cx, cy, SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);
	}

	// Tree control should cover a whole client area:
	//m_wndTree.SetWindowPos(NULL, 0, 0, cx, cy, SWP_NOACTIVATE | SWP_NOZORDER);


}

std::string CWorkSpaceBar_Postgis::SettingsXml()
{
	return m_pDatasourcesPostgis->SettingsXml();
}
void CWorkSpaceBar_Postgis::SettingsXml(std::string str)
{
	m_pDatasourcesPostgis->SettingsXml(str);
}