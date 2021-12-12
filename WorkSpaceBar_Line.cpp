// workspace.cpp : implementation of the CWorkSpaceBar_Line class
//

#include "stdafx.h"
#include "BCGPSymbolizer.h"
#include "WorkSpaceBar_Line.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CWorkSpaceBar_Line

BEGIN_MESSAGE_MAP(CWorkSpaceBar_Line, CBCGPDockingControlBar)
	ON_WM_CREATE()
	ON_WM_SIZE()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWorkSpaceBar_Line construction/destruction

CWorkSpaceBar_Line::CWorkSpaceBar_Line()
{
	m_pContext = NULL;
	m_pSymbolizerLine = new Symbolizer_Line;
}

CWorkSpaceBar_Line::~CWorkSpaceBar_Line()
{
}


/////////////////////////////////////////////////////////////////////////////
// CWorkSpaceBar_Line message handlers

int CWorkSpaceBar_Line::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CBCGPDockingControlBar::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rectDummy;
	rectDummy.SetRectEmpty();

	if (m_pSymbolizerLine != NULL)
	{
		m_pSymbolizerLine->CreateView(this, m_pContext);
	}

	return 0;
}

void CWorkSpaceBar_Line::OnSize(UINT nType, int cx, int cy)
{
	CBCGPDockingControlBar::OnSize(nType, cx, cy);

	if (m_pSymbolizerLine->GetSafeHwnd())
	{
		m_pSymbolizerLine->SetWindowPos(NULL, -1, -1, cx, cy, SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);
	}

	// Tree control should cover a whole client area:
	//m_wndTree.SetWindowPos(NULL, 0, 0, cx, cy, SWP_NOACTIVATE | SWP_NOZORDER);

	
}

std::string CWorkSpaceBar_Line::SettingsXml()
{
	return m_pSymbolizerLine->SettingsXml();
}
void CWorkSpaceBar_Line::SettingsXml(std::string str)
{
	m_pSymbolizerLine->SettingsXml(str);
}