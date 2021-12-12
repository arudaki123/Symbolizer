#include "stdafx.h"
#include "WorkSpaceBar_Raster.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CWorkSpaceBar

BEGIN_MESSAGE_MAP(CWorkSpaceBar_Raster, CBCGPDockingControlBar)
	ON_WM_CREATE()
	ON_WM_SIZE()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWorkSpaceBar construction/destruction

CWorkSpaceBar_Raster::CWorkSpaceBar_Raster()
{
	m_pContext = NULL;
	m_pSymbolizerRaster = new Symbolizer_Raster;
}

CWorkSpaceBar_Raster::~CWorkSpaceBar_Raster()
{
}


/////////////////////////////////////////////////////////////////////////////
// CWorkSpaceBar message handlers

int CWorkSpaceBar_Raster::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CBCGPDockingControlBar::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rectDummy;
	rectDummy.SetRectEmpty();

	if (m_pSymbolizerRaster != NULL)
	{
		m_pSymbolizerRaster->CreateView(this, m_pContext);
	}

	return 0;
}

void CWorkSpaceBar_Raster::OnSize(UINT nType, int cx, int cy)
{
	CBCGPDockingControlBar::OnSize(nType, cx, cy);

	if (m_pSymbolizerRaster->GetSafeHwnd())
	{
		m_pSymbolizerRaster->SetWindowPos(NULL, -1, -1, cx, cy, SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);
	}

	// Tree control should cover a whole client area:
	//m_wndTree.SetWindowPos(NULL, 0, 0, cx, cy, SWP_NOACTIVATE | SWP_NOZORDER);


}

std::string CWorkSpaceBar_Raster::SettingsXml()
{
	return m_pSymbolizerRaster->SettingsXml();
}
void CWorkSpaceBar_Raster::SettingsXml(std::string str)
{
	m_pSymbolizerRaster->SettingsXml(str);
}