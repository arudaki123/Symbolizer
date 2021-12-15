// workspace.cpp : implementation of the CWorkSpaceBar class
//

#include "stdafx.h"
#include "BCGPSymbolizer.h"
#include "WorkSpaceBar_Python.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CWorkSpaceBar

BEGIN_MESSAGE_MAP(CWorkSpaceBar_Python, CBCGPDockingControlBar)
	ON_WM_CREATE()
	ON_WM_SIZE()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWorkSpaceBar construction/destruction

CWorkSpaceBar_Python::CWorkSpaceBar_Python()
{
	m_pContext = NULL;
	m_pDatasourcesPython = new Datasources_Python;
}

CWorkSpaceBar_Python::~CWorkSpaceBar_Python()
{
}


/////////////////////////////////////////////////////////////////////////////
// CWorkSpaceBar message handlers

int CWorkSpaceBar_Python::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CBCGPDockingControlBar::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rectDummy;
	rectDummy.SetRectEmpty();

	if (m_pDatasourcesPython != NULL)
	{
		m_pDatasourcesPython->CreateView(this, m_pContext);
	}

	return 0;
}

void CWorkSpaceBar_Python::OnSize(UINT nType, int cx, int cy)
{
	CBCGPDockingControlBar::OnSize(nType, cx, cy);

	if (m_pDatasourcesPython->GetSafeHwnd())
	{
		m_pDatasourcesPython->SetWindowPos(NULL, -1, -1, cx, cy, SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);
	}

	// Tree control should cover a whole client area:
	//m_wndTree.SetWindowPos(NULL, 0, 0, cx, cy, SWP_NOACTIVATE | SWP_NOZORDER);


}

std::string CWorkSpaceBar_Python::SettingsXml()
{
	return m_pDatasourcesPython->SettingsXml();
}
void CWorkSpaceBar_Python::SettingsXml(std::string str)
{
	m_pDatasourcesPython->SettingsXml(str);
}